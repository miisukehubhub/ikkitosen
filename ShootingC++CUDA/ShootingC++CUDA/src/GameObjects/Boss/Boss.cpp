#include "Boss.h"

#include <DxLib.h>

#include "../../Screen/Screen.h"
#include "../../MyMemory/MyMemory.h"
#include "../../MyRandom/MyRandom.h"
#include "../../Image/Image.h"

#include "../EnemyBullet/EnemyBullet.h"
#include "../Player/Player.h"

Boss::Boss(Vector2 position)
	: m_position(position)
{
	m_state |= (unsigned char)BossState::IsAppear; // �o���Ԃɂ���
	m_modeChangeTimer = MyRandom::RandomRange(60, 600); // ���[�h�`�F���W�������_���Ȏ��Ԃł�����
	m_speed = MyRandom::RandomRange(Vector2(-6.0f, -6.0f), Vector2(6.0f, 6.0f));
}

void Boss::Update()
{
	// �o���Ԃ̎�
	if ((m_state & (unsigned char)BossState::IsAppear) != 0)
	{
		m_position += Vector2(-1.0f, 0.0f);
		if (m_position.x <= 1500.0f)
		{
			m_position.x = 1500.0f;
			m_state &= ~(unsigned char)BossState::IsAppear; // �o���Ԃ�����
		}
		return;
	}

	// �ړ�
	m_position += m_speed;

	// �{�X�͈��̗̈�Ń����_���ȕ����Ɉړ�������
	if (m_position.x < 700.0f)
	{
		m_position.x = 700.0f;
		m_speed = MyRandom::RandomRange(Vector2(-6.0f, -6.0f), Vector2(6.0f, 6.0f));
	}
	else if (m_position.x > Screen::Width)
	{
		m_position.x = Screen::Width;
		m_speed = MyRandom::RandomRange(Vector2(-6.0f, -6.0f), Vector2(6.0f, 6.0f));
	}
	if (m_position.y < 0.0f)
	{
		m_position.y = 0.0f;
		m_speed = MyRandom::RandomRange(Vector2(-6.0f, -6.0f), Vector2(6.0f, 6.0f));
	}
	else if (m_position.y > Screen::Height)
	{
		m_position.y = Screen::Height;
		m_speed = MyRandom::RandomRange(Vector2(-6.0f, -6.0f), Vector2(6.0f, 6.0f));
	}

	// �����̃��[�h�͒e�̉�����Ԋu�Ŕ��˂��Ă���
	if ((m_state & (unsigned char)BossState::IsChangedMode) == 0 && m_massBulletFireTimer <= 0)
	{
		m_massBulletFireTimer = MyRandom::RandomRange(20, 40);
		// �v���C���[�̕����֔��˂���
		Vector2 bulletSpeed = Vector2::normalize(PlayerPtr::host->GetPosition() - m_position) * 30.0f;
		for (int i = 0; i < 200; i++)
		{
			EnemyBulletPtr::host[EnemyBulletPtr::length] =
				EnemyBullet(MyRandom::RandomRange(m_position, 64.0f),
					bulletSpeed,
					4.0f);
			// �v�f���𑝂₷
			EnemyBulletPtr::length++;
		}
	}
	// ���[�h�`�F���W�����Ă�����
	else if ((m_state & (unsigned char)BossState::IsChangedMode) != 0)
	{
		// �₦���e�𔭎˂��Ă���
		for (int i = 0; i < 10; i++)
		{
			Vector2 bulletSpeed = Vector2::normalize(PlayerPtr::host->GetPosition() - m_position) * 12.0f;
			
			EnemyBulletPtr::host[EnemyBulletPtr::length] =
				EnemyBullet(MyRandom::RandomRange(m_position, 32.0f),
					bulletSpeed,
					2.2f);
			// �v�f���𑝂₷
			EnemyBulletPtr::length++;
		}
	}

	m_massBulletFireTimer--;

	if (m_modeChangeTimer > 0)
	{
		m_modeChangeTimer--;
		return;
	}

	m_modeChangeTimer = MyRandom::RandomRange(60, 600);
	m_state ^= (unsigned char)BossState::IsChangedMode; // ���[�h��؂�ւ���
}

void Boss::Draw()
{
	DrawRotaGraphF(m_position.x, m_position.y, 1.0f, 0.0f, Image::At((unsigned char)PlaySceneImageID::Boss), TRUE);
}

void Boss::TakeDamage(short damage)
{
	// �o�ꎞ�̓_���[�W���󂯂Ȃ�
	if ((m_state & (unsigned char)BossState::IsAppear) != 0) return;

	m_hp -= damage;

	if (m_hp < 0)
	{
		m_hp = 0;
		m_state |= (unsigned char)BossState::IsDead;
	}
}

Vector2 Boss::GetPosition()
{
	return m_position;
}

float Boss::GetCollisionRadius()
{
	return m_collisionRadius;
}

unsigned char Boss::GetState()
{
	return m_state;
}

int* Boss::GetMaxHpPtr()
{
	return &m_maxHp;
}

int* Boss::GetHpPtr()
{
	return &m_hp;
}

// namespace BossPtr

Boss* BossPtr::host;
Boss* BossPtr::device;

void BossPtr::Get()
{
	host = (Boss*)MyMemory::hostPtr;
	MyMemory::hostPtr = (void*)&host[1];
	device = (Boss*)MyMemory::devicePtr;
	MyMemory::devicePtr = (void*)&device[1];
	MyMemory::usingSize += sizeof(Boss);
}