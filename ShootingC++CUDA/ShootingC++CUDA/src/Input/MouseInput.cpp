#include"MouseInput.h"

int MouseInput::prevState{ 0 };
int MouseInput::currentState{ 0 };

// 初期化
void MouseInput::Init()
{
	prevState = 0;
	currentState = 0;
}

// 最新の入力状況に更新する処理
void MouseInput::Update()
{
	prevState = currentState;

	currentState = GetMouseInput();
}

// マウスの位置を取得
Vector2 MouseInput::GetPosition()
{
	int x, y;
	GetMousePoint(&x, &y);
	return Vector2(x, y);
}

// ボタンが押されているか？
bool MouseInput::GetButton(int buttonId)
{
	// 今ボタンが押されているかどうかを返却
	return (currentState & buttonId) != 0;
}

// ボタンが押された瞬間か？
bool MouseInput::GetButtonDown(int buttonId)
{
	// 今は押されていて、かつ1フレーム前は押されていない場合はtrueを返却
	return ((currentState & buttonId) & ~(prevState & buttonId)) != 0;
}

// ボタンが離された瞬間か？
bool MouseInput::GetButtonUp(int buttonId)
{
	// 1フレーム前は押されていて、かつ今は押されている場合はtrueを返却
	return ((prevState & buttonId) & ~(currentState & buttonId)) != 0;
}