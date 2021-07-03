#include "EnemyDrawer.h"

#include <DxLib.h>

#include "../../../Image/Image.h"

#include "../Enemy.h"

void EnemyDrawer::Run()
{
	auto ptr = EnemyPtr::host;
	for (int i = 0; i < EnemyPtr::length; i++)
	{
		DrawGraphF(ptr[i].m_position.x, ptr[i].m_position.y, Image::At((unsigned char)PlaySceneImageID::Enemy), TRUE);
	}
}