#include "EnemyBulletDrawer.h"

#include "../EnemyBullet.h"

void EnemyBulletDrawer::Run()
{
	auto ptr = EnemyBulletPtr::host;
	for (int i = 0; i < EnemyBulletPtr::length; i++)
	{
		DrawCircleAA(ptr[i].m_position.x, ptr[i].m_position.y, ptr[i].m_collisionRadius, 16, (255 << 16) + 255, TRUE);
	}
}