#include <iostream>
#include <cuda_runtime.h>

__global__ void addMatrix2D(unsigned int width, unsigned int height, float *a, float *b, float *c)
{
	int x = blockIdx.x * blockDim.x + threadIdx.x;						// x coordinate of thread in the entire pool
	int y = blockIdx.y * blockDim.y + threadIdx.y;						// y coordinate of thread in the entire pool

	if((x < width) && (y<height))										// check limits of the pool
	{
		unsigned int index = ( y * width ) + x;							// flatten the 2d coordinate to 1d coordinates
		c[index] = a[index] + b[index];
	}
}

int main()
{
	unsigned int width{ 1024 };
	unsigned int height{ 1024 };
	unsigned int threadsPerBlock_width{ 16 };
	unsigned int threadsPerBlock_height{ 16 };
	unsigned int dim{ width * height };
	size_t size = dim * sizeof(float);

	// Host memory
	float *h_a = new float[dim];
	float *h_b = new float[dim];
	float *h_c = new float[dim];
	
	for(int i=0; i<dim; i++)
	{
		h_a[i] = 1.0f;
		h_b[i] = 2.0f;
	}

	// Device memory
	float *d_a, *d_b, *d_c;
	cudaMalloc((void **)&d_a, size);
	cudaMalloc((void **)&d_b, size);
	cudaMalloc((void **)&d_c, size);

	cudaMemcpy(d_a, h_a, size, cudaMemcpyHostToDevice);
	cudaMemcpy(d_b, h_b, size, cudaMemcpyHostToDevice);

	dim3 threadsPerBlock(threadsPerBlock_width, threadsPerBlock_height);				// create a 2d grid of threads, 16 x 16 = 256 (256 threads in each block arranged in a grid of 16 x 16)

	dim3 blocksPerGrid(																	// create a 2d grid of blocks, round_up_formula(width) x round_up_formula(height)
		( width + threadsPerBlock.x - 1) / threadsPerBlock.x,
		( height + threadsPerBlock.y - 1) / threadsPerBlock.y
	);

	cudaEvent_t start_gpu, stop_gpu;
	cudaEventCreate(&start_gpu);
	cudaEventCreate(&stop_gpu);

	cudaEventRecord(start_gpu);
	addMatrix2D<<<blocksPerGrid, threadsPerBlock>>>(width, height, d_a, d_b, d_c);		// launch kernel
	cudaEventRecord(stop_gpu);
	cudaEventSynchronize(stop_gpu);

	float duration_gpu = 0;
	cudaEventElapsedTime(&duration_gpu, start_gpu, stop_gpu);
	cudaError_t err = cudaGetLastError();
	std::cout << std::endl << "Kernel launch status: " << cudaGetErrorString(err) << std::endl;
	std::cout << "[GPU] Execution Time: " << duration_gpu << " ms" << std::endl << std::endl;

	// cudaDeviceSynchronize();															// waith for GPU to finish

	cudaMemcpy(h_c, d_c, size, cudaMemcpyDeviceToHost);

	bool success{true};
	for(int i=0; i<dim; i++)
	{
		if( h_c[i] != 3.0f )
		{
			success = false;
			break;
		}
	}

	if(success)
	{
		std::cout << "2D Matrix addition was successful!" << std::endl;
	}
	else
	{
		std::cout << "2D Matrix addition failed!" << std::endl;
	}

	cudaFree(d_a);
	cudaFree(d_b);
	cudaFree(d_c);
	free(h_a);
	free(h_b);
	free(h_c);

	return 0;
}
