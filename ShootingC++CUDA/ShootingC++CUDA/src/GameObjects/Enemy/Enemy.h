#ifndef ENEMY_H_
#define ENEMY_H_

#include <cuda_runtime.h>

#include "../../Vector2/Vector2.h"
#include "EnemyKind.h"

__device__ __host__ enum class EnemyState : unsigned char
{
	IsDead = 1,
	canFire = 1 << 1,
	IsDamage = 1 << 2,
};

class Enemy
{
public:

	Enemy(Vector2 position, EnemyKind kind); // �R���X�g���N�^

	void Init(); // ����������

public:

	Vector2 m_position{ Vector2_v::zero };
	Vector2 m_basePosition{ Vector2_v::zero };
	Vector2 m_speed{ Vector2_v::zero };
	int m_hp{ 0 };
	short m_defenceLevel{ 0 };
	short m_bulletFireIntervalTimeFrame{ 0 };
	short m_bulletFireIntervalTimer{ 0 };
	float m_angle{ 0.0f };
	float m_collisionRadius{ 2.0f };
	short m_score{ 0 };
	EnemyKind m_kind{ EnemyKind::SoftEnemy };
	unsigned char m_state{ 0 };
};

namespace EnemyPtr
{
	extern Enemy* host; // CPU���̃������̃A�h���X
	extern Enemy* device; // GPU���̂߂�����̃A�h���X
	extern int maxLength; // �ő�v�f��
	extern int length; // �v�f��
	extern int soundPlayTimer; // SE��������x����ɖ炷���߂̃^�C�}�[
	extern cudaStream_t stream; // �G�Ɋւ��邱�Ƃ�����X�g���[��

	// EnemyPtr���g���A�h���X�����肷��
	void Get();
	// �������A�|��
	void Init();

	// �G�̍폜����
	void EraseRemoveIfIsDead();
}

#endif
