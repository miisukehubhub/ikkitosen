#include "EnemyBulletUpdater.h"

#include <cuda_runtime.h>

#include "../EnemyBullet.h"
#include "EnemyBulletUpdaterKernel.cuh"

void EnemyBulletUpdater::Run()
{
	int length = EnemyBulletPtr::length;

	// CPUからGPUにデータを転送
	cudaMemcpyAsync(
		EnemyBulletPtr::device,
		EnemyBulletPtr::host,
		sizeof(EnemyBullet) * length,
		cudaMemcpyHostToDevice,
		EnemyBulletPtr::stream);

	dim3 block(256, 1, 1);
	dim3 grid((length + 256 - 1) / 256, 1, 1);

	// 敵弾更新カーネル実行
	EnemyBulletUpdaterKernel::Process << <grid, block, 0, EnemyBulletPtr::stream >> > (EnemyBulletPtr::device, length);

	// GPUからCPUにデータを転送
	cudaMemcpyAsync(
		EnemyBulletPtr::host,
		EnemyBulletPtr::device,
		sizeof(EnemyBullet) * length,
		cudaMemcpyDeviceToHost,
		EnemyBulletPtr::stream);
}