#ifndef MOUSEINPUT_H_
#define MOUSEINPUT_H_

#include <DxLib.h>
#include "../Vector2/Vector2.h"

// ���̓N���X
class MouseInput
{
public:
    static int prevState; // 1�t���[���O�̏��
    static int currentState; // ���݂̏��


    // �������B�ŏ���1�񂾂��Ă�ł��������B
    static void Init();

    // �ŐV�̓��͏󋵂ɍX�V���鏈���B
    // ���t���[���̍ŏ��Ɂi�Q�[���̏�������Ɂj�Ă�ł��������B
    static void Update();

    // �}�E�X�̈ʒu���擾
    static Vector2 GetPosition();

    // �{�^����������Ă��邩�H
    static bool GetButton(int buttonId);

    // �{�^���������ꂽ�u�Ԃ��H
    static bool GetButtonDown(int buttonId);

    // �{�^���������ꂽ�u�Ԃ��H
    static bool GetButtonUp(int buttonId);

};

// MouseInput��ID�\����
struct MouseInputID
{
    static constexpr int Left{ MOUSE_INPUT_LEFT }; // ���{�_��
    static constexpr int Right{ MOUSE_INPUT_RIGHT }; // �E�{�^��
    static constexpr int Middle{ MOUSE_INPUT_MIDDLE }; // ���{�^��
};
#endif