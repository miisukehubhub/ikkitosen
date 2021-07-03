#ifndef MYRANDOM_H_
#define MYRANDOM_H_

#include <random>

#include "../Vector2/Vector2.h"

class MyRandom
{
public:

	// �͈͗���(����)
	static int RandomRange(int minValue, int maxValue);

	// �͈͗���(����)
	static float RandomRange(float minValue, float maxValue);

	// �͈͗���(Vector2�A�l�p�`�͈̔�)
	static Vector2 RandomRange(Vector2 minValue, Vector2 maxValue);

	// �͈͗���(Vector2�A�~�͈̔�)
	static Vector2 RandomRange(Vector2 center, float r);

	// �w��̊m����true��Ԃ�
	static bool Probab(float probability);

private:

	static std::random_device seed_gen;
	static std::mt19937 engine;
};

#endif
