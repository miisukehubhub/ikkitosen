#include "XInput.h"

#include <cmath>

XINPUT_STATE XInput::prevState{ XINPUT_STATE() };
XINPUT_STATE XInput::currentState{ XINPUT_STATE() };

// ������
void XInput::Init()
{
	SetJoypadDeadZone(DX_INPUT_PAD1, 0.0);
}

// �ŐV�̓��͏󋵂ɍX�V���鏈��
void XInput::Update()
{
	prevState = currentState;
	GetJoypadXInputState(DX_INPUT_PAD1, &currentState);
}

// �{�^����������Ă��邩�H
bool XInput::GetButton(XInputDigitalID id)
{
	return currentState.Buttons[(int)id] != 0;
}

// �{�^���������ꂽ�u�Ԃ��H
bool XInput::GetButtonDown(XInputDigitalID id)
{
	return currentState.Buttons[(int)id] - prevState.Buttons[(int)id] > 0;
}

// �{�^���������ꂽ�u�Ԃ��H
bool XInput::GetButtonUp(XInputDigitalID id)
{
	return prevState.Buttons[(int)id] - currentState.Buttons[(int)id] > 0;
}

// �w��̃A�i���O�l���̈��ʂ𒴂��Ă��邩
bool XInput::GetAnalogInput(XInputAnalogID id, short min)
{
	if (id == XInputAnalogID::LeftTrigger) return std::abs(currentState.LeftTrigger) >= min;
	if (id == XInputAnalogID::RightTrigger) return std::abs(currentState.RightTrigger) >= min;
	if (id == XInputAnalogID::ThumbLX) return std::abs(currentState.ThumbLX) >= min;
	if (id == XInputAnalogID::ThumbLY) return std::abs(currentState.ThumbLY) >= min;
	if (id == XInputAnalogID::ThumbRX) return std::abs(currentState.ThumbRX) >= min;
	if (id == XInputAnalogID::ThumbRY) return std::abs(currentState.ThumbRY) >= min;
	return false;
}

// �A�i���O�l���ω������u�Ԃ��ǂ���
bool XInput::GetAnalogInputMoment(XInputAnalogID id, short min)
{
	int cs = -1;
	if (id == XInputAnalogID::LeftTrigger) cs = std::abs(currentState.LeftTrigger) - min;
	else if (id == XInputAnalogID::RightTrigger) cs = std::abs(currentState.RightTrigger) - min;
	else if (id == XInputAnalogID::ThumbLX) cs = std::abs(currentState.ThumbLX) - min;
	else if (id == XInputAnalogID::ThumbLY) cs = std::abs(currentState.ThumbLY) - min;
	else if (id == XInputAnalogID::ThumbRX) cs = std::abs(currentState.ThumbRX) - min;
	else if (id == XInputAnalogID::ThumbRY) cs = std::abs(currentState.ThumbRY) - min;

	int ps = -1;
	if (id == XInputAnalogID::LeftTrigger) ps = std::abs(prevState.LeftTrigger) - min;
	else if (id == XInputAnalogID::RightTrigger) ps = std::abs(prevState.RightTrigger) - min;
	else if (id == XInputAnalogID::ThumbLX) ps = std::abs(prevState.ThumbLX) - min;
	else if (id == XInputAnalogID::ThumbLY) ps = std::abs(prevState.ThumbLY) - min;
	else if (id == XInputAnalogID::ThumbRX) ps = std::abs(prevState.ThumbRX) - min;
	else if (id == XInputAnalogID::ThumbRY) ps = std::abs(prevState.ThumbRY) - min;

	return (cs > ps) && (cs * ps < 0);
}

// �X�e�B�b�N�̌X�������ʂ𒴂��Ă��邩
bool XInput::GetStickMove(bool isLeft, float min)
{
	Vector2 v = GetStickState(isLeft);
	return v.lengthSquared() >= min * min;
}

// �X�e�B�b�N�̌X�������ʂ𒴂����u�Ԃ�
bool XInput::GetStickMoveMoment(bool isLeft, float min)
{
	Vector2 cv = GetStickState(isLeft);
	Vector2 pv;
	if (isLeft) pv = Vector2(prevState.ThumbLX, prevState.ThumbLY);
	else pv = Vector2(prevState.ThumbRX, prevState.ThumbRY);
	return (pv.lengthSquared() < min * min) && (cv.lengthSquared() >= min * min);
}

// �A�i���O�l���擾����
short XInput::GetAnalogPoint(XInputAnalogID id)
{
	if (id == XInputAnalogID::LeftTrigger) return currentState.LeftTrigger;
	if (id == XInputAnalogID::RightTrigger) return currentState.RightTrigger;
	if (id == XInputAnalogID::ThumbLX) return currentState.ThumbLX;
	if (id == XInputAnalogID::ThumbLY) return currentState.ThumbLY;
	if (id == XInputAnalogID::ThumbRX) return currentState.ThumbRX;
	if (id == XInputAnalogID::ThumbRY) return currentState.ThumbRY;
	return 0;
}

// �X�e�B�b�N�̃A�i���O�l���擾����
Vector2 XInput::GetStickState(bool isLeft)
{
	if (isLeft) return Vector2(currentState.ThumbLX, currentState.ThumbLY);
	return Vector2(currentState.ThumbRX, currentState.ThumbRY);
}