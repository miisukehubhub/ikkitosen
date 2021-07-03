#include"MouseInput.h"

int MouseInput::prevState{ 0 };
int MouseInput::currentState{ 0 };

// ������
void MouseInput::Init()
{
	prevState = 0;
	currentState = 0;
}

// �ŐV�̓��͏󋵂ɍX�V���鏈��
void MouseInput::Update()
{
	prevState = currentState;

	currentState = GetMouseInput();
}

// �}�E�X�̈ʒu���擾
Vector2 MouseInput::GetPosition()
{
	int x, y;
	GetMousePoint(&x, &y);
	return Vector2(x, y);
}

// �{�^����������Ă��邩�H
bool MouseInput::GetButton(int buttonId)
{
	// ���{�^����������Ă��邩�ǂ�����ԋp
	return (currentState & buttonId) != 0;
}

// �{�^���������ꂽ�u�Ԃ��H
bool MouseInput::GetButtonDown(int buttonId)
{
	// ���͉�����Ă��āA����1�t���[���O�͉�����Ă��Ȃ��ꍇ��true��ԋp
	return ((currentState & buttonId) & ~(prevState & buttonId)) != 0;
}

// �{�^���������ꂽ�u�Ԃ��H
bool MouseInput::GetButtonUp(int buttonId)
{
	// 1�t���[���O�͉�����Ă��āA�����͉�����Ă���ꍇ��true��ԋp
	return ((prevState & buttonId) & ~(currentState & buttonId)) != 0;
}