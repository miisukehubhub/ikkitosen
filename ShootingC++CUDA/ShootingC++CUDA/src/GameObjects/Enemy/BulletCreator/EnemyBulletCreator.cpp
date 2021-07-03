#include "EnemyBulletCreator.h"

#include <cmath>

#include "../Enemy.h"
#include "../../Player/Player.h"
#include "../../EnemyBullet/EnemyBullet.h"

void EnemyBulletCreator::Run()
{
	for (int i = 0; i < EnemyPtr::length; i++)
	{
		// 弾を打てないときはスキップ
		if ((EnemyPtr::host[i].m_state & (unsigned char)EnemyState::canFire) == 0) continue;

		if (EnemyPtr::host[i].m_kind == EnemyKind::SoftEnemy)
		{
			EnemyBulletPtr::host[EnemyBulletPtr::length] =
				EnemyBullet(EnemyPtr::host[i].m_position,
					Vector2::normalize(PlayerPtr::host->GetPosition() - EnemyPtr::host[i].m_position) * 7.0f,
					0.1f);
			// 要素数を増やす
			EnemyBulletPtr::length++;
		}
		else if (EnemyPtr::host[i].m_kind == EnemyKind::HardEnemy)
		{
			EnemyBulletPtr::host[EnemyBulletPtr::length] =
				EnemyBullet(EnemyPtr::host[i].m_position,
					Vector2::normalize(PlayerPtr::host->GetPosition() - EnemyPtr::host[i].m_position) * 5.0f,
					0.2f);
			// 要素数を増やす
			EnemyBulletPtr::length++;
		}
		else if (EnemyPtr::host[i].m_kind == EnemyKind::MetalEnemy)
		{
			for (int j = 0; j < 3; j++)
			{
				// 前方に15度の幅で3つ弾を発射する
				float angle = (3.14159265f / 12.0f) * (11 + j);
				EnemyBulletPtr::host[EnemyBulletPtr::length] =
					EnemyBullet(EnemyPtr::host[i].m_position,
						Vector2(std::cosf(angle), std::sinf(angle)) * 4.0f,
						0.4f);
				// 要素数を増やす
				EnemyBulletPtr::length++;
			}
		}
	}
}