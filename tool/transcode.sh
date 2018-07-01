#!/bin/bash

SHADERS="metal:metal
glsl:frag"

(
	cd "$(dirname "$0")/../src"
	for SHADER in $SHADERS; do
		TYPE=$(echo $SHADER | cut -d: -f1)
		EXT=$(echo $SHADER | cut -d: -f2)
		mkdir -p "../shaders/$TYPE"
		find . -name '*\.txt' | xargs -I{} -L 1 -P $(sysctl -n hw.ncpu) bash -c "../tool/transcode/${TYPE}.sh {} ../shaders/$TYPE/\$(basename {} | cut -d. -f1).${EXT}"
	done
)
