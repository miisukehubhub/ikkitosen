#ifndef DINPUT_H_
#define DINPUT_H_

#include <DxLib.h>

// ���̓N���X
class DInput
{
public:
    static int prevState; // 1�t���[���O�̏��
    static int currentState; // ���݂̏��

    // �������B�ŏ���1�񂾂��Ă�ł��������B
    static void Init();

    // �ŐV�̓��͏󋵂ɍX�V���鏈���B
    // ���t���[���̍ŏ��Ɂi�Q�[���̏�������Ɂj�Ă�ł��������B
    static void Update();

    // �{�^����������Ă��邩�H
    static bool GetButton(int buttonId);

    // �{�^���������ꂽ�u�Ԃ��H
    static bool GetButtonDown(int buttonId);

    // �{�^���������ꂽ�u�Ԃ��H
    static bool GetButtonUp(int buttonId);

};

// DirectInput��ID�\����
struct DInputID
{
    static constexpr int ZKey{ PAD_INPUT_1 }; // �p�b�h��A�{�^��
    static constexpr int XKey{ PAD_INPUT_2 }; // �p�b�h��B�{�^��
    static constexpr int CKey{ PAD_INPUT_3 }; // �p�b�h��X�{�^��
    static constexpr int AKey{ PAD_INPUT_4 }; // �p�b�h��Y�{�^��
    static constexpr int SKey{ PAD_INPUT_5 }; // �p�b�h��LB�{�^��
    static constexpr int DKey{ PAD_INPUT_6 }; // �p�b�h��RB�{�^��
    static constexpr int QKey{ PAD_INPUT_7 }; // �p�b�h��BACK�{�^��
    static constexpr int WKey{ PAD_INPUT_8 }; // �p�b�h��START�{�^��
    static constexpr int LeftKey{ PAD_INPUT_LEFT };
    static constexpr int RightKey{ PAD_INPUT_RIGHT };
    static constexpr int UpKey{ PAD_INPUT_UP };
    static constexpr int DownKey{ PAD_INPUT_DOWN };
};
#endif