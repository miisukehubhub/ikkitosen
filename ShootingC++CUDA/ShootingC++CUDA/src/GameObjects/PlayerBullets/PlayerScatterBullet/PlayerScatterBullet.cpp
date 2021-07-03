#include "PlayerScatterBullet.h"

#include <cmath>
#include "../../../MyMemory/MyMemory.h"

PlayerScatterBullet::PlayerScatterBullet(Vector2 position, float angle)
	:m_position(position)
{
	m_speed.x = std::cosf(angle) * 10.0f;
	m_speed.y = std::sinf(angle) * 10.0f;
}

// namespace PlayerScatterBulletPtr

PlayerScatterBullet* PlayerScatterBulletPtr::host;
PlayerScatterBullet* PlayerScatterBulletPtr::device;
int PlayerScatterBulletPtr::maxLength = 1024 * 2;
int PlayerScatterBulletPtr::length = 0;
cudaStream_t PlayerScatterBulletPtr::stream;

void PlayerScatterBulletPtr::Get()
{
	host = (PlayerScatterBullet*)MyMemory::hostPtr;
	MyMemory::hostPtr = (void*)&host[maxLength];
	device = (PlayerScatterBullet*)MyMemory::devicePtr;
	MyMemory::devicePtr = (void*)&device[maxLength];
	MyMemory::usingSize += sizeof(PlayerScatterBullet) * maxLength;

	cudaStreamCreate(&stream);
}

void PlayerScatterBulletPtr::Init()
{
	length = 0;
	cudaStreamDestroy(stream);
}

void PlayerScatterBulletPtr::EraseRemoveIfIsDead()
{
	int newLength = 0;
	for (int i = 0; i < length; i++)
	{
		if (host[i].m_isDead) continue;

		memcpy(
			(void*)&host[newLength],
			(void*)&host[i],
			sizeof(PlayerScatterBullet));

		// —v‘f‚ð‘‚â‚·
		newLength++;
	}

	// —v‘f”‚ðŠm’è‚·‚é
	length = newLength;
}