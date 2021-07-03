#include "Player.h"

#include <DxLib.h>

#include "../../Input/XInput.h"
#include "../../Input/DInput.h"
#include "../../Screen/Screen.h"
#include "../../MyMemory/MyMemory.h"
#include "../../Image/Image.h"
#include "Weapons/PlayerNormalBulletCreator/PlayerNormalBulletCreator.h"
#include "Weapons/PlayerScatterBulletCreator/PlayerScatterBulletCreator.h"

Player::Player(Vector2 initPosition)
	: m_initPosition(initPosition)
{
	Init();
}

void Player::Init()
{
	m_mainWeapon = std::make_shared<PlayerNormalBulletCreator>();
	m_subWeapon = std::make_shared<PlayerScatterBulletCreator>();
	m_position = m_initPosition;
	m_hp = m_maxHp;
	m_state = 0;
}

void Player::Update()
{
	GameManager& gm = GameManager::GetInstance();

	// 使用する入力がXInputなら
	if (gm.playingInputType == InputType::XInput)
	{
		Vector2 stickState = Vector2_v::zero; // スティックのアナログ値
		if (XInput::GetStickMove(true, 5000.f)) // 左スティックが5000以上の時
		{
			stickState = XInput::GetStickState(true); // アナログ値を得る
		}

		Vector2 speed = Vector2_v::zero;

		if (stickState != Vector2_v::zero) // スティックが傾いていれば
		{
			float magniX = stickState.x / 32768.0f;
			float magniY = stickState.y / 32768.0f;
			if (stickState.x != 0) speed.x = m_maxSpeed * magniX;
			if (stickState.y != 0) speed.y = -1.f * m_maxSpeed * magniY;
		}

		m_position += speed; // 移動

		if (XInput::GetButtonDown(XInputDigitalID::LeftThumb))
		{
			// 武器を切り替える
			m_state ^= (unsigned char)PlayerState::UseSubWeapon;
		}

		if ((m_state & (unsigned char)PlayerState::UseSubWeapon) == 0) 	m_mainWeapon->Update(); // メイン武器の更新
		else m_subWeapon->Update(); // サブ武器の更新
	}
	// 使用する入力がDirectInputなら
	else if (gm.playingInputType == InputType::DirectInput)
	{
		Vector2 speed = Vector2_v::zero;
		if (DInput::GetButton(DInputID::LeftKey))
		{
			speed.x = -m_maxSpeed;
		}
		else if (DInput::GetButton(DInputID::RightKey))
		{
			speed.x = m_maxSpeed;
		}
		if (DInput::GetButton(DInputID::UpKey))
		{
			speed.y = -m_maxSpeed;
		}
		else if (DInput::GetButton(DInputID::DownKey))
		{
			speed.y = m_maxSpeed;
		}

		m_position += speed; // 移動

		if (DInput::GetButtonDown(DInputID::CKey))
		{
			// 武器を切り替える
			m_state ^= (unsigned char)PlayerState::UseSubWeapon;
		}
		
		if ((m_state & (unsigned char)PlayerState::UseSubWeapon) == 0) 	m_mainWeapon->Update(); // メイン武器の更新
		else m_subWeapon->Update(); // サブ武器の更新
	}

	// 画面外禁止
	if (m_position.x < m_collisionRadius) m_position.x = m_collisionRadius;
	else if (m_position.x > Screen::Width - m_collisionRadius) m_position.x = Screen::Width - m_collisionRadius;
	if (m_position.y < m_collisionRadius) m_position.y = m_collisionRadius;
	else if (m_position.y > Screen::Height - m_collisionRadius) m_position.y = Screen::Height - m_collisionRadius;
}

void Player::Draw()
{
	DrawRotaGraphF(m_position.x, m_position.y, 1.0f, 0.0f, Image::At((unsigned char)PlaySceneImageID::Player), TRUE);
}

void Player::TakeDamage()
{
	m_hp--;

	if (m_hp < 0)
	{
		m_hp = 0;
		m_state |= (unsigned char)PlayerState::IsDead;
	}
}

Vector2 Player::GetPosition()
{
	return m_position;
}

float Player::GetCollisionRadius()
{
	return m_collisionRadius;
}

int* Player::GetMaxHpPtr()
{
	return &m_maxHp;
}

int* Player::GetHpPtr()
{
	return &m_hp;
}

// namespace PlayerPtr

Player* PlayerPtr::host;
Player* PlayerPtr::device;

void PlayerPtr::Get()
{
	host = (Player*)MyMemory::hostPtr;
	MyMemory::hostPtr = (void*)&host[1];
	device = (Player*)MyMemory::devicePtr;
	MyMemory::devicePtr = (void*)&device[1];
	MyMemory::usingSize += sizeof(Player);
}