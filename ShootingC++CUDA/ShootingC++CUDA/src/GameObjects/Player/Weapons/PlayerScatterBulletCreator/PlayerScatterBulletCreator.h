#ifndef PLAYERSCATTERBULLETCREATOR_H_
#define PLAYERSCATTERBULLETCREATOR_H_

#include "../../../../GameManager/GameManager.h"

#include "../PlayerWeapon.h"

class PlayerScatterBulletCreator : public PlayerWeapon
{
public:

	PlayerScatterBulletCreator() = default; // コンストラクタ

	~PlayerScatterBulletCreator() = default; // デストラクタ

	void Update() override; // 更新処理

private:

	GameManager& gm = GameManager::GetInstance();

private:

	short m_playSoundIntervalTimeFrame{ 3 };

	short  m_playSoundIntervalTimer{ 0 };
};

#endif