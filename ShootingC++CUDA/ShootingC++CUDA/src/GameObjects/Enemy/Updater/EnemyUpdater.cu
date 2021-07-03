#include "EnemyUpdater.h"

#include <cuda_runtime.h>

#include "../Enemy.h"
#include "EnemyUpdaterKernel.cuh"

void EnemyUpdater::Run()
{
	int length = EnemyPtr::length;

	// CPUからGPUにデータを転送
	cudaMemcpyAsync(
		EnemyPtr::device,
		EnemyPtr::host,
		sizeof(Enemy) * length,
		cudaMemcpyHostToDevice,
		EnemyPtr::stream);

	dim3 block(256, 1, 1);
	dim3 grid((length + 256 - 1) / 256, 1, 1);

	// 敵の更新カーネルを実行
	EnemyUpdaterKernel::Process << <grid, block, 0, EnemyPtr::stream >> > (EnemyPtr::device, length);

	// GPUからCPUにデータを転送
	cudaMemcpyAsync(
		EnemyPtr::host,
		EnemyPtr::device,
		sizeof(Enemy) * length,
		cudaMemcpyDeviceToHost,
		EnemyPtr::stream);
}