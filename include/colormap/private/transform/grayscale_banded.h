/**
 * This file was automatically created with "create_c++_header.sh".
 * Do not edit manually.
 */
#pragma once
#include "../../colormap.h"

namespace colormap
{
namespace transform
{

class GrayscaleBanded : public Colormap
{
private:
	class Wrapper : public WrapperBase
	{
	public:
		#if defined(__clang__)
		#pragma clang diagnostic push
		#pragma clang diagnostic ignored "-Wkeyword-macro"
		#elif defined(__GNUC__)
		#pragma GCC diagnostic push
		#pragma GCC diagnostic ignored "-Wkeyword-macro"
		#endif

		#define float local_real_t
		#include "../../../../shaders/glsl/transform_grayscale_banded.frag"
		#undef float

		#if defined(__clang__)
		#pragma clang diagnostic pop
		#elif defined(__GNUC__)
		#pragma GCC diagnostic pop
		#endif
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
		return std::string("grayscale_banded");
	}

	std::string getCategory() const override
	{
		return std::string("transform");
	}

	std::string getSource() const override
	{
		return std::string(
			"vec4 colormap(float x) {\n"
			"    float v = cos(133.0 * x) * 28.0 + 230.0 * x + 27.0;\n"
			"    if (v > 255.0) {\n"
			"        v = 510.0 - v;\n"
			"    }\n"
			"    v = v / 255.0;\n"
			"    return vec4(v, v, v, 1.0);\n"
			"}\n"
		);
	}
};

} // namespace transform
} // namespace colormap
