for N in {0..1000..10}
do
  echo "N = $N"
  srun ./axpy_openacc $N

done