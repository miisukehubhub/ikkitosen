#include "EnemyBulletUpdaterKernel.cuh"

#include "../../../Screen/Screen.h"

__global__ void EnemyBulletUpdaterKernel::Process(EnemyBullet* ebPtr, int length)
{
	int idx = blockDim.x * blockIdx.x + threadIdx.x;

	if (idx >= length) return;
	// 移動
	ebPtr[idx].m_position += ebPtr[idx].m_speed;

	// 画面外に出たら死亡
	if (ebPtr[idx].m_position.x > Screen::Width + ebPtr[idx].m_collisionRadius ||
		ebPtr[idx].m_position.x < -ebPtr[idx].m_collisionRadius ||
		ebPtr[idx].m_position.y > Screen::Height + ebPtr[idx].m_collisionRadius ||
		ebPtr[idx].m_position.y < -ebPtr[idx].m_collisionRadius) ebPtr[idx].m_isDead = true;
	return;
}