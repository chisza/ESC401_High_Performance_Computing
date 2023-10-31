#!/bin/bash -l
#SBATCH --job-name="serial"
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

export OMP_NUM_TREADS=1
srun --exact --cpus-per-task=1 serial
export OMP_NUM_TREADS=5
srun --exact --cpus-per-task=5 serial
export OMP_NUM_THREADS=30 
srun --exact --cpus-per-task=30 serial
export OMP_NUM_TREADS=128
srun --exact --cpus-per-task=128 serial

