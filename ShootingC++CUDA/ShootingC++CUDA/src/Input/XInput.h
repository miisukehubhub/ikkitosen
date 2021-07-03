#ifndef INPUT_H_
#define INPUT_H_

#include <DxLib.h>

#include "../Vector2/Vector2.h"

// XInput��ID
enum class XInputDigitalID : unsigned char
{
    Up =                    XINPUT_BUTTON_DPAD_UP,          // �f�W�^�������{�^����
    Down =                  XINPUT_BUTTON_DPAD_DOWN,        // �f�W�^�������{�^����
    Left =                  XINPUT_BUTTON_DPAD_LEFT,        // �f�W�^�������{�^����
    Right =                 XINPUT_BUTTON_DPAD_RIGHT,       // �f�W�^�������{�^���E
    Start =                 XINPUT_BUTTON_START,            // START�{�^��
    Back =                  XINPUT_BUTTON_BACK,             // BACK�{�^��
    LeftThumb =             XINPUT_BUTTON_LEFT_THUMB,       // ���X�e�B�b�N��������
    RightThumb =            XINPUT_BUTTON_RIGHT_THUMB,      // �E�X�e�B�b�N��������
    LeftShoulder =          XINPUT_BUTTON_LEFT_SHOULDER,    // LB�{�^��
    RightShoulder =         XINPUT_BUTTON_RIGHT_SHOULDER,   // RB�{�^��
    A =                     XINPUT_BUTTON_A,                // A�{�^��
    B =                     XINPUT_BUTTON_B,                // B�{�^��
    X =                     XINPUT_BUTTON_X,                // X�{�^��
    Y =                     XINPUT_BUTTON_Y,                // Y�{�^��
};

// XInput�̃A�i���O�lID
enum class XInputAnalogID : unsigned char
{
    LeftTrigger = 0,
    RightTrigger,
    ThumbLX,
    ThumbLY,
    ThumbRX,
    ThumbRY
};

// ���̓N���X
class XInput
{
public:
    static XINPUT_STATE prevState; // 1�t���[���O�̏��
    static XINPUT_STATE currentState; // ���݂̏��

    // �������B�ŏ���1�񂾂��Ă�ł��������B
    static void Init();

    // �ŐV�̓��͏󋵂ɍX�V���鏈���B
    // ���t���[���̍ŏ��Ɂi�Q�[���̏�������Ɂj�Ă�ł��������B
    static void Update();

    // �{�^����������Ă��邩�H
    static bool GetButton(XInputDigitalID id);

    // �{�^���������ꂽ�u�Ԃ��H
    static bool GetButtonDown(XInputDigitalID id);

    // �{�^���������ꂽ�u�Ԃ��H
    static bool GetButtonUp(XInputDigitalID id);

    // �A�i���O�l���w��̒l�ȏォ?
    static bool GetAnalogInput(XInputAnalogID id, short min);

    // �A�i���O�l���w��̒l�ȏ�ɂȂ����u�Ԃ�?
    static bool GetAnalogInputMoment(XInputAnalogID id, short min);

    // �X�e�B�b�N�̃A�i���O�l�x�N�^�[�̒������w��̒l�ȏォ?
    static bool GetStickMove(bool isLeft, float min);

    // �X�e�B�b�N�̃A�i���O�l�x�N�^�[�̒������w��̒l�ȏ�ɂȂ����u�Ԃ�?
    static bool GetStickMoveMoment(bool isLeft, float min);

    // �A�i���O�l���擾����
    static short GetAnalogPoint(XInputAnalogID id);

    // �X�e�B�b�N�̃A�i���O�l��Vector2�ŕԂ�
    static Vector2 GetStickState(bool isLeft);
};
#endif