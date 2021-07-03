#ifndef ENEMYSPAWNER_H_
#define ENEMYSPAWNER_H_

#include <unordered_map>

#include "../../Vector2/Vector2.h"
#include "../../Screen/Screen.h"
#include "../Enemy/EnemyKind.h"

class EnemySpawner
{
public:

	EnemySpawner() = default; // �R���X�g���N�^

	void Update(); // �X�V����

	void SetProportion(short softEnemyProp, short hardEnemyProp, short metalEnemyProp); // �G�o���̔䗦��ς���

	void SetOneClusterNum(short num); // �G�̂P�W�c�̐���ݒ肷��

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
	extern EnemySpawner* host; // CPU���̃������̃A�h���X
	extern EnemySpawner* device; // GPU���̃������̃A�h���X

	// EnemySpawnPtr���g�p����A�h���X���擾
	void Get();
}
#endif