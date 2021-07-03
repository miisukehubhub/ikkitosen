#ifndef PLAYER_H_
#define PLAYER_H_

#include <cuda_runtime.h>
#include <memory>

#include "../../GameManager/GameManager.h"

#include "../../Vector2/Vector2.h"
#include "Weapons/PlayerWeapon.h"

// プレイヤーの状態
__device__ __host__ enum class PlayerState : unsigned char
{
	IsDead = 1,
	UseSubWeapon = 1 << 1,
};

class Player
{
public:

	Player(Vector2 initPosition); // コンストラクタ

	~Player() = default; // デストラクタ

	void Init(); // 初期化処理

	void Update(); // 更新処理

	void Draw(); // 描画処理

	void TakeDamage(); //	被ダメージ処理

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
	extern Player* host; // CPU側のメモリのアドレス
	extern Player* device; // GPU側のメモリのアドレス

	// PlayerPtrが使用するアドレスを取得
	void Get();
}

#endif
