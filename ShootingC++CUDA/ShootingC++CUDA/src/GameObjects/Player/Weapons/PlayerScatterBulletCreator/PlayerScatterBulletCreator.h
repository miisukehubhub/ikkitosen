#ifndef PLAYERSCATTERBULLETCREATOR_H_
#define PLAYERSCATTERBULLETCREATOR_H_

#include "../../../../GameManager/GameManager.h"

#include "../PlayerWeapon.h"

class PlayerScatterBulletCreator : public PlayerWeapon
{
public:

	PlayerScatterBulletCreator() = default; // �R���X�g���N�^

	~PlayerScatterBulletCreator() = default; // �f�X�g���N�^

	void Update() override; // �X�V����

private:

	GameManager& gm = GameManager::GetInstance();

private:

	short m_playSoundIntervalTimeFrame{ 3 };

	short  m_playSoundIntervalTimer{ 0 };
};

#endif