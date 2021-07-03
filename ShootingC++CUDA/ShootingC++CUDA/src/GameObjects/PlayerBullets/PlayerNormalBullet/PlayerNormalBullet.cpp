#include "PlayerNormalBullet.h"

#include <cmath>
#include "../../../MyMemory/MyMemory.h"

PlayerNormalBullet::PlayerNormalBullet(Vector2 position)
	:m_position(position)
{
	
}

// namespace PlayerNormalBulletPtr

PlayerNormalBullet* PlayerNormalBulletPtr::host;
PlayerNormalBullet* PlayerNormalBulletPtr::device;
int PlayerNormalBulletPtr::maxLength = 16;
int PlayerNormalBulletPtr::length = 0;
cudaStream_t PlayerNormalBulletPtr::stream;

void PlayerNormalBulletPtr::Get()
{
	host = (PlayerNormalBullet*)MyMemory::hostPtr;
	MyMemory::hostPtr = (void*)&host[maxLength];
	device = (PlayerNormalBullet*)MyMemory::devicePtr;
	MyMemory::devicePtr = (void*)&device[maxLength];
	MyMemory::usingSize += sizeof(PlayerNormalBullet) * maxLength;

	cudaStreamCreate(&stream);
}

void PlayerNormalBulletPtr::Init()
{
	length = 0;
	cudaStreamDestroy(stream);
}

void PlayerNormalBulletPtr::EraseRemoveIfIsDead()
{
	int newLength = 0;
	for (int i = 0; i < length; i++)
	{
		if (host[i].m_isDead) continue;

		memcpy(
			(void*)&host[newLength],
			(void*)&host[i],
			sizeof(PlayerNormalBullet));

		// V‚µ‚¢—v‘f‚ð‘‚â‚·
		newLength++;
	}

	// —v‘f”‚ðŠm’è‚·‚é
	length = newLength;
}