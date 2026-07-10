#include <iostream>
#include <chrono>
#include <cuda_runtime.h>

__global__ void addVectorsGPU(int N, float *a, float *b, float *c)			// GPU function for adding two arrays
{
	int idx = blockIdx.x * blockDim.x + threadIdx.x;

	if(idx < N)
	{
		c[idx] = a[idx] + b[idx];
	}
}

void addVectorsCPU(int N, float *a, float *b, float *c)						// CPU function for adding two arrays
{
	for(int i=0; i<N; i++)
	{
		c[i] = a[i] + b[i];
	}
}

int main()
{
	int N = 20000000;														// very large data size
	size_t size = N * sizeof(float);

	float *h_a = new float[N];
	float *h_b = new float[N];
	float *h_c_cpu = new float[N];
	float *h_c_gpu = new float[N];

	for(int i=0; i<N; i++)
	{
		h_a[i] = 1.0f;
		h_b[i] = 2.0f;
	}

	float *d_a, *d_b, *d_c;
	cudaMalloc((void **)&d_a, size);
	cudaMalloc((void **)&d_b, size);
	cudaMalloc((void **)&d_c, size);

	cudaMemcpy(d_a, h_a, size, cudaMemcpyHostToDevice);
	cudaMemcpy(d_b, h_b, size, cudaMemcpyHostToDevice);

	std::cout << "Starting Benchmark for " << N << " elements..." << std::endl;
	std::cout << "-------------------------------------------------" << std::endl;

	// CPU Benchmark
	auto start_cpu = std::chrono::high_resolution_clock::now();									// start clock before adding the two arrays

	addVectorsCPU(N, h_a, h_b, h_c_cpu);

	auto end_cpu = std::chrono::high_resolution_clock::now();									// stop clock after adding the two arrays
	std::chrono::duration<float, std::milli> duration_cpu = end_cpu - start_cpu;				// calculate the difference in the two times
	std::cout << "[CPU] Execution Time: " << duration_cpu.count() << " ms" << std::endl;

	// GPU Benchmark
	int threadsPerBlock = 256;
	int blocksPerGrid = ( N + threadsPerBlock - 1 ) / threadsPerBlock;

	cudaEvent_t start_gpu, stop_gpu;															// hardware stopwatch to time GPU execution
	cudaEventCreate(&start_gpu);																// init
	cudaEventCreate(&stop_gpu);

	cudaEventRecord(start_gpu);																	// start timer
	addVectorsGPU<<<blocksPerGrid, threadsPerBlock>>>(N, d_a, d_b, d_c);
	cudaEventRecord(stop_gpu);																	// stop timer

	cudaEventSynchronize(stop_gpu);																// CPU waits till stop_timer is recorded
	cudaError_t err = cudaGetLastError();
	std::cout << std::endl << "Kernel launch status: " << cudaGetErrorString(err) << std::endl;

	float duration_gpu = 0;
	cudaEventElapsedTime(&duration_gpu, start_gpu, stop_gpu);
	std::cout << "[GPU] Execution Time: " << duration_gpu << " ms" << std::endl;
	std::cout << "-------------------------------------------------" << std::endl;

	cudaMemcpy(h_c_gpu, d_c, size, cudaMemcpyDeviceToHost);
	cudaEventDestroy(start_gpu);
	cudaEventDestroy(stop_gpu);

	cudaFree(d_a);
	cudaFree(d_b);
	cudaFree(d_c);
	delete[] h_a;
	delete[] h_b;
	delete[] h_c_cpu;
	delete[] h_c_gpu;

	return 0;
}
