#!/bin/bash -l
#SBATCH --job-name="sum_omp_multi_thread"
#SBATCH --account="uzh8"
#SBATCH --mail-type=ALL
#SBATCH --mail-user=chiara.zanatta@uzh.ch
#SBATCH --time=00:05:00
#SBATCH --nodes=1
#SBATCH --ntasks-per-core=1
#SBATCH --ntasks-per-node=1
#SBATCH --partition=debug
#SBATCH --constraint=mc
#SBATCH --hint=nomultithread
#SBATCH --output=%x_%j.out
#SBATCH --error=%x_%j.err

for i in {2..4..128}
do
	export OMP_NUM_THREADS=$i
	srun --cpus-per-task=$i sum_omp &
done

wait
