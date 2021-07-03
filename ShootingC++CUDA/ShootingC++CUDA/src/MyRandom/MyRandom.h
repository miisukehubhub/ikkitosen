#ifndef MYRANDOM_H_
#define MYRANDOM_H_

#include <random>

#include "../Vector2/Vector2.h"

class MyRandom
{
public:

	// 範囲乱数(整数)
	static int RandomRange(int minValue, int maxValue);

	// 範囲乱数(実数)
	static float RandomRange(float minValue, float maxValue);

	// 範囲乱数(Vector2、四角形の範囲)
	static Vector2 RandomRange(Vector2 minValue, Vector2 maxValue);

	// 範囲乱数(Vector2、円の範囲)
	static Vector2 RandomRange(Vector2 center, float r);

	// 指定の確率でtrueを返す
	static bool Probab(float probability);

private:

	static std::random_device seed_gen;
	static std::mt19937 engine;
};

#endif
