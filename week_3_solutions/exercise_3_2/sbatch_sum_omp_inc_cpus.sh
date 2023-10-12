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

export OMP_NUM_THREADS=1
srun --exact --cpus-per-task=1 sum_omp
export OMP_NUM_THREADS=2
srun --exact --cpus-per-task=2 sum_omp
export OMP_NUM_THREADS=4
srun --exact --cpus-per-task=4 sum_omp
export OMP_NUM_THREADS=8
srun --exact --cpus-per-task=8 sum_omp
export OMP_NUM_THREADS=16
srun --exact --cpus-per-task=16 sum_omp
export OMP_NUM_THREADS=32
srun --exact --cpus-per-task=32 sum_omp
export OMP_NUM_THREADS=64
srun --exact --cpus-per-task=64 sum_omp
export OMP_NUM_THREADS=128
srun --exact --cpus-per-task=128 sum_omp 

wait
