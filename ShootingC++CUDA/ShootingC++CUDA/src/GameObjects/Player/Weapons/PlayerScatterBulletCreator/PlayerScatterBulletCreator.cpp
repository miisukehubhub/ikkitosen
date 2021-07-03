#include "PlayerScatterBulletCreator.h"

#include "../../../PlayerBullets/PlayerScatterBullet/PlayerScatterBullet.h"
#include "../../Player.h"
#include "../../../../Input/XInput.h"
#include "../../../../Input/DInput.h"
#include "../../../../MyRandom/MyRandom.h"
#include "../../../../SE/SE.h"

void PlayerScatterBulletCreator::Update()
{
	// ���˃{�^����������Ă�����
	if ((XInput::GetButton(XInputDigitalID::LeftShoulder) && gm.playingInputType == InputType::XInput) ||
		(DInput::GetButton(DInputID::ZKey) && gm.playingInputType == InputType::DirectInput))
	{
		for (int i = 0; i < 10; i++)
		{
			// �����_����15�x�͈̔͂̊p�x��
			float angle = MyRandom::RandomRange(-3.14159f / 12.0f, 3.14159f / 12.0f);

			PlayerScatterBulletPtr::host[PlayerScatterBulletPtr::length]
				= PlayerScatterBullet(PlayerPtr::host->GetPosition(), angle);
			PlayerScatterBulletPtr::length++;
		}

		if (m_playSoundIntervalTimer > 0)
		{
			m_playSoundIntervalTimer--;
			return;
		}
		m_playSoundIntervalTimer = m_playSoundIntervalTimeFrame;
		PlaySoundMem(SE::At(SEID::ScatterBulletFire), DX_PLAYTYPE_BACK); // ����炷
	}
}