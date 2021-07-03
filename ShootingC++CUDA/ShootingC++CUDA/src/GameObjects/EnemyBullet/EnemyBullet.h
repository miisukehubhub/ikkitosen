#ifndef ENEMYBULLET_H_
#define ENEMYBULLET_H_

#include <cmath>
#include <DxLib.h>
#include <cuda_runtime.h>

#include "../../Vector2/Vector2.h"
#include "../../Screen/Screen.h"

class EnemyBullet
{
public:

	EnemyBullet(Vector2 position, Vector2 speed, float sizeRate); // �R���X�g���N�^

public:

	Vector2 m_position{ Vector2_v::zero };
	Vector2 m_speed{ Vector2_v::zero };
	bool m_isDead{ false };
	float m_collisionRadius{ 8.0f };
	float m_sizeRate{ 1.0f };
};

namespace EnemyBulletPtr
{
	extern EnemyBullet* host; // CPU���̃������̃A�h���X
	extern EnemyBullet* device; // GPU���̃������̃A�h���X
	extern int maxLength; // �ő�v�f��
	extern int length; // �v�f��
	extern cudaStream_t stream;  // EnemyBullet�̏������s���X�g���[��

	// EnemyBulletPtr���g�p����A�h���X���擾����
	void Get();

	// �������A�|��
	void Init();

	// �폜����
	void EraseRemoveIfIsDead();
}

#endif