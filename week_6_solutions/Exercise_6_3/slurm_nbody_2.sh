#!/bin/bash -l
#SBATCH --job-name="nbody_omp"
#SBATCH --account="uzh8"
#SBATCH --mail-type=ALL
#SBATCH --mail-user=chiara.zanatta@uzh.ch
#SBATCH --time=00:15:00
#SBATCH --nodes=1
#SBATCH --ntasks-per-core=1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=12
#SBATCH --partition=debug
#SBATCH --constraint=mc
#SBATCH --hint=nomultithread
#SBATCH --output=%x_%j.out
#SBATCH --error=%x_%j.err

srun nbody_omp 100
srun nbody_omp 500
srun nbody_omp 1000
srun nbody_omp 5000
srun nbody_omp 10000
srun nbody_omp 20000
srun nbody_omp 50000
