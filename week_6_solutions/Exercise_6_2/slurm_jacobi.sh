#!/bin/bash -l
#SBATCH --job-name="jacobi_step"
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

export OMP_NUM_THREADS=1
srun --exact --cpus-per-task=1 main
export OMP_NUM_THREADS=2
srun --exact --cpus-per-task=2 main
export OMP_NUM_THREADS=3
srun --exact --cpus-per-task=3 main
export OMP_NUM_THREADS=4
srun --exact --cpus-per-task=4 main

