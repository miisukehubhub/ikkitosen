#ifndef BUTTON_H_
#define BUTTON_H_

#include <string>

#include "../UI.h"

class Button : public UI
{
public:

	Button(Vector2 position, int width, int height, std::string text); // コンストラクタ

	void Update() override; // 更新処理

	void Draw() override; // 描画処理

	bool IsClick() override; // クリックされたかどうか

private:

	int m_width;
	int m_height;
	std::string m_text;
	bool isClick{ false };
};

#endif