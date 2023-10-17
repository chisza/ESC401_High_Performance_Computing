set title 'Speedup'
set xlabel 'Threads'
set ylabel 'Speedup'
set key top left
plot x t 'Ideal Speedup', "sum_omp.dat" u 1:(1.072/$2) w l t 'OpenMP'
