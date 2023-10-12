#!/bin/bash -l
#SBATCH --job-name="sum_omp"
#SBATCH --account="uzh8"
#SBATCH --mail-type=ALL
#SBATCH --mail-user=chiara.zanatta@uzh.ch
#SBATCH --time=00:15:00
#SBATCH --nodes=1
#SBATCH --ntasks-per-core=1
#SBATCH --ntasks-per-node=1
#SBATCH --partition=debug
#SBATCH --constraint=mc
#SBATCH --hint=nomultithread
#SBATCH --output=%x_%j.out
#SBATCH --error=%x_%j.err

export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK

srun --cpus-per-task=1 sum_omp &
srun --cpus-per-task=2 sum_omp &
srun --cpus-per-task=4 sum_omp &
srun --cpus-per-task=8 sum_omp &
srun --cpus-per-task=16 sum_omp &
srun --cpus-per-task=32 sum_omp &
srun --cpus-per-task=64 sum_omp &
srun --cpus-per-task=128 sum_omp &

wait
