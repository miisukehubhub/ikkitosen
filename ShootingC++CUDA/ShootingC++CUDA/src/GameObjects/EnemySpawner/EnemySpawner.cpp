#include "EnemySpawner.h"

#include <cmath>

#include "../Enemy/Enemy.h"
#include "../../MyRandom/MyRandom.h"
#include "../../MyMemory/MyMemory.h"

void EnemySpawner::Update()
{
	// スポーンタイマーがゼロになるまでスポーンさせない
	if (m_spawnIntervalTimer > 0)
	{
		m_spawnIntervalTimer--;
		return;
	}

	m_spawnIntervalTimer = m_spawnIntervalTimeFrame;

	// ランダムな位置で
	m_position.y = MyRandom::RandomRange(-300.f, Screen::Height + 300.f);

	// 一塊の数分ループする
	for (int i = 0; i < m_oneClusterNum; i++)
	{
		Vector2 spawnPosition = MyRandom::RandomRange(m_position - Vector2(150.f, 150.f), m_position + Vector2(150.f, 150.f));

		if (MyRandom::Probab((float)m_softEnemyProportion / m_proportionSum))
		{
			EnemyPtr::host[EnemyPtr::length] = Enemy(spawnPosition, EnemyKind::SoftEnemy);
			EnemyPtr::length++;
			continue;
		}

		if (MyRandom::Probab((float)m_hardEnemyProportion / (m_proportionSum - m_softEnemyProportion)))
		{
			EnemyPtr::host[EnemyPtr::length] = Enemy(spawnPosition, EnemyKind::HardEnemy);
			EnemyPtr::length++;
			continue;
		}

		EnemyPtr::host[EnemyPtr::length] = Enemy(spawnPosition, EnemyKind::MetalEnemy);
		EnemyPtr::length++;
	}
}

void EnemySpawner::SetProportion(short softEnemyProp, short hardEnemyProp, short metalEnemyProp)
{
	m_softEnemyProportion = softEnemyProp;
	m_hardEnemyProportion = hardEnemyProp;
	m_metalEnemyProportion = metalEnemyProp;
	m_proportionSum = softEnemyProp + hardEnemyProp + metalEnemyProp;
}

void EnemySpawner::SetOneClusterNum(short num)
{
	m_oneClusterNum = num;
}

// namespace EnemySpawnerPtr

EnemySpawner* EnemySpawnerPtr::host;
EnemySpawner* EnemySpawnerPtr::device;

void EnemySpawnerPtr::Get()
{
	host = (EnemySpawner*)MyMemory::hostPtr;
	MyMemory::hostPtr = (void*)&host[1];
	device = (EnemySpawner*)MyMemory::devicePtr;
	MyMemory::devicePtr = (void*)&device[1];
	MyMemory::usingSize += sizeof(EnemySpawner);
}