#include "MyRandom.h"

std::random_device MyRandom::seed_gen{};
std::mt19937 MyRandom::engine(seed_gen());

int MyRandom::RandomRange(int minValue, int maxValue)
{
	std::uniform_int_distribution<int> dist(minValue, maxValue);
	return dist(engine);
}

float MyRandom::RandomRange(float minValue, float maxValue)
{
	std::uniform_real_distribution<float> dist(minValue, maxValue);
	return dist(engine);
}

Vector2 MyRandom::RandomRange(Vector2 minValue, Vector2 maxValue)
{
	std::uniform_real_distribution<float> distX(minValue.x, maxValue.x);
	std::uniform_real_distribution<float> distY(minValue.y, maxValue.y);
	Vector2 v = Vector2(distX(engine), distY(engine));
	return v;
}

Vector2 MyRandom::RandomRange(Vector2 center, float r)
{
	Vector2 v = center;
	float len = MyRandom::RandomRange(0.0f, r);
	float ang = MyRandom::RandomRange(0.f, 3.14159265f);
	v.x += std::cosf(ang) * len;
	v.y += std::sinf(ang) * len;
	return v;
}

bool MyRandom::Probab(float probability)
{
	return probability >= RandomRange(0.0f, 1.0f);
}