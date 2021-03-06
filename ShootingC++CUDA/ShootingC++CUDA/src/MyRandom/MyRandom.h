#ifndef MYRANDOM_H_
#define MYRANDOM_H_

#include <random>

#include "../Vector2/Vector2.h"

class MyRandom
{
public:

	// ÍÍ(®)
	static int RandomRange(int minValue, int maxValue);

	// ÍÍ(À)
	static float RandomRange(float minValue, float maxValue);

	// ÍÍ(Vector2Alp`ÌÍÍ)
	static Vector2 RandomRange(Vector2 minValue, Vector2 maxValue);

	// ÍÍ(Vector2A~ÌÍÍ)
	static Vector2 RandomRange(Vector2 center, float r);

	// wèÌm¦ÅtrueðÔ·
	static bool Probab(float probability);

private:

	static std::random_device seed_gen;
	static std::mt19937 engine;
};

#endif
