#include "../ext/pngpp/png.hpp"
#include <libgen.h>
#include <GLUT/glut.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>

int const width = 256;
int const height = 16;

std::string inputFile;

static std::string file_get_contents(std::string const& file)
{
    FILE* fp = fopen(file.c_str(), "r");
    if (fp == NULL) {
        return std::string("");
    }
    fseek(fp, 0, SEEK_END);
    long const length = ftell(fp);
    std::vector<char> buffer(length + 1);
    fseek(fp, 0, SEEK_SET);
    fread(buffer.data(), buffer.size(), sizeof(char), fp);
    fclose(fp);
    std::string s(buffer.data());
    return s;
}

static std::string get_sample_name(std::string const& file)
{
    size_t period_pos = file.find_last_of('.');
    if (period_pos != std::string::npos) {
        std::string draft = file.substr(0, period_pos) + std::string(".png");
        if (draft != file) {
            return draft;
        }
    }
    return file + std::string(".png");
}

static std::string get_shader_compile_error(GLuint shader)
{
    int logSize;

    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);

    if (logSize > 1) {
        std::vector<char> buffer(logSize, (char)0);
        int length;
        glGetShaderInfoLog(shader, logSize, &length, buffer.data());
        return std::string(buffer.data());
    } else {
        return std::string("");
    }
}

static void display(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glViewport(0, 0, width, height);
    glOrtho(0, width, height, 0, 0, -24);

    glEnable(GL_DEPTH_TEST);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_TEXTURE_2D);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    std::string srcString = file_get_contents(inputFile) + std::string("void main() { gl_FragColor = colormap(gl_TexCoord[0].x); }");
    char const* src = srcString.c_str();
    GLint const length = strlen(src) + 1;

    glShaderSource(fragmentShader, 1, (GLchar**)&src, &length);
    glCompileShader(fragmentShader);
    GLint compiled;
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compiled);
    if (compiled == GL_FALSE) {
        std::cerr << "failed to compile shader: " << inputFile << std::endl;
        std::cerr << get_shader_compile_error(fragmentShader);
        exit(1);
    }
    GLuint prog = glCreateProgram();
    glAttachShader(prog, fragmentShader);
    glDeleteShader(fragmentShader);
    glLinkProgram(prog);
    GLint linked;
    glGetProgramiv(prog, GL_LINK_STATUS, &linked);
    if (linked == GL_FALSE) {
        std::cerr << "link failed: " << inputFile << std::endl;
        std::cerr << get_shader_compile_error(fragmentShader);
        exit(1);
    }

    glUseProgram(prog);

    glBegin(GL_QUADS);
    {
        glTexCoord2f(0, 1);
        glVertex2i(0, 0);

        glTexCoord2f(1, 1);
        glVertex2i(width, 0);

        glTexCoord2f(1, 0);
        glVertex2i(width, height);

        glTexCoord2f(0, 0);
        glVertex2i(0, height);
    }
    glEnd();

	std::vector<uint8_t> data(width * height * 4);
	glReadBuffer(GL_BACK);
	glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data.data());
	
	png::image<png::rgb_pixel> image(width, height);
	size_t pos = 0;
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			image.set_pixel(x, y, png::rgb_pixel(data[pos], data[pos + 1], data[pos + 2]));
			pos += 4;
		}
	}
	image.write(get_sample_name(inputFile));

    exit(0);
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        std::cerr << "too few argument" << std::endl;
        return 1;
    } else if (argc > 2) {
        std::cerr << "too many arguments" << std::endl;
        return 1;
    }
    inputFile = argv[1];

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
    glutCreateWindow("create_samples");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
