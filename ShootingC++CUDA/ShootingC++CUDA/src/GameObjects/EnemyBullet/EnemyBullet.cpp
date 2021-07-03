#include "EnemyBullet.h"

#include <cmath>
#include "../../MyMemory/MyMemory.h"

EnemyBullet::EnemyBullet(Vector2 position, Vector2 speed, float sizeRate)
	:m_position(position)
	,m_speed(speed)
	,m_sizeRate(sizeRate)
{
	m_collisionRadius *= sizeRate;
}

// namespace EnemyBulletPtr

EnemyBullet* EnemyBulletPtr::host;
EnemyBullet* EnemyBulletPtr::device;
int EnemyBulletPtr::maxLength = 1024 * 16;
int EnemyBulletPtr::length = 0;
cudaStream_t EnemyBulletPtr::stream;

void EnemyBulletPtr::Get()
{
	host = (EnemyBullet*)MyMemory::hostPtr;
	MyMemory::hostPtr = (void*)&host[maxLength];
	device = (EnemyBullet*)MyMemory::devicePtr;
	MyMemory::devicePtr = (void*)&device[maxLength];
	MyMemory::usingSize += sizeof(EnemyBullet) * maxLength;

	cudaStreamCreate(&stream);
}

void EnemyBulletPtr::Init()
{
	length = 0;
	cudaStreamDestroy(stream);
}

void EnemyBulletPtr::EraseRemoveIfIsDead()
{
	int newLength = 0;
	for (int i = 0; i < length; i++)
	{
		if (host[i].m_isDead) continue;

		memcpy(
			(void*)&host[newLength],
			(void*)&host[i],
			sizeof(EnemyBullet));

		// V‚µ‚¢—v‘f”‚ð‘‚â‚·
		newLength++;
	}

	// —v‘f”‚ðŠm’è
	length = newLength;
}