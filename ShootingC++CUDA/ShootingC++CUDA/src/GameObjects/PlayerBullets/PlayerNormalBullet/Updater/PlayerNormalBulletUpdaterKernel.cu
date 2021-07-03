#include "PlayerNormalBulletUpdaterKernel.cuh"

#include "../../../../Screen/Screen.h"

__global__ void PlayerNormalBulletUpdaterKernel::Process(PlayerNormalBullet* pnbPtr, int length)
{
	int idx = blockDim.x * blockIdx.x + threadIdx.x;

	if (idx >= length) return;

	pnbPtr[idx].m_position += pnbPtr[idx].m_speed; // 移動

	// 画面の右端を超えたら死亡
	if (pnbPtr[idx].m_position.x > Screen::Width + pnbPtr[idx].m_visibleRadius) pnbPtr[idx].m_isDead = true;
	return;
}