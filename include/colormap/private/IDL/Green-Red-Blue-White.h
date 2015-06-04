#pragma once
#include "../../colormap.h"

namespace colormap
{
namespace IDL
{

class GreenRedBlueWhite : public Colormap
{
private:
	class Wrapper : public WrapperBase
	{
	public:
		#include "../../../../shaders/IDL_Green-Red-Blue-White.frag"
	};

public:
	Color getColor(float x) const override
	{
		Wrapper w;
		vec4 c = w.colormap(x);
		Color result;
		result.r = c.r;
		result.g = c.g;
		result.b = c.b;
		result.a = c.a;
		return result;
	}

	std::string getTitle() const override
	{
		return std::string("Green-Red-Blue-White");
	}

	std::string getCategory() const override
	{
		return std::string("IDL");
	}
};

} // namespace IDL
} // namespace colormap
