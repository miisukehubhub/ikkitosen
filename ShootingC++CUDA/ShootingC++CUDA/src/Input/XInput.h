#ifndef INPUT_H_
#define INPUT_H_

#include <DxLib.h>

#include "../Vector2/Vector2.h"

// XInputのID
enum class XInputDigitalID : unsigned char
{
    Up =                    XINPUT_BUTTON_DPAD_UP,          // デジタル方向ボタン上
    Down =                  XINPUT_BUTTON_DPAD_DOWN,        // デジタル方向ボタン下
    Left =                  XINPUT_BUTTON_DPAD_LEFT,        // デジタル方向ボタン左
    Right =                 XINPUT_BUTTON_DPAD_RIGHT,       // デジタル方向ボタン右
    Start =                 XINPUT_BUTTON_START,            // STARTボタン
    Back =                  XINPUT_BUTTON_BACK,             // BACKボタン
    LeftThumb =             XINPUT_BUTTON_LEFT_THUMB,       // 左スティック押し込み
    RightThumb =            XINPUT_BUTTON_RIGHT_THUMB,      // 右スティック押し込み
    LeftShoulder =          XINPUT_BUTTON_LEFT_SHOULDER,    // LBボタン
    RightShoulder =         XINPUT_BUTTON_RIGHT_SHOULDER,   // RBボタン
    A =                     XINPUT_BUTTON_A,                // Aボタン
    B =                     XINPUT_BUTTON_B,                // Bボタン
    X =                     XINPUT_BUTTON_X,                // Xボタン
    Y =                     XINPUT_BUTTON_Y,                // Yボタン
};

// XInputのアナログ値ID
enum class XInputAnalogID : unsigned char
{
    LeftTrigger = 0,
    RightTrigger,
    ThumbLX,
    ThumbLY,
    ThumbRX,
    ThumbRY
};

// 入力クラス
class XInput
{
public:
    static XINPUT_STATE prevState; // 1フレーム前の状態
    static XINPUT_STATE currentState; // 現在の状態

    // 初期化。最初に1回だけ呼んでください。
    static void Init();

    // 最新の入力状況に更新する処理。
    // 毎フレームの最初に（ゲームの処理より先に）呼んでください。
    static void Update();

    // ボタンが押されているか？
    static bool GetButton(XInputDigitalID id);

    // ボタンが押された瞬間か？
    static bool GetButtonDown(XInputDigitalID id);

    // ボタンが離された瞬間か？
    static bool GetButtonUp(XInputDigitalID id);

    // アナログ値が指定の値以上か?
    static bool GetAnalogInput(XInputAnalogID id, short min);

    // アナログ値が指定の値以上になった瞬間か?
    static bool GetAnalogInputMoment(XInputAnalogID id, short min);

    // スティックのアナログ値ベクターの長さが指定の値以上か?
    static bool GetStickMove(bool isLeft, float min);

    // スティックのアナログ値ベクターの長さが指定の値以上になった瞬間か?
    static bool GetStickMoveMoment(bool isLeft, float min);

    // アナログ値を取得する
    static short GetAnalogPoint(XInputAnalogID id);

    // スティックのアナログ値をVector2で返す
    static Vector2 GetStickState(bool isLeft);
};
#endif