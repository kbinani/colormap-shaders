#!/bin/bash

DIR="$(cd "$(dirname "$0")"; pwd)"

(
	cd "$DIR/../shaders"
	echo -n "" > "../include/colormap/private/all_colormaps.h"
	echo -n "" > "../include/colormap/private/init_colormap_list.inc"
	for FILE in $(git ls-files | grep '\.frag$' | grep _); do
		CATEGORY=$(echo $FILE | sed 's/^\([^_]*\)_.*$/\1/g')
		NAME=$(echo $FILE | sed 's/^[^_]*_\(.*\)\.frag$/\1/g')
		CLASSNAME=
		for TOKEN in $(echo $NAME | tr '-' ' ' | tr '_' ' '); do
			if [ "$TOKEN" = "16" ]; then
				CLASSNAME="Sixteen"
			else
				CLASSNAME="${CLASSNAME}$(echo $TOKEN | cut -b 1 | tr a-z A-Z)$(echo $TOKEN | cut -b 2-)"
			fi
		done

		mkdir -p "$DIR/../include/colormap/private/$CATEGORY"
		(
			cat << EOS
#pragma once
#include "../../colormap.h"

namespace colormap
{
namespace ${CATEGORY}
{

class ${CLASSNAME} : public Colormap
{
private:
	class Wrapper : public WrapperBase
	{
	public:
		#include "../../../../shaders/${FILE}"
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
		return std::string("${NAME}");
	}

	std::string getCategory() const override
	{
		return std::string("${CATEGORY}");
	}
};

} // namespace ${CATEGORY}
} // namespace colormap
EOS
		) > "$DIR/../include/colormap/private/${CATEGORY}/${NAME}.h"

		echo "#include \"./${CATEGORY}/${NAME}.h\"" >> "../include/colormap/private/all_colormaps.h"
		echo "list_.push_back(std::make_shared<colormap::${CATEGORY}::${CLASSNAME}>());" >> "../include/colormap/private/init_colormap_list.inc"
	done
)
