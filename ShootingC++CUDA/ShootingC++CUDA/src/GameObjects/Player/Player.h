#ifndef PLAYER_H_
#define PLAYER_H_

#include <cuda_runtime.h>
#include <memory>

#include "../../GameManager/GameManager.h"

#include "../../Vector2/Vector2.h"
#include "Weapons/PlayerWeapon.h"

// �v���C���[�̏��
__device__ __host__ enum class PlayerState : unsigned char
{
	IsDead = 1,
	UseSubWeapon = 1 << 1,
};

class Player
{
public:

	Player(Vector2 initPosition); // �R���X�g���N�^

	~Player() = default; // �f�X�g���N�^

	void Init(); // ����������

	void Update(); // �X�V����

	void Draw(); // �`�揈��

	void TakeDamage(); //	��_���[�W����

	Vector2 GetPosition();

	float GetCollisionRadius();

	int* GetMaxHpPtr();

	int* GetHpPtr();

	__device__ __host__ unsigned char* GetStatePtr() { return &m_state; }

private:

	Vector2 m_initPosition;
	Vector2 m_position{ 0.0f };
	std::shared_ptr<PlayerWeapon> m_mainWeapon;
	std::shared_ptr<PlayerWeapon> m_subWeapon;
	float m_maxSpeed{ 6.0f };
	float m_collisionRadius{ 32.0f };
	int m_maxHp{ 50000 };
	int m_hp{ 50000 };
	unsigned char m_state{ 0 };
};

namespace PlayerPtr
{
	extern Player* host; // CPU���̃������̃A�h���X
	extern Player* device; // GPU���̃������̃A�h���X

	// PlayerPtr���g�p����A�h���X���擾
	void Get();
}

#endif
