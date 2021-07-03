#include "EnemyUpdaterKernel.cuh"

#include <math.h>

#include "../../../Screen/Screen.h"
#include "../EnemyKind.h"
#include "../../Player/Player.h"

__global__ void EnemyUpdaterKernel::Process(Enemy* ePtr, int length)
{
	// スレッド番号の取得
	int idx = blockDim.x * blockIdx.x + threadIdx.x;

	// 存在しない要素は処理を行わない
	if (idx >= length) return;

	ePtr[idx].m_state &= ~(unsigned char)EnemyState::IsDamage;
	ePtr[idx].m_state &= ~(unsigned char)EnemyState::canFire;

	if (ePtr[idx].m_kind == EnemyKind::SoftEnemy) SoftEnemyUpdate(&ePtr[idx]);
	if (ePtr[idx].m_kind == EnemyKind::HardEnemy) HardEnemyUpdate(&ePtr[idx]);
	if (ePtr[idx].m_kind == EnemyKind::MetalEnemy) MetalEnemyUpdate(&ePtr[idx]);

	if (ePtr[idx].m_position.x < -ePtr[idx].m_collisionRadius)
	{
		// 画面外に出ての死亡はスコアが入らないようにする
		ePtr[idx].m_state |= (unsigned char)EnemyState::IsDead;
		ePtr[idx].m_score = 0;
	}
	return;
}

__device__ void EnemyUpdaterKernel::SoftEnemyUpdate(Enemy* ePtr)
{
	ePtr->m_angle += 0.05f;

	ePtr->m_basePosition += ePtr->m_speed;
	ePtr->m_position = ePtr->m_basePosition;
	ePtr->m_position.y += sinf(ePtr->m_angle) * 30.0f;

	if (ePtr->m_bulletFireIntervalTimer > 0)
	{
		ePtr->m_bulletFireIntervalTimer--;
		return;
	}

	ePtr->m_state |= (unsigned char)EnemyState::canFire;
	ePtr->m_bulletFireIntervalTimer = ePtr->m_bulletFireIntervalTimeFrame;
}

__device__ void EnemyUpdaterKernel::HardEnemyUpdate(Enemy* ePtr)
{
	ePtr->m_angle += 0.05f;

	ePtr->m_basePosition += ePtr->m_speed;
	ePtr->m_position = ePtr->m_basePosition;
	ePtr->m_position.x += cosf(ePtr->m_angle) * 20.0f;

	if (ePtr->m_bulletFireIntervalTimer > 0)
	{
		ePtr->m_bulletFireIntervalTimer--;
		return;
	}

	ePtr->m_state |= (unsigned char)EnemyState::canFire;
	ePtr->m_bulletFireIntervalTimer = ePtr->m_bulletFireIntervalTimeFrame;
}

__device__ void EnemyUpdaterKernel::MetalEnemyUpdate(Enemy* ePtr)
{
	ePtr->m_angle += 0.03f;

	ePtr->m_basePosition += ePtr->m_speed;
	ePtr->m_position = ePtr->m_basePosition;
	ePtr->m_position.x += cosf(ePtr->m_angle) * 32.0f;
	ePtr->m_position.y += sinf(ePtr->m_angle) * 32.0f;

	if (ePtr->m_bulletFireIntervalTimer > 0)
	{
		ePtr->m_bulletFireIntervalTimer--;
		return;
	}

	ePtr->m_state |= (unsigned char)EnemyState::canFire;
	ePtr->m_bulletFireIntervalTimer = ePtr->m_bulletFireIntervalTimeFrame;
}