#include "MyMemory.h"

#include <cuda_runtime.h>

void* MyMemory::baseHostPtr;
void* MyMemory::hostPtr;
void* MyMemory::baseDevicePtr;
void* MyMemory::devicePtr;
size_t MyMemory::mallocSize = 1024 * 1024;
size_t MyMemory::usingSize = 0;

void MyMemory::Malloc()
{
	cudaMallocHost(&baseHostPtr, mallocSize);
	hostPtr = baseHostPtr;
	cudaMalloc(&baseDevicePtr, mallocSize);
	devicePtr = baseDevicePtr;
}

void MyMemory::Free()
{
	cudaFree(baseDevicePtr);
	cudaFreeHost(baseHostPtr);
	usingSize = 0;
}