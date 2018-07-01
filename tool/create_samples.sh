#!/bin/bash

function exec {
	echo -e "\033[2m$@\033[0m"
	$@
}

(
	cd "$(dirname "$0")/create_samples"
	exec pwd
	exec mkdir -p ../../samples
	(
		exec cd build
		exec cmake ..
		exec cmake --build .
	)

	echo find ../../shaders/glsl/*.frag | grep -v gnuplot | xargs -I{} -L1 -P $(sysctl -n hw.ncpu) bash -c 'build/create_samples {} ../../samples/$(basename "{}" | cut -d. -f1).png'
	find ../../shaders/glsl/*.frag | grep -v gnuplot | xargs -I{} -L1 -P $(sysctl -n hw.ncpu) bash -c 'build/create_samples {} ../../samples/$(basename "{}" | cut -d. -f1).png'

	for ARGS in 21_22_23 23_28_3 30_31_32 33_13_10 34_35_36 3_11_6 7_5_15; do
		A0=$(echo $ARGS | cut -f1 -d_)
		A1=$(echo $ARGS | cut -f2 -d_)
		A2=$(echo $ARGS | cut -f3 -d_)
		exec build/create_samples ../../shaders/glsl/gnuplot.frag ../../samples/gnuplot_$ARGS.png $A0 $A1 $A2
	done
)
