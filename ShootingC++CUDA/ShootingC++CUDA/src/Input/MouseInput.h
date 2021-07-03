#ifndef MOUSEINPUT_H_
#define MOUSEINPUT_H_

#include <DxLib.h>
#include "../Vector2/Vector2.h"

// 入力クラス
class MouseInput
{
public:
    static int prevState; // 1フレーム前の状態
    static int currentState; // 現在の状態


    // 初期化。最初に1回だけ呼んでください。
    static void Init();

    // 最新の入力状況に更新する処理。
    // 毎フレームの最初に（ゲームの処理より先に）呼んでください。
    static void Update();

    // マウスの位置を取得
    static Vector2 GetPosition();

    // ボタンが押されているか？
    static bool GetButton(int buttonId);

    // ボタンが押された瞬間か？
    static bool GetButtonDown(int buttonId);

    // ボタンが離された瞬間か？
    static bool GetButtonUp(int buttonId);

};

// MouseInputのID構造体
struct MouseInputID
{
    static constexpr int Left{ MOUSE_INPUT_LEFT }; // 左ボダン
    static constexpr int Right{ MOUSE_INPUT_RIGHT }; // 右ボタン
    static constexpr int Middle{ MOUSE_INPUT_MIDDLE }; // 中ボタン
};
#endif