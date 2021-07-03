#include "PlayerNormalBulletDrawer.h"

#include "../PlayerNormalBullet.h"
#include "../../../../Image/Image.h"

void PlayerNormalBulletDrawer::Run()
{
	auto ptr = PlayerNormalBulletPtr::host;
	for (int i = 0; i < PlayerNormalBulletPtr::length; i++)
	{
		DrawRotaGraphF(ptr[i].m_position.x, ptr[i].m_position.y, 2.0f, 0.0f, Image::At((unsigned char)PlaySceneImageID::PlayerNormalBullet), TRUE);
	}
}