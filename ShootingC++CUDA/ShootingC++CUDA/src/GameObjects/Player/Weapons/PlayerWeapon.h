#ifndef WEAPON_H_
#define WEAPON_H_

// �v���C���[�̕���̊��N���X
class PlayerWeapon
{
public:

	PlayerWeapon() = default; // �R���X�g���N�^

	virtual ~PlayerWeapon() = default; // �f�X�g���N�^

	virtual void Update() = 0; //	�X�V����
};

#endif