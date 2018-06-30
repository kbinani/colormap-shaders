#!/bin/bash

INPUT="$1"
OUTPUT="$2"

FILENAME=$(basename "$INPUT")
NAMESPACE1=$(echo "$FILENAME" | cut -d_ -f1 | sed 's/-/_/g')
NAMESPACE2=$(echo "$FILENAME" | cut -d_ -f2- | cut -d. -f1 | sed 's/-/_/g' | sed 's/+/_/g' | sed 's/^\([0-9]\)/_\1/g')

(
	echo "#include <metal_stdlib>"
	echo "using namespace metal;"
	echo
	echo "namespace colormap {"
	if [ "$NAMESPACE1" != "$FILENAME" ]; then
		echo "namespace $NAMESPACE1 {"
	fi
	echo "namespace $NAMESPACE2 {"
	echo

	cat "$INPUT" \
		| sed 's/vec4/float4/g' \
		| sed 's/mod/fmod/g' \
		| sed 's/STATIC_CONST/static constant/g'

	echo
	echo "} // namespace $NAMESPACE2"
	if [ "$NAMESPACE1" != "$FILENAME" ]; then
		echo "} // namespace $NAMESPACE1"
	fi
	echo "} // namespace colormap"
) > "$OUTPUT"
