#include "PlayerScatterBulletUpdater.h"

#include <cuda_runtime.h>

#include "../PlayerScatterBullet.h"
#include "PlayerScatterBulletUpdaterKernel.cuh"

void PlayerScatterBulletUpdater::Run()
{
	int length = PlayerScatterBulletPtr::length;

	// CPUからGPUにデータを転送
	cudaMemcpyAsync(
		PlayerScatterBulletPtr::device,
		PlayerScatterBulletPtr::host,
		sizeof(PlayerScatterBullet) * length,
		cudaMemcpyHostToDevice,
		PlayerScatterBulletPtr::stream);

	dim3 block(256, 1, 1);
	dim3 grid((length + 256 - 1) / 256, 1, 1);

	// プレイヤー散弾更新カーネル実行
	PlayerScatterBulletUpdaterKernel::Process << <grid, block, 0, PlayerScatterBulletPtr::stream >> > (PlayerScatterBulletPtr::device, length);

	// GPUからCPUにデータを転送
	cudaMemcpyAsync(
		PlayerScatterBulletPtr::host,
		PlayerScatterBulletPtr::device,
		sizeof(PlayerScatterBullet) * length,
		cudaMemcpyDeviceToHost,
		PlayerScatterBulletPtr::stream);
}