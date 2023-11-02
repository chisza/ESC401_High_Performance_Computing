I expect that the most efficient solution is parallizing both loops with one ```#pragma omp parallel```. If each loop would be initialized
with its own parallelization, it would give more forkings, which would lead to more overhead.

The files [nbody_first_loop.cpp]('nbody_first_loop.cpp'), [nbody_second_loop.cpp]('nbody_secpmd_loop.cpp'), [nbody_both_loops.cpp]('nbody_both_loops.cpp') are my different implementations to check which is the fastest. Parallelising over both for loops was the fastest execution ([nbody_2422063.out]('nbody_2422063.out')). The rest of the exercise will be done with [nbody.cpp]('nbody.cpp'), modified to parallelize over both loops.

I expect it to scale with $N^2$, as each particle has to be compared to all the other particles.

Bonus: I think implementing an FFT is a way to speed up the N-Body calculation, 
in which case it would scale with $N log N$


