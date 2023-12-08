for N in {0..1000..100}
do
  echo "N = $N"
  srun ./axpy.openacc $N
done