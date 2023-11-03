I expect that the most efficient solution is parallizing both loops with one ```#pragma omp parallel```. If each loop would be initialized
with its own parallelization, it would give more forkings, which would lead to more overhead.

The files [nbody_first_loop.cpp]('nbody_first_loop.cpp'), [nbody_second_loop.cpp]('nbody_secpmd_loop.cpp'), [nbody_both_loops.cpp]('nbody_both_loops.cpp') are my different implementations to check which is the fastest. Parallelising over both for loops was the fastest execution ([nbody_2422063.out]('nbody_2422063.out')). The rest of the exercise will be done with [nbody.cpp]('nbody.cpp'), modified to parallelize over both loops.

I expect it to scale with $N^2$, as each particle has to be compared to all the other particles.

The outputs for both the serial and parallel implementation are in [nbody_serial_2422574.out]('nbody_serial_2422574.out') and [nbody_omp_2422569.out]('nbody_omp_2422569.out'), respectively. The speedup is visible in the omp implementation for the higher number of particles, while for a lower amount of particles serial was faster.

Concerning the ploting, somehow the approach I used before for parsing did not work again, it did not find the matches, but it found the file. The file [parse.py]('parse.py') would be the file I used after I managed to force the nbody program to not print scientific notiation. Ploting could have been done after parsing with either python or bash.

Bonus: I think implementing an FFT is a way to speed up the N-Body calculation, 
in which case it would scale with $N log N$


