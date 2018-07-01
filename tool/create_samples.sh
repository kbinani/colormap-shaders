#!/bin/bash

(
	cd "$(dirname "$0")/create_samples"
	mkdir -p ../../samples
	(
		cd build
		cmake ..
		cmake --build .
	)
	find ../../shaders/glsl/*.frag | grep -v gnuplot | xargs -I{} -L1 bash -c 'build/create_samples {} ../../samples/$(basename "{}" | cut -d. -f1).png'
	for ARGS in 21_22_23 23_28_3 30_31_32 33_13_10 34_35_36 3_11_6 7_5_15; do
		A0=$(echo $ARGS | cut -f1 -d_)
		A1=$(echo $ARGS | cut -f2 -d_)
		A2=$(echo $ARGS | cut -f3 -d_)
		build/create_samples ../../shaders/glsl/gnuplot.frag ../../samples/gnuplot_$ARGS.png $A0 $A1 $A2
	done
)
