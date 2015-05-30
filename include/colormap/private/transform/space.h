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

class Space : public Colormap
{
private:
	class Wrapper : public WrapperBase
	{
	public:
		#include "../../../../shaders/transform_space.frag"
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
		return std::string("space");
	}

	std::string getCategory() const override
	{
		return std::string("transform");
	}
};

} // namespace transform
} // namespace colormap
