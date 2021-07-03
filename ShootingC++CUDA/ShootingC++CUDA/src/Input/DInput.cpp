#include"DInput.h"

int DInput::prevState{ 0 };
int DInput::currentState{ 0 };

// 初期化
void DInput::Init()
{
	prevState = 0;
	currentState = 0;
}

// 最新の入力状況に更新する処理
void DInput::Update()
{
	prevState = currentState;

	currentState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
}

// ボタンが押されているか？
bool DInput::GetButton(int buttonId)
{
	// 今ボタンが押されているかどうかを返却
	return (currentState & buttonId) != 0;
}

// ボタンが押された瞬間か？
bool DInput::GetButtonDown(int buttonId)
{
	// 今は押されていて、かつ1フレーム前は押されていない場合はtrueを返却
	return ((currentState & buttonId) & ~(prevState & buttonId)) != 0;
}

// ボタンが離された瞬間か？
bool DInput::GetButtonUp(int buttonId)
{
	// 1フレーム前は押されていて、かつ今は押されている場合はtrueを返却
	return ((prevState & buttonId) & ~(currentState & buttonId)) != 0;
}