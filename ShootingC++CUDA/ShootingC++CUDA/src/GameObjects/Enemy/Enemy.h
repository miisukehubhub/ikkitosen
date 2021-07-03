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

	Enemy(Vector2 position, EnemyKind kind); // コンストラクタ

	void Init(); // 初期化処理

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
	extern Enemy* host; // CPU側のメモリのアドレス
	extern Enemy* device; // GPU側のめっもりのアドレス
	extern int maxLength; // 最大要素数
	extern int length; // 要素数
	extern int soundPlayTimer; // SEをある程度正常に鳴らすためのタイマー
	extern cudaStream_t stream; // 敵に関することをするストリーム

	// EnemyPtrが使うアドレスを決定する
	void Get();
	// 初期化、掃除
	void Init();

	// 敵の削除処理
	void EraseRemoveIfIsDead();
}

#endif
