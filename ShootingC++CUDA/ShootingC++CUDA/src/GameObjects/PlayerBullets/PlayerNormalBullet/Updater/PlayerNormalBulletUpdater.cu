#include "PlayerNormalBulletUpdater.h"

#include <cuda_runtime.h>

#include "../PlayerNormalBullet.h"
#include "PlayerNormalBulletUpdaterKernel.cuh"

void PlayerNormalBulletUpdater::Run()
{
	int length = PlayerNormalBulletPtr::length;

	// CPUからGPUにデータを転送
	cudaMemcpyAsync(
		PlayerNormalBulletPtr::device,
		PlayerNormalBulletPtr::host,
		sizeof(PlayerNormalBullet) * length,
		cudaMemcpyHostToDevice,
		PlayerNormalBulletPtr::stream);

	dim3 block(256, 1, 1);
	dim3 grid((length + 256 - 1) / 256, 1, 1);

	// プレイヤー通常弾更新カーネルを実行
	PlayerNormalBulletUpdaterKernel::Process << <grid, block, 0, PlayerNormalBulletPtr::stream >> > (PlayerNormalBulletPtr::device, length);

	// GPUからCPUにデータを転送
	cudaMemcpyAsync(
		PlayerNormalBulletPtr::host,
		PlayerNormalBulletPtr::device,
		sizeof(PlayerNormalBullet) * length,
		cudaMemcpyDeviceToHost,
		PlayerNormalBulletPtr::stream);
}