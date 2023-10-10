#!/bin/bash -l
#SBATCH --job-name="cpi"
#SBATCH --account="uzh8"
#SBATCH --mail-type=ALL
#SBATCH --mail-user=chiara.zanatta@uzh.ch
#SBATCH --time=00:05:00
#SBATCH --nodes=1
#SBATCH --ntasks-per-core=1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=128
#SBATCH --partition=debug
#SBATCH --constraint=mc
#SBATCH --hint=nomultithread
#SBATCH --output=%x_%j.out
#SBATCH --error=%x_%j.err

export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK

srun cpi
