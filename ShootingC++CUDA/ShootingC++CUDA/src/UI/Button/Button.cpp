#include "Button.h"

#include <DxLib.h>

#include "../../Input/MouseInput.h"

Button::Button(Vector2 position, int width, int height, std::string text)
	:UI(position)
	,m_width(width)
	,m_height(height)
	,m_text(text)
{

}

void Button::Update()
{
	
}

void Button::Draw()
{
	DrawBoxAA(m_position.x, m_position.y, m_position.x + m_width, m_position.y + m_height, GetColor(255, 255, 255), TRUE);

	DrawFormatStringF(m_position.x + 20, m_position.y + 20, 0, m_text.c_str());
}

bool Button::IsClick()
{
	Vector2 mPos = MouseInput::GetPosition();
	if (mPos.x >= m_position.x &&
		mPos.x <= m_position.x + m_width &&
		mPos.y >= m_position.y &&
		mPos.y <= m_position.y + m_height)
	{
		if (MouseInput::GetButtonDown(MouseInputID::Left))
		{
			return true;
		}
	}

	return false;
}