#ifndef PLAYERNORMALBULLETCREATOR_H_
#define PLAYERNORMALBULLETCREATOR_H_

#include "../../../../GameManager/GameManager.h"

#include "../PlayerWeapon.h"

class PlayerNormalBulletCreator : public PlayerWeapon
{
public:

	PlayerNormalBulletCreator() = default;  // コンストラクタ

	~PlayerNormalBulletCreator() = default; // デストラクタ

	void Update() override; // 更新処理

private:

	GameManager& gm = GameManager::GetInstance();

private:

	short m_createIntervalTimeFrame{ 60 };

	short m_createIntervalTimer{ 0 };
};

#endif