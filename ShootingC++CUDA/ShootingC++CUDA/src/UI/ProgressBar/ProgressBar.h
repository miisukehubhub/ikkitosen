#ifndef PROGRESSBAR_H_
#define PROGRESSBAR_H_

#include "../UI.h"

class ProgressBar : public UI
{
public:

	ProgressBar(Vector2 position, int width, int height, int* maxPoint, int* point, unsigned int color); // コンストラクタ

	void Update() override; // 更新処理

	void Draw() override; // 描画処理

	void ChangeReference(int* maxPoint, int* point); // 参照する値を変える

private:

	int m_width;
	int m_height;
	int* m_maxPoint;
	int* m_point;
	unsigned int m_color;
	float length{ 1.0f };
};

#endif