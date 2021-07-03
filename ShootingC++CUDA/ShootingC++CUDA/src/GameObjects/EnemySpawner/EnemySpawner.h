#ifndef ENEMYSPAWNER_H_
#define ENEMYSPAWNER_H_

#include <unordered_map>

#include "../../Vector2/Vector2.h"
#include "../../Screen/Screen.h"
#include "../Enemy/EnemyKind.h"

class EnemySpawner
{
public:

	EnemySpawner() = default; // コンストラクタ

	void Update(); // 更新処理

	void SetProportion(short softEnemyProp, short hardEnemyProp, short metalEnemyProp); // 敵出現の比率を変える

	void SetOneClusterNum(short num); // 敵の１集団の数を設定する

private:

	Vector2 m_position{ Vector2(Screen::Width + 100, Screen::Height / 2.0f) };
	float m_angle{ 0.0f };
	float m_speed{ 0.16f };
	short m_spawnIntervalTimeFrame{ 60 };
	short m_spawnIntervalTimer{ 0 };
	short m_oneClusterNum{ 400 };
	short m_softEnemyProportion{ 0 };
	short m_hardEnemyProportion{ 0 };
	short m_metalEnemyProportion{ 0 };
	int m_proportionSum{ 0 };
};

namespace EnemySpawnerPtr
{
	extern EnemySpawner* host; // CPU側のメモリのアドレス
	extern EnemySpawner* device; // GPU側のメモリのアドレス

	// EnemySpawnPtrが使用するアドレスを取得
	void Get();
}
#endif