#include "PlayerNormalBulletCreator.h"

#include "../../../PlayerBullets/PlayerNormalBullet/PlayerNormalBullet.h"
#include "../../Player.h"
#include "../../../../Input/XInput.h"
#include "../../../../Input/DInput.h"
#include "../../../../SE/SE.h"

void PlayerNormalBulletCreator::Update()
{
	if (m_createIntervalTimer > 0)
	{
		m_createIntervalTimer--;
		return;
	}

	// ”­ŽËƒ{ƒ^ƒ“‚ª‰Ÿ‚³‚ê‚Ä‚¢‚½‚ç
	if ((XInput::GetButton(XInputDigitalID::LeftShoulder) && gm.playingInputType == InputType::XInput) ||
		(DInput::GetButton(DInputID::ZKey) && gm.playingInputType == InputType::DirectInput))
	{
		PlayerNormalBulletPtr::host[PlayerNormalBulletPtr::length]
			= PlayerNormalBullet(PlayerPtr::host->GetPosition());
		PlayerNormalBulletPtr::length++;
		m_createIntervalTimer = m_createIntervalTimeFrame;

		PlaySoundMem(SE::At(SEID::NormalBulletFire), DX_PLAYTYPE_BACK); // ‰¹‚ð–Â‚ç‚·
	}
}