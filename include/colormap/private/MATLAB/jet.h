/**
 * This file was automatically created with "create_c++_header.sh".
 * Do not edit manually.
 */
#pragma once
#include "../../colormap.h"

namespace colormap
{
namespace MATLAB
{

class Jet : public Colormap
{
private:
	class Wrapper : public WrapperBase
	{
	public:
		#include "../../../../shaders/MATLAB_jet.frag"
	};

public:
	Color getColor(float x) const override
	{
		Wrapper w;
		vec4 c = w.colormap(x);
		Color result;
		result.r = std::max(0.0f, std::min(1.0f, c.r));
		result.g = std::max(0.0f, std::min(1.0f, c.g));
		result.b = std::max(0.0f, std::min(1.0f, c.b));
		result.a = std::max(0.0f, std::min(1.0f, c.a));
		return result;
	}

	std::string getTitle() const override
	{
		return std::string("jet");
	}

	std::string getCategory() const override
	{
		return std::string("MATLAB");
	}

	std::string getSource() const override
	{
		return std::string(
			"float colormap_red(float x) {\n"
			"    if (x < 0.7) {\n"
			"        return 4.0 * x - 1.5;\n"
			"    } else {\n"
			"        return -4.0 * x + 4.5;\n"
			"    }\n"
			"}\n"
			"\n"
			"float colormap_green(float x) {\n"
			"    if (x < 0.5) {\n"
			"        return 4.0 * x - 0.5;\n"
			"    } else {\n"
			"        return -4.0 * x + 3.5;\n"
			"    }\n"
			"}\n"
			"\n"
			"float colormap_blue(float x) {\n"
			"    if (x < 0.3) {\n"
			"       return 4.0 * x + 0.5;\n"
			"    } else {\n"
			"       return -4.0 * x + 2.5;\n"
			"    }\n"
			"}\n"
			"\n"
			"vec4 colormap(float x) {\n"
			"    float r = clamp(colormap_red(x), 0.0, 1.0);\n"
			"    float g = clamp(colormap_green(x), 0.0, 1.0);\n"
			"    float b = clamp(colormap_blue(x), 0.0, 1.0);\n"
			"    return vec4(r, g, b, 1.0);\n"
			"}\n"
		);
	}
};

} // namespace MATLAB
} // namespace colormap
