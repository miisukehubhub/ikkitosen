#include "PlayerScatterBulletUpdaterKernel.cuh"

#include "../../../../Screen/Screen.h"

__global__ void PlayerScatterBulletUpdaterKernel::Process(PlayerScatterBullet* psbPtr, int length)
{
	int idx = blockDim.x * blockIdx.x + threadIdx.x;

	if (idx >= length) return;

	psbPtr[idx].m_position += psbPtr[idx].m_speed; // 移動

	if (psbPtr[idx].m_position.x > Screen::Width + psbPtr[idx].m_visibleRadius ||
		psbPtr[idx].m_position.y < 0 - psbPtr[idx].m_visibleRadius ||
		psbPtr[idx].m_position.y > Screen::Height + psbPtr[idx].m_visibleRadius)
	{
		psbPtr[idx].m_isDead = true;
	}
	return;
}