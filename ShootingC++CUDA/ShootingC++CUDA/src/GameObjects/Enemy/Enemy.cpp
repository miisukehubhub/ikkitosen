#include "Enemy.h"

#include <cuda_runtime.h>
#include <DxLib.h>

#include "../../GameManager/GameManager.h"

#include "../../MyMemory/MyMemory.h"
#include "../../SE/SE.h"
#include "../Player/Player.h"

Enemy::Enemy(Vector2 position, EnemyKind kind)
	: m_position(position)
	, m_basePosition(position)
	, m_kind(kind)
{
	m_speed = Vector2::normalize(PlayerPtr::host->GetPosition() - position);
	Init();
}

void Enemy::Init()
{
	if (m_kind == EnemyKind::SoftEnemy)
	{
		m_hp = 5;
		m_speed *= 4.0f;
		m_defenceLevel = 0;
		m_bulletFireIntervalTimeFrame = 100;
		m_score = 250;
	}
	else if (m_kind == EnemyKind::HardEnemy)
	{
		m_hp = 4;
		m_speed *= 3.0f;
		m_defenceLevel = 1;
		m_bulletFireIntervalTimeFrame = 100;
		m_score = 300;
	}
	else if (m_kind == EnemyKind::MetalEnemy)
	{
		m_hp = 6;
		m_speed *= 1.8f;
		m_defenceLevel = 2;
		m_bulletFireIntervalTimeFrame = 120;
		m_score = 400;
	}
}

// namespace EnemyPtr

Enemy* EnemyPtr::host;
Enemy* EnemyPtr::device;
int EnemyPtr::maxLength = 1024 * 8;
int EnemyPtr::length = 0;
int EnemyPtr::soundPlayTimer = 0;
cudaStream_t EnemyPtr::stream;

void EnemyPtr::Get()
{
	host = (Enemy*)MyMemory::hostPtr;
	MyMemory::hostPtr = (void*)&host[maxLength];
	device = (Enemy*)MyMemory::devicePtr;
	MyMemory::devicePtr = (void*)&device[maxLength];
	MyMemory::usingSize += sizeof(Enemy) * maxLength;

	cudaStreamCreate(&stream);
}

void EnemyPtr::Init()
{
	length = 0;
	cudaStreamDestroy(stream);
}

void EnemyPtr::EraseRemoveIfIsDead()
{
	int newLength = 0;
	bool isPlaySound = false;
	GameManager& gm = GameManager::GetInstance();
	for (int i = 0; i < length; i++)
	{
		// �G������ł�����
		if ((host[i].m_state & (unsigned char)EnemyState::IsDead) != 0)
		{
			// �X�R�A�����Z
			gm.score += host[i].m_score;
			// �X�R�A���ϓ����Ă����
			if (host[i].m_score != 0)
			{
				// �X�e�[�W�̐i�s�x���グ��
				gm.progressValue--;
				// ����炷����������
				isPlaySound = true;
			}
			continue;
		}

		// ����ł��Ȃ���ΐV�����ꏊ�ɃR�s�[����
		memcpy(
			(void*)&host[newLength],
			(void*)&host[i],
			sizeof(Enemy));

		// �V�����v�f���𑝂₷
		newLength++;
	}

	// �v�f�����m�肳����
	length = newLength;

	if (soundPlayTimer > 0)
	{
		soundPlayTimer--;
		return;
	}
	
	if (isPlaySound)
	{
		soundPlayTimer = 3;
		PlaySoundMem(SE::At(SEID::EnemyDead), DX_PLAYTYPE_BACK);
	}
}