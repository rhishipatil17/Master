#include <iostream>
#include <cuda_runtime.h>

#define BLOCK_SIZE 64

__global__ void reverseArray(int *d_out, int *d_in)
{
	__shared__ int s_data[BLOCK_SIZE];					// __shared__ declares this memory within the block i.e. common to all threads within a block

	int idx = threadIdx.x;
	int ridx = BLOCK_SIZE - idx - 1;

	s_data[idx] = d_in[idx];

	__syncthreads();									// GPU waits for every thread to finish before proceding

	d_out[ridx] = s_data[idx];
}

int main()
{
	size_t size = BLOCK_SIZE * sizeof(int);
	int *h_in = (int *)malloc(size);
	int *h_out = (int *)malloc(size);

	for(int i=0; i<BLOCK_SIZE; i++)
	{
		h_in[i] = i;
	}

	std::cout << "Array before GPU reversing" << std::endl;
	for(int i=0; i<BLOCK_SIZE; i++)
	{
		std::cout << h_in[i] << " ";
	}
	std::cout << std::endl;

	int *d_in, *d_out;

	cudaMalloc((void **)&d_in, size);
	cudaMalloc((void **)&d_out, size);

	cudaMemcpy(d_in, h_in, size, cudaMemcpyHostToDevice);

	reverseArray<<<1, BLOCK_SIZE>>>(d_out, d_in);
	cudaError_t err = cudaGetLastError();
	std::cout << std::endl << "Kernel launch status: " << cudaGetErrorString(err) << std::endl << std:: endl;

	cudaDeviceSynchronize();
	cudaMemcpy(h_out, d_out, size, cudaMemcpyDeviceToHost);

	std::cout << "Array after GPU reversing" << std::endl;
	for(int i=0; i<BLOCK_SIZE; i++)
	{
		std::cout << h_out[i] << " ";
	}
	std::cout << std::endl;

	cudaFree(d_in);
	cudaFree(d_out);
	free(h_in);
	free(h_out);

	return 0;
}
