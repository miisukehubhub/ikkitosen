#ifndef BOSS_H_
#define BOSS_H_

#include <cuda_runtime.h>
#include <memory>

#include "../../Vector2/Vector2.h"

__device__ __host__ enum class BossState : unsigned char
{
	IsDead = 1,
	IsAppear = 1 << 1,
	IsChangedMode = 1 << 2,
};

class Boss
{
public:

	Boss(Vector2 position); // �R���X�g���N�^

	~Boss() = default; // �f�X�g���N�^

	void Update(); // �X�V����

	void Draw(); // �`�揈��

	void TakeDamage(short damage); // ��_���[�W����

	Vector2 GetPosition();

	float GetCollisionRadius();

	unsigned char GetState();

	int* GetMaxHpPtr();

	int* GetHpPtr();

private:

	Vector2 m_position{ 0.0f };
	Vector2 m_speed{ Vector2_v::zero };
	float m_collisionRadius{ 64.0f };
	int m_maxHp{ 30000 };
	int m_hp{ 30000 };
	int m_modeChangeTimer{ 0 };
	int m_massBulletFireTimer{ 0 };
	unsigned char m_state{ 0 };
};

namespace BossPtr
{
	extern Boss* host; // CPU���̃������̃A�h���X
	extern Boss* device; // GPU���̃������̃A�h���X

	// BossPtr���g�p����A�h���X���߂�
	void Get();
}

#endif
