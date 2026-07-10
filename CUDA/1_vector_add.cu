#include <iostream>
#include <cuda_runtime.h>

// Adding 2 1D-arrays using the GPU
// c = a + b
// Host: CPU
// Device: GPU

__global__ void addVectors(int n, float* a, float* b, float* c)			// __global__ keyword means all the threads in the GPU can access this
{
    int i = blockIdx.x * blockDim.x + threadIdx.x;						// Idx arguments are passed to each thread by default; formula for calculating index of thread in the entire thread pool (threadIdx give index within the block)
																		// here 'i' is a local variable (specific to each individual thread- register memory)

	if(i < n)															// since number of threads is more than data size, extra threads should not access the data
	{
		c[i] = a[i] + b[i];												// each thread adds its corresponding data byte and puts it into 'c'
	}
}

int main()
{
	int N = 50000;									// Size of each array 
	size_t size = N * sizeof(float);

	float *h_a = (float *)malloc(size);				// Array 'a' on Host
	float *h_b = (float *)malloc(size);				// Array 'b' on Host
	float *h_c = (float *)malloc(size);				// Result array on Host

	for(int i=0; i<N; i++)
	{
		h_a[i] = 1.0f;								// Storing 1.0f in 'a' and 2.0f in 'b'
		h_b[i] = 2.0f;
	}

	float *d_a, *d_b, *d_c;							// Declaring arrays on the Device
	cudaMalloc((void **)&d_a, size);				// Allocating arrays on the Device
	cudaMalloc((void **)&d_b, size);				// The first argument for cudaMalloc() is a void** to accept all types of pointers, hence float pointers need to be casted to void**
	cudaMalloc((void **)&d_c, size);				// cudaMalloc() will ask the GPU to allocate memory in the VRAM and then will store the address of the allocated memory in *d_a on CPU,
													// so that CPU knows the address the array is on the GPU. It is needed later.

	cudaMemcpy(d_a, h_a, size, cudaMemcpyHostToDevice);		// copy data from CPU (h_a) to GPU (d_a)
	cudaMemcpy(d_b, h_b, size, cudaMemcpyHostToDevice);

	int threadsPerBlock = 256;											// should be in multiples of 32; by default use 256 and reduce or increase if required; max 1024 / block
	int blocksPerGrid = (N + threadsPerBlock - 1) / threadsPerBlock;	// (data size) / threadsPerBlock gives total blocks required; formula used here always rounds up the decimal place so, 
																		// eg- 5000/256 = 19.5 {total number of threads (256*19) is less than data- not good}
																		// (5000+256-1)/256 = 20.5 {total number of threads (256*20) is more than data- good}
	std::cout << "Launching GPU Kernel with " << blocksPerGrid << " blocks of " << threadsPerBlock << " threads..." << std::endl;
	addVectors<<<blocksPerGrid, threadsPerBlock>>>(N, d_a, d_b, d_c);		// launch GPU kernel
	cudaError_t err = cudaGetLastError();									// check status of kernel launch
	std::cout << "Kernel launch status: " << cudaGetErrorString(err) << std::endl;

	cudaDeviceSynchronize();												// CPU waits for GPU to finish the execution

	cudaMemcpy(h_c, d_c, size, cudaMemcpyDeviceToHost);						// copy data from device to host

	bool success = true;
	for(int i=0; i<N; i++)													// check if data is correct
	{
		if(h_c[i] != 3.0f)
		{
			success = false;
			break;
		}
	}

	if(success)
	{
		std::cout << "Success " << N << " elements added successfully on the GPU" << std::endl;
	}
	else
	{
		std::cout << "Failed to add elements on the GPU" << std::endl;
	}

	cudaFree(d_a);															// free all memory
	cudaFree(d_b);
	cudaFree(d_c);
	free(h_a);
	free(h_b);
	free(h_c);

	return 0;
}
