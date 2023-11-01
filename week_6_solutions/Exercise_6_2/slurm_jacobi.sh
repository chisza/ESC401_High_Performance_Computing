#!/bin/bash -l
#SBATCH --job-name="jacobi_step"
#SBATCH --account="uzh8"
#SBATCH --mail-type=ALL
#SBATCH --mail-user=chiara.zanatta@uzh.ch
#SBATCH --time=00:15:00
#SBATCH --nodes=1
#SBATCH --ntasks-per-core=1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=128
#SBATCH --partition=debug
#SBATCH --constraint=mc
#SBATCH --hint=nomultithread

export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK

srun main
