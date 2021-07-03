#ifndef PLAYERSCATTERBULLET_H_
#define PLAYERSCATTERBULLET_H_

#include <DxLib.h>
#include <cuda_runtime.h>

#include "../../../Vector2/Vector2.h"
#include "../../../Screen/Screen.h"

class PlayerScatterBullet
{
public:

	PlayerScatterBullet(Vector2 position, float angle); // �R���X�g���N�^

public:

	Vector2 m_position{ Vector2_v::zero };
	Vector2 m_speed{ Vector2_v::zero };
	short m_power{ 4 };
	bool m_isDead{ false };
	short m_visibleRadius{ 8 };
	float m_collisionRadius{ 4.0f };
};

namespace PlayerScatterBulletPtr
{
	extern PlayerScatterBullet* host; // CPU���̃������̃A�h���X
	extern PlayerScatterBullet* device; // GPU���̃������̃A�h���X
	extern int maxLength; // �ő�v�f��
	extern int length; // �v�f��
	extern cudaStream_t stream; // PlayerScatterBullet�Ɋ֌W���鏈�����s���X�g���[��

	// PlayerScatterBulletPtr���g�p����A�h���X���擾����
	void Get();

	// �������A�|��
	void Init();

	// �폜����
	void EraseRemoveIfIsDead();
}

#endif
