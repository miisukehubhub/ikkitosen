#include "EnemyCollisionDetectionKernel.cuh"

#include "../../../MyMath/MyMath.h"

#include "../../PlayerBullets/PlayerNormalBullet/PlayerNormalBullet.h"
#include "../../PlayerBullets/PlayerScatterBullet/PlayerScatterBullet.h"

__global__ void EnemyCollisionDetectionKernel::Process(Enemy* ePtr, int eLength, PlayerNormalBullet* pnbPtr, int pnbLength, PlayerScatterBullet* psbPtr, int psbLength)
{
	 // スレッド番号を取得
	int idx = blockDim.x * blockIdx.x + threadIdx.x;

	// 存在しない要素は処理を行わない
	if (idx >= eLength) return;
	
	for (int i = 0; i < pnbLength; i++)
	{
		// 敵が死んでいたら終了
		if ((ePtr[idx].m_state & (unsigned char)EnemyState::IsDead) != 0) return;

		if (MyMath::CircleCircleIntersection(ePtr[idx].m_position, ePtr[idx].m_collisionRadius,
											  pnbPtr[i].m_position, pnbPtr[i].m_collisionRadius))
		{
			int damage = pnbPtr[i].m_power / (ePtr[idx].m_defenceLevel + 1);
			ePtr[idx].m_hp -= damage;
			if (damage > 0) ePtr[idx].m_state |= (unsigned char)EnemyState::IsDamage;

			if (ePtr[idx].m_hp < 0)
			{
				ePtr[idx].m_state |= (unsigned char)EnemyState::IsDead;
			}
		}
	}

	for (int i = 0; i < psbLength; i++)
	{
		// 敵が死んでいたら終了
		if ((ePtr[idx].m_state & (unsigned char)EnemyState::IsDead) != 0) return;

		if (MyMath::CircleCircleIntersection(ePtr[idx].m_position, ePtr[idx].m_collisionRadius,
			psbPtr[i].m_position, psbPtr[i].m_collisionRadius))
		{
			int damage = pnbPtr[i].m_power / (ePtr[idx].m_defenceLevel + 1);
			ePtr[idx].m_hp -= damage;
			if (damage > 0) ePtr[idx].m_state |= (unsigned char)EnemyState::IsDamage;
			psbPtr[i].m_isDead = true;

			if (ePtr[idx].m_hp < 0)
			{
				ePtr[idx].m_state |= (unsigned char)EnemyState::IsDead;
			}
		}
	}

	return;
}