#ifndef PLAYERNORMALBULLET_H_
#define PLAYERNORMALBULLET_H_

#include <cmath>
#include <DxLib.h>
#include <cuda_runtime.h>

#include "../../../Vector2/Vector2.h"
#include "../../../Screen/Screen.h"

class PlayerNormalBullet
{
public:

	PlayerNormalBullet(Vector2 position); // �R���X�g���N�^

public:

	Vector2 m_position{ Vector2_v::zero };
	Vector2 m_speed{ Vector2(30.0f, 0) };
	short m_power{ 120 };
	bool m_isDead{ false };
	short m_visibleRadius{ 64 };
	float m_collisionRadius{ 60.f };
};

namespace PlayerNormalBulletPtr
{
	extern PlayerNormalBullet* host; // CPU���̃������̃A�h���X
	extern PlayerNormalBullet* device; // GPU���̃������̃A�h���X
	extern int maxLength; // �ő�v�f��
	extern int length; // �v�f��
	extern cudaStream_t stream; // PlayerNOrmalBullet�Ɋւ��鏈�����s���X�g���[��

	// PlayerNormalBulletPtr���g�p����A�h���X���擾
	void Get();

	// �������A�|��
	void Init();

	// �폜����
	void EraseRemoveIfIsDead();
}

#endif