#ifndef UI_H_
#define UI_H_

#include "../Vector2/Vector2.h"

class UI
{
public:

	UI(Vector2 position) :m_position(position){} // コンストラクタ

	virtual ~UI() = default; // デストラクタ

	virtual void Update() = 0; // 更新処理

	virtual void Draw() = 0; // 描画処理

	virtual bool IsClick() { return false; } // クリックされたかどうか

protected:

	Vector2 m_position;
};

#endif
