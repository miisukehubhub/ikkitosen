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
	m_state |= (unsigned char)BossState::IsAppear; // 登場状態にする
	m_modeChangeTimer = MyRandom::RandomRange(60, 600); // モードチェンジをランダムな時間でさせる
	m_speed = MyRandom::RandomRange(Vector2(-6.0f, -6.0f), Vector2(6.0f, 6.0f));
}

void Boss::Update()
{
	// 登場状態の時
	if ((m_state & (unsigned char)BossState::IsAppear) != 0)
	{
		m_position += Vector2(-1.0f, 0.0f);
		if (m_position.x <= 1500.0f)
		{
			m_position.x = 1500.0f;
			m_state &= ~(unsigned char)BossState::IsAppear; // 登場状態を解除
		}
		return;
	}

	// 移動
	m_position += m_speed;

	// ボスは一定の領域でランダムな方向に移動させる
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

	// 初期のモードは弾の塊を一定間隔で発射してくる
	if ((m_state & (unsigned char)BossState::IsChangedMode) == 0 && m_massBulletFireTimer <= 0)
	{
		m_massBulletFireTimer = MyRandom::RandomRange(20, 40);
		// プレイヤーの方向へ発射する
		Vector2 bulletSpeed = Vector2::normalize(PlayerPtr::host->GetPosition() - m_position) * 30.0f;
		for (int i = 0; i < 200; i++)
		{
			EnemyBulletPtr::host[EnemyBulletPtr::length] =
				EnemyBullet(MyRandom::RandomRange(m_position, 64.0f),
					bulletSpeed,
					4.0f);
			// 要素数を増やす
			EnemyBulletPtr::length++;
		}
	}
	// モードチェンジをしていたら
	else if ((m_state & (unsigned char)BossState::IsChangedMode) != 0)
	{
		// 絶えず弾を発射してくる
		for (int i = 0; i < 10; i++)
		{
			Vector2 bulletSpeed = Vector2::normalize(PlayerPtr::host->GetPosition() - m_position) * 12.0f;
			
			EnemyBulletPtr::host[EnemyBulletPtr::length] =
				EnemyBullet(MyRandom::RandomRange(m_position, 32.0f),
					bulletSpeed,
					2.2f);
			// 要素数を増やす
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
	m_state ^= (unsigned char)BossState::IsChangedMode; // モードを切り替える
}

void Boss::Draw()
{
	DrawRotaGraphF(m_position.x, m_position.y, 1.0f, 0.0f, Image::At((unsigned char)PlaySceneImageID::Boss), TRUE);
}

void Boss::TakeDamage(short damage)
{
	// 登場時はダメージを受けない
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