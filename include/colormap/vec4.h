#pragma once

#include <cassert>
#include <cstdint>
#include <string>

namespace colormap
{

struct vec4
{
	vec4(float a0, float a1, float a2, float a3)
		: x(a0)
		, y(a1)
		, z(a2)
		, w(a3)
	{
	}

	float operator[](size_t index) const
	{
		assert(index < 4);
		if (index < 2) {
			if (index < 1) {
				return x;
			} else {
				return y;
			}
		} else {
			if (index < 3) {
				return z;
			} else {
				return w;
			}
		}
	}

	float& operator[](size_t index)
	{
		assert(index < 4);
		if (index < 2) {
			if (index < 1) {
				return x;
			} else {
				return y;
			}
		} else {
			if (index < 3) {
				return z;
			} else {
				return w;
			}
		}
	}

	bool operator==(vec4 const& o) const
	{
		return x == o.x && y == o.y && z == o.z && w == o.w;
	}

	vec4 operator*(float v) const
	{
		return vec4(r * v, g * v, b * v, a * v);
	}

	vec4 operator+(vec4 const& v) const
	{
		return vec4(r + v.r, g + v.g, b + v.b, a + v.a);
	}

	std::string to_string() const
	{
		return
			std::string("{") +
			std::to_string(x) + std::string(",") +
			std::to_string(y) + std::string(",") +
			std::to_string(z) + std::string(",") +
			std::to_string(w) +
			std::string("}");
	}

	union {
		float r;
		float x;
	};
	union {
		float g;
		float y;
	};
	union {
		float b;
		float z;
	};
	union {
		float a;
		float w;
	};
};

} // namespace colormap
