#pragma once
#include "./vec4.h"
#include <cmath>
#include <vector>
#include <string>

namespace colormap
{

class Colormap
{
public:
	struct Color
	{
		float r, g, b, a;
	};

public:
	virtual ~Colormap()
	{}

	virtual Color getColor(float x) const = 0;

	virtual std::string getTitle() const = 0;

	virtual std::string getCategory() const = 0;

protected:
	class WrapperBase
	{
	public:
		virtual ~WrapperBase()
		{}

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
class ColormapProvider
{
private:
	typedef std::shared_ptr<Colormap const> element_t;
	typedef std::vector<element_t> container_t;

public:
	static ColormapProvider const& getInstance()
	{
		static ColormapProvider instance;
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
	ColormapProvider()
	{
#include "./private/init_colormap_list.inc"
	}

	ColormapProvider(ColormapProvider const&) = delete;
	ColormapProvider(ColormapProvider&&) = delete;
	ColormapProvider& operator=(ColormapProvider const&) = delete;
	ColormapProvider& operator=(ColormapProvider&&) = delete;

private:
	container_t list_;
};

} // namespace colormap
