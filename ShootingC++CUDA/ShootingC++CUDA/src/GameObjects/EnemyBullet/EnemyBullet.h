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

	EnemyBullet(Vector2 position, Vector2 speed, float sizeRate); // コンストラクタ

public:

	Vector2 m_position{ Vector2_v::zero };
	Vector2 m_speed{ Vector2_v::zero };
	bool m_isDead{ false };
	float m_collisionRadius{ 8.0f };
	float m_sizeRate{ 1.0f };
};

namespace EnemyBulletPtr
{
	extern EnemyBullet* host; // CPU側のメモリのアドレス
	extern EnemyBullet* device; // GPU側のメモリのアドレス
	extern int maxLength; // 最大要素数
	extern int length; // 要素数
	extern cudaStream_t stream;  // EnemyBulletの処理を行うストリーム

	// EnemyBulletPtrが使用するアドレスを取得する
	void Get();

	// 初期化、掃除
	void Init();

	// 削除処理
	void EraseRemoveIfIsDead();
}

#endif