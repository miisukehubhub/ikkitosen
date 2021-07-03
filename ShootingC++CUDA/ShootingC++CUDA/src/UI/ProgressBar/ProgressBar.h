#ifndef PROGRESSBAR_H_
#define PROGRESSBAR_H_

#include "../UI.h"

class ProgressBar : public UI
{
public:

	ProgressBar(Vector2 position, int width, int height, int* maxPoint, int* point, unsigned int color); // �R���X�g���N�^

	void Update() override; // �X�V����

	void Draw() override; // �`�揈��

	void ChangeReference(int* maxPoint, int* point); // �Q�Ƃ���l��ς���

private:

	int m_width;
	int m_height;
	int* m_maxPoint;
	int* m_point;
	unsigned int m_color;
	float length{ 1.0f };
};

#endif