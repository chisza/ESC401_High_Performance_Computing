I expect that the most efficient solution is parallizing both loops with one ´´´#pragma omp parallel´´´. If each loop would be initialized
with its own parallelization, it would give more forkings, which would lead to more overhead.

I expect it to scale with $N^2$, as each particle has to be compared to all the other particles.

Bonus: I think implementing an FFT is a way to speed up the N-Body calculation, 
in which case it would scale with $N log N$
