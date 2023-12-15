#include <time.h>
#include <cuda.h>
#include <stdio.h>
#define STOP 0
#define START 1

#define BLOCKSIZE 256 // number of threads per block


extern "C" void chrono (int kind, float *time);

__global__ void kconvol (float *gpu_a, float *gpu_b, int n) {
  int i, j, l;
  // TODO : evaluate the global 1D index l of the current thread,
  // using blockDim, blockIdx and threadIdx.
  l = threadIdx.x + blockIdx.x * blockDim.x;

  // TODO : evaluate global indeces of thread (i,j) from the index l
  j = l/n;
  i = l - j*n;

  if ((i >= n) || (j >= n)) return;
  if ((i == 0) || (j == 0) || (i == n-1) || (j == n-1))  {
    gpu_b[l] = gpu_a[l]; // edges are untouched
  }
  else
    // TODO : fill up the MISSING indices below
    gpu_b[l]=(1./5.)*(gpu_a[l-n] + gpu_a[l-1] + gpu_a[l] + gpu_a[l+1]+ gpu_a[l+n]);
}

extern "C" void gpu_convol (float *a, float *b, int n) {
  float *gpu_a;
  float *gpu_b;
  cudaError_t err;
  float time;
  
  err = cudaMalloc (&gpu_a, n*n*sizeof(float));
  if (err != 0) {
    printf ("Error allocating gpu_a: %s\n", cudaGetErrorString (err));
    exit (1);
  }
  err = cudaMalloc (&gpu_b, n*n*sizeof(float));
  if (err != 0) {
    printf ("Error allocating gpu_b: %s\n", cudaGetErrorString (err));
    exit (1);
  }
  
  cudaMemcpy (gpu_a, a, n*n*sizeof(float), cudaMemcpyHostToDevice);
    
  // NOTE : the chronometer below does not contemplate overhead of memory allocation and
  // memory transfer.
  chrono (START, &time);
  // TODO : the number of blocks is missing below in the kernel invocation
  int numBlocks = (n*n + BLOCKSIZE -1) / BLOCKSIZE;
  kconvol <<<numBlocks,BLOCKSIZE>>> (gpu_a, gpu_b, n);
  err=cudaDeviceSynchronize ();
  chrono (STOP, &time);
  printf ("Convolution took  %f sec. on GPU\n", time);
  cudaMemcpy (b, gpu_b, n*n*sizeof(float), cudaMemcpyDeviceToHost);
  if (err != 0) {
    printf ("%s\n", cudaGetErrorString (err));
    exit (1);
  }
  cudaFree (gpu_a);
  cudaFree (gpu_b);
}
