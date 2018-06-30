#!/bin/bash

SHADERS="metal:metal
glsl:frag"

(
	cd "$(dirname "$0")/../src"
	for SHADER in $SHADERS; do
		TYPE=$(echo $SHADER | cut -d: -f1)
		EXT=$(echo $SHADER | cut -d: -f2)
		for FILE in $(find . -name '*\.txt'); do
			NAME=$(basename "$FILE" | cut -d. -f1)
			bash ../tool/transcode/glsl_to_${TYPE}.sh "$FILE" "../shaders/${TYPE}/${NAME}.${EXT}"
		done
	done
)
