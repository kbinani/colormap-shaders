/**
 * This file was automatically created with "create_c++_header.sh".
 * Do not edit manually.
 */
#pragma once
#include "../../colormap.h"

namespace colormap
{
namespace IDL
{

class GreenWhiteLinear : public Colormap
{
private:
	class Wrapper : public WrapperBase
	{
	public:
		#pragma GCC diagnostic push
		#pragma GCC diagnostic ignored "-Wkeyword-macro"
		#define float local_real_t
		#include "../../../../shaders/glsl/IDL_Green-White_Linear.frag"
		#undef float
		#pragma GCC diagnostic pop
	};

public:
	Color getColor(double x) const override
	{
		Wrapper w;
		vec4 c = w.colormap(x);
		Color result;
		result.r = std::max(0.0, std::min(1.0, c.r));
		result.g = std::max(0.0, std::min(1.0, c.g));
		result.b = std::max(0.0, std::min(1.0, c.b));
		result.a = std::max(0.0, std::min(1.0, c.a));
		return result;
	}

	std::string getTitle() const override
	{
		return std::string("Green-White_Linear");
	}

	std::string getCategory() const override
	{
		return std::string("IDL");
	}

	std::string getSource() const override
	{
		return std::string(
			"float colormap_red(float x) {\n"
			"    return 1.61361058036781E+00 * x - 1.55391688559828E+02;\n"
			"}\n"
			"\n"
			"float colormap_green(float x) {\n"
			"    return 9.99817607003891E-01 * x + 1.01544260700389E+00;\n"
			"}\n"
			"\n"
			"float colormap_blue(float x) {\n"
			"    return 3.44167852062589E+00 * x - 6.19885917496444E+02;\n"
			"}\n"
			"\n"
			"vec4 colormap(float x) {\n"
			"    float t = x * 255.0;\n"
			"    float r = clamp(colormap_red(t) / 255.0, 0.0, 1.0);\n"
			"    float g = clamp(colormap_green(t) / 255.0, 0.0, 1.0);\n"
			"    float b = clamp(colormap_blue(t) / 255.0, 0.0, 1.0);\n"
			"    return vec4(r, g, b, 1.0);\n"
			"}\n"
		);
	}
};

} // namespace IDL
} // namespace colormap
