#!/bin/bash
set title 'OpenMP Speedup'
set xlabel 'Threads'
set ylabel 'Speedup'
set key top left
plot x lc 2 lw 2 t 'Ideal Speedup'\
	"cpi_openmp.txt" u 1:(4.55/$2),\
	w lp lc 1 lw 2 t 'OpenMp'
