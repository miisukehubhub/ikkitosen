#include "XInput.h"

#include <cmath>

XINPUT_STATE XInput::prevState{ XINPUT_STATE() };
XINPUT_STATE XInput::currentState{ XINPUT_STATE() };

// 初期化
void XInput::Init()
{
	SetJoypadDeadZone(DX_INPUT_PAD1, 0.0);
}

// 最新の入力状況に更新する処理
void XInput::Update()
{
	prevState = currentState;
	GetJoypadXInputState(DX_INPUT_PAD1, &currentState);
}

// ボタンが押されているか？
bool XInput::GetButton(XInputDigitalID id)
{
	return currentState.Buttons[(int)id] != 0;
}

// ボタンが押された瞬間か？
bool XInput::GetButtonDown(XInputDigitalID id)
{
	return currentState.Buttons[(int)id] - prevState.Buttons[(int)id] > 0;
}

// ボタンが離された瞬間か？
bool XInput::GetButtonUp(XInputDigitalID id)
{
	return prevState.Buttons[(int)id] - currentState.Buttons[(int)id] > 0;
}

// 指定のアナログ値をの一定量を超えているか
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

// アナログ値が変化した瞬間かどうか
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

// スティックの傾きが一定量を超えているか
bool XInput::GetStickMove(bool isLeft, float min)
{
	Vector2 v = GetStickState(isLeft);
	return v.lengthSquared() >= min * min;
}

// スティックの傾きが一定量を超えた瞬間か
bool XInput::GetStickMoveMoment(bool isLeft, float min)
{
	Vector2 cv = GetStickState(isLeft);
	Vector2 pv;
	if (isLeft) pv = Vector2(prevState.ThumbLX, prevState.ThumbLY);
	else pv = Vector2(prevState.ThumbRX, prevState.ThumbRY);
	return (pv.lengthSquared() < min * min) && (cv.lengthSquared() >= min * min);
}

// アナログ値を取得する
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

// スティックのアナログ値を取得する
Vector2 XInput::GetStickState(bool isLeft)
{
	if (isLeft) return Vector2(currentState.ThumbLX, currentState.ThumbLY);
	return Vector2(currentState.ThumbRX, currentState.ThumbRY);
}