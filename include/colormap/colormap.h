#pragma once
#include <cassert>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <memory>

namespace colormap
{

struct Color
{
	float r, g, b, a;
};

class Colormap
{
public:
	virtual ~Colormap()
	{}

	virtual Color getColor(float x) const = 0;

	virtual std::string getTitle() const = 0;

	virtual std::string getCategory() const = 0;

	virtual std::string getSource() const = 0;

protected:
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

	class WrapperBase
	{
	public:
		virtual ~WrapperBase()
		{}

	protected:
		template <class Value, class MinMax>
		typename std::common_type<Value, MinMax>::type clamp(Value v, MinMax min, MinMax max) const
		{
			if (v < min) {
				return min;
			} else if (max < v) {
				return max;
			} else {
				return v;
			}
		}

		template <class Value>
		Value sign(Value v) const
		{
			if (v < (Value)0) {
				return (Value)-1;
			} else if ((Value)0 < v) {
				return (Value)1;
			} else {
				return (Value)0;
			}
		}

		float abs(float v) const
		{
			return std::fabs(v);
		}
	};
};

} // namespace colormap

#include "./private/all_colormaps.h"

namespace colormap
{
class ColormapList
{
private:
	typedef std::shared_ptr<Colormap const> element_t;
	typedef std::vector<element_t> container_t;

public:
	static ColormapList const& getSharedList()
	{
		static ColormapList instance;
		return instance;
	}

	container_t::const_iterator begin() const
	{
		return list_.begin();
	}

	container_t::const_iterator end() const
	{
		return list_.end();
	}

	container_t::const_iterator cbegin() const
	{
		return list_.cbegin();
	}

	container_t::const_iterator cend() const
	{
		return list_.cend();
	}

	element_t const& at(size_t index) const
	{
		return list_[index];
	}

	element_t operator[](size_t index) const
	{
		return list_[index];
	}

	size_t size() const
	{
		return list_.size();
	}

private:
	ColormapList()
	{
#include "./private/init_colormap_list.inc"
	}

	ColormapList(ColormapList const&) = delete;
	ColormapList(ColormapList&&) = delete;
	ColormapList& operator=(ColormapList const&) = delete;
	ColormapList& operator=(ColormapList&&) = delete;

private:
	container_t list_;
};

} // namespace colormap
