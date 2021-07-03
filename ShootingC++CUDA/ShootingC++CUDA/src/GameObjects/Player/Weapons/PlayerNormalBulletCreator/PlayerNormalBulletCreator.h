#ifndef PLAYERNORMALBULLETCREATOR_H_
#define PLAYERNORMALBULLETCREATOR_H_

#include "../../../../GameManager/GameManager.h"

#include "../PlayerWeapon.h"

class PlayerNormalBulletCreator : public PlayerWeapon
{
public:

	PlayerNormalBulletCreator() = default;  // �R���X�g���N�^

	~PlayerNormalBulletCreator() = default; // �f�X�g���N�^

	void Update() override; // �X�V����

private:

	GameManager& gm = GameManager::GetInstance();

private:

	short m_createIntervalTimeFrame{ 60 };

	short m_createIntervalTimer{ 0 };
};

#endif