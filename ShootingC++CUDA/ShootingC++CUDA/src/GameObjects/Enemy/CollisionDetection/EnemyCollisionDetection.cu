#include "EnemyCollisionDetection.h"

#include <cuda_runtime.h>

#include "../Enemy.h"
#include "EnemyCollisionDetectionKernel.cuh"
#include "../../PlayerBullets/PlayerNormalBullet/PlayerNormalBullet.h"
#include "../../PlayerBullets/PlayerScatterBullet/PlayerScatterBullet.h"

void EnemyCollisionDetection::Run()
{
	int eLength = EnemyPtr::length;
	int pnbLength = PlayerNormalBulletPtr::length;
	int psbLength = PlayerScatterBulletPtr::length;

	dim3 block(256, 1, 1);
	dim3 grid((eLength + 256 - 1) / 256 * 4, 1, 1);

	// 敵の当たり判定カーネルを実行
	EnemyCollisionDetectionKernel::Process << <grid, block, 0, EnemyPtr::stream >> > (EnemyPtr::device, eLength, PlayerNormalBulletPtr::device, pnbLength, PlayerScatterBulletPtr::device, psbLength);

	// GPUからCPUにデータを転送
	cudaMemcpyAsync(
		EnemyPtr::host,
		EnemyPtr::device,
		sizeof(Enemy) * eLength,
		cudaMemcpyDeviceToHost,
		EnemyPtr::stream);

	cudaMemcpyAsync(
		PlayerNormalBulletPtr::host,
		PlayerNormalBulletPtr::device,
		sizeof(PlayerNormalBullet) * pnbLength,
		cudaMemcpyDeviceToHost,
		EnemyPtr::stream);

	cudaMemcpyAsync(
		PlayerScatterBulletPtr::host,
		PlayerScatterBulletPtr::device,
		sizeof(PlayerScatterBullet) * psbLength,
		cudaMemcpyDeviceToHost,
		EnemyPtr::stream);
}