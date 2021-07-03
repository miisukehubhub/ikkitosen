#include"DInput.h"

int DInput::prevState{ 0 };
int DInput::currentState{ 0 };

// ������
void DInput::Init()
{
	prevState = 0;
	currentState = 0;
}

// �ŐV�̓��͏󋵂ɍX�V���鏈��
void DInput::Update()
{
	prevState = currentState;

	currentState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
}

// �{�^����������Ă��邩�H
bool DInput::GetButton(int buttonId)
{
	// ���{�^����������Ă��邩�ǂ�����ԋp
	return (currentState & buttonId) != 0;
}

// �{�^���������ꂽ�u�Ԃ��H
bool DInput::GetButtonDown(int buttonId)
{
	// ���͉�����Ă��āA����1�t���[���O�͉�����Ă��Ȃ��ꍇ��true��ԋp
	return ((currentState & buttonId) & ~(prevState & buttonId)) != 0;
}

// �{�^���������ꂽ�u�Ԃ��H
bool DInput::GetButtonUp(int buttonId)
{
	// 1�t���[���O�͉�����Ă��āA�����͉�����Ă���ꍇ��true��ԋp
	return ((prevState & buttonId) & ~(currentState & buttonId)) != 0;
}