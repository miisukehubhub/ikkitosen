#include "ProgressBar.h"

#include <DxLib.h>

ProgressBar::ProgressBar(Vector2 position, int width, int height, int* maxPoint, int* point, unsigned int color)
	:UI(position)
	, m_width(width)
	, m_height(height)
	, m_maxPoint(maxPoint)
	, m_point(point)
	, m_color(color)
{
}

void ProgressBar::Update()
{
	length = (float)*m_point / *m_maxPoint;
}

void ProgressBar::Draw()
{
	DrawBoxAA(m_position.x, m_position.y, m_position.x + m_width * length, m_position.y + m_height, m_color, TRUE);
	DrawBoxAA(m_position.x, m_position.y, m_position.x + m_width, m_position.y + m_height, GetColor(100, 100, 100), FALSE, 3.0f);
}

void ProgressBar::ChangeReference(int* maxPoint, int* point)
{
	m_maxPoint = maxPoint;
	m_point = point;
}
