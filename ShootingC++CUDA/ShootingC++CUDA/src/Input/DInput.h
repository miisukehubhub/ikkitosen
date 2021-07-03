#ifndef DINPUT_H_
#define DINPUT_H_

#include <DxLib.h>

// 入力クラス
class DInput
{
public:
    static int prevState; // 1フレーム前の状態
    static int currentState; // 現在の状態

    // 初期化。最初に1回だけ呼んでください。
    static void Init();

    // 最新の入力状況に更新する処理。
    // 毎フレームの最初に（ゲームの処理より先に）呼んでください。
    static void Update();

    // ボタンが押されているか？
    static bool GetButton(int buttonId);

    // ボタンが押された瞬間か？
    static bool GetButtonDown(int buttonId);

    // ボタンが離された瞬間か？
    static bool GetButtonUp(int buttonId);

};

// DirectInputのID構造体
struct DInputID
{
    static constexpr int ZKey{ PAD_INPUT_1 }; // パッドはAボタン
    static constexpr int XKey{ PAD_INPUT_2 }; // パッドはBボタン
    static constexpr int CKey{ PAD_INPUT_3 }; // パッドはXボタン
    static constexpr int AKey{ PAD_INPUT_4 }; // パッドはYボタン
    static constexpr int SKey{ PAD_INPUT_5 }; // パッドはLBボタン
    static constexpr int DKey{ PAD_INPUT_6 }; // パッドはRBボタン
    static constexpr int QKey{ PAD_INPUT_7 }; // パッドはBACKボタン
    static constexpr int WKey{ PAD_INPUT_8 }; // パッドはSTARTボタン
    static constexpr int LeftKey{ PAD_INPUT_LEFT };
    static constexpr int RightKey{ PAD_INPUT_RIGHT };
    static constexpr int UpKey{ PAD_INPUT_UP };
    static constexpr int DownKey{ PAD_INPUT_DOWN };
};
#endif