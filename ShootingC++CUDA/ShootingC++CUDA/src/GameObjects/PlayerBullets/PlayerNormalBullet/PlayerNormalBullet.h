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

	PlayerNormalBullet(Vector2 position); // コンストラクタ

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
	extern PlayerNormalBullet* host; // CPU側のメモリのアドレス
	extern PlayerNormalBullet* device; // GPU側のメモリのアドレス
	extern int maxLength; // 最大要素数
	extern int length; // 要素数
	extern cudaStream_t stream; // PlayerNOrmalBulletに関する処理を行うストリーム

	// PlayerNormalBulletPtrが使用するアドレスを取得
	void Get();

	// 初期化、掃除
	void Init();

	// 削除処理
	void EraseRemoveIfIsDead();
}

#endif