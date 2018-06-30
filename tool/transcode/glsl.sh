#!/bin/bash

INPUT="$1"
OUTPUT="$2"

cat "$INPUT" \
	| sed 's/STATIC_CONST//g' \
	| sed 's/FLOAT4/vec4/g' \
	> "$OUTPUT"
