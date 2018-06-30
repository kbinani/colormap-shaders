#!/bin/bash

function echo_header {
	cat << EOS
/**
 * This file was automatically created with "$(basename "$0")".
 * Do not edit manually.
 */
EOS
}

DIR="$(cd "$(dirname "$0")"; pwd)"

(
	cd "$DIR/../shaders/glsl"

	mkdir -p ../../include/colormap/private
	ALL_COLORMAPS_FILE="../../include/colormap/private/all_colormaps.h"
	INIT_COLORMAP_FILE="../../include/colormap/private/init_colormap_list.inc"
	echo_header > $ALL_COLORMAPS_FILE
	echo_header > $INIT_COLORMAP_FILE
	for FILE in $(find . -name '*\.frag' | grep _ | sort); do
		FILE=$(basename "$FILE")
		CATEGORY=$(echo "$FILE" | sed 's/^\([^_]*\)_.*$/\1/g')
		NAME=$(echo "$FILE" | sed 's/^[^_]*_\(.*\)\.frag$/\1/g')
		CLASSNAME=
		for TOKEN in $(echo $NAME | tr '-' ' ' | tr '_' ' ' | tr '+' ' '); do
			if [ "$TOKEN" = "16" ]; then
				CLASSNAME="Sixteen"
			else
				CLASSNAME="${CLASSNAME}$(echo $TOKEN | cut -b 1 | tr a-z A-Z)$(echo $TOKEN | cut -b 2-)"
			fi
		done

		mkdir -p "$DIR/../include/colormap/private/$CATEGORY"
		HEADER_FILE="$DIR/../include/colormap/private/${CATEGORY}/${NAME}.h"
		(
			echo_header
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
		#ifdef float
			#error "TODO"
		#endif
		#define float local_real_t
		#include "../../../../shaders/glsl/${FILE}"
		#undef float
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
		return std::string("${NAME}");
	}

	std::string getCategory() const override
	{
		return std::string("${CATEGORY}");
	}

	std::string getSource() const override
	{
		return std::string(
EOS
			cat "$FILE" | tr -d '\r' | sed 's/^\(.*\)$/			"\1\\n"/g'
			cat << EOS
		);
	}
};

} // namespace ${CATEGORY}
} // namespace colormap
EOS
		) > $HEADER_FILE

		echo "#include \"./${CATEGORY}/${NAME}.h\"" >> $ALL_COLORMAPS_FILE
		echo "std::make_shared<colormap::${CATEGORY}::${CLASSNAME}>()," >> $INIT_COLORMAP_FILE
	done
)
