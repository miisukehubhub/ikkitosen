#ifndef PLAYERSCATTERBULLET_H_
#define PLAYERSCATTERBULLET_H_

#include <DxLib.h>
#include <cuda_runtime.h>

#include "../../../Vector2/Vector2.h"
#include "../../../Screen/Screen.h"

class PlayerScatterBullet
{
public:

	PlayerScatterBullet(Vector2 position, float angle); // コンストラクタ

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
	extern PlayerScatterBullet* host; // CPU側のメモリのアドレス
	extern PlayerScatterBullet* device; // GPU側のメモリのアドレス
	extern int maxLength; // 最大要素数
	extern int length; // 要素数
	extern cudaStream_t stream; // PlayerScatterBulletに関係する処理を行うストリーム

	// PlayerScatterBulletPtrが使用するアドレスを取得する
	void Get();

	// 初期化、掃除
	void Init();

	// 削除処理
	void EraseRemoveIfIsDead();
}

#endif
