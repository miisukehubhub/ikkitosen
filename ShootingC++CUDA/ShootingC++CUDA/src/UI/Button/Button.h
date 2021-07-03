#ifndef BUTTON_H_
#define BUTTON_H_

#include <string>

#include "../UI.h"

class Button : public UI
{
public:

	Button(Vector2 position, int width, int height, std::string text); // �R���X�g���N�^

	void Update() override; // �X�V����

	void Draw() override; // �`�揈��

	bool IsClick() override; // �N���b�N���ꂽ���ǂ���

private:

	int m_width;
	int m_height;
	std::string m_text;
	bool isClick{ false };
};

#endif