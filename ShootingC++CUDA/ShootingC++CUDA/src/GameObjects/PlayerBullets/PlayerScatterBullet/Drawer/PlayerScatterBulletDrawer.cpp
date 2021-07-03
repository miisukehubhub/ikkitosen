#include "PlayerScatterBulletDrawer.h"

#include "../PlayerScatterBullet.h"
#include "../../../../Image/Image.h"

void PlayerScatterBulletDrawer::Run()
{
	auto ptr = PlayerScatterBulletPtr::host;
	for (int i = 0; i < PlayerScatterBulletPtr::length; i++)
	{
		DrawRotaGraph3F(ptr[i].m_position.x, ptr[i].m_position.y, 16.0f, 16.0f, 0.5f, 0.25f, 0, Image::At((unsigned char)PlaySceneImageID::PlayerScatterBullet), TRUE);
	}
}