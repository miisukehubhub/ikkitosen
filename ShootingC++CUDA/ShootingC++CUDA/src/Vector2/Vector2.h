#ifndef VECTOR2_H_
#define VECTOR2_H_

#include <string>
#include <cmath>
#include <cuda_runtime.h>

struct Vector2
{
public:

	// コンストラクタ
	constexpr Vector2() = default;
	constexpr Vector2(float value) : x(value), y(value) {}
	__device__ __host__ constexpr Vector2(float x, float y) : x(x), y(y) {}

public:

	// 指定ベクトルから単位ベクトルを作成
	static Vector2 normalize(const Vector2& value);

	// 2つのベクトルのなす角を返す
	static float angle(const Vector2& vector1, const Vector2& vector2);

	// 2つのベクトルの内積を計算
	static float dot(const Vector2& vector1, const Vector2& vector2);

	// 2つのベクトルの外積を計算
	static float cross(const Vector2& vector1, const Vector2& vector2);

	// 2つのベクトル間の距離を計算
	static float distance(const Vector2& vector1, const Vector2& vector2);

	// 2つのベクトル間の線形補間を行う
	static Vector2 lerp(const Vector2& value1, const Vector2& value2, float amount);

	// 値を指定された範囲内に制限する
	static Vector2 clamp(const Vector2& value1, const Vector2& min, const Vector2& max);

	// 大きさをmaxLengthまで制限した値を取得する
	static Vector2 clampLength(const Vector2& vector1, float maxLength);

	// 引数のベクトルの垂直方向のベクトルを取得
	static Vector2 perpendicular(const Vector2& inDirection);

	// 法線を基準にしてベクトルに反射したベクトルを取得する
	static Vector2 reflect(const Vector2& inDirection, const Vector2& inNormal);

	// 2つのベクトルの各成分を乗算する
	static Vector2 scale(const Vector2& vector1, const Vector2& vector2);

public:

	// ベクトルの長さ
	float length() const;

	// ベクトルの長さの平方
	__device__ __host__ float lengthSquared() const
	{
		return x * x + y * y;
	}

	// 単位ベクトルを取得する
	Vector2 normalized() const;

	// 自身と引数の値が代替同じだったら真を返す
	bool equals(const Vector2& other);

	// 値を再設定する
	void setValue(float x, float y);

	// ベクトルの値を文字列に起こしたものを取得
	std::string toString() const;

public:

	// 各要素
	float x{ 0.0f };
	float y{ 0.0f };
};

// Vector2構造体の定数達
struct Vector2_v
{
	static constexpr Vector2 zero{ 0.0f };
	static constexpr Vector2 one{ 1.0f };
	static constexpr Vector2 up{ 0.0f,1.0f };
	static constexpr Vector2 down{ 0.0f,-1.0f };
	static constexpr Vector2 left{ -1.0f,0.0f };
	static constexpr Vector2 right{ 1.0f,0.0f };
};

// 演算子オーバーロード達
template <class T>
__device__ __host__ static Vector2& operator *= (Vector2& v, T s)
{
	v.x *= s;
	v.y *= s;
	return v;
}
template <class T>
__device__ __host__ static Vector2& operator /= (Vector2& v, T s)
{
	v.x /= s;
	v.y /= s;
	return v;
}
template <class T>
__device__ __host__ static Vector2 operator * (Vector2 v, T s)
{
	return v *= s;
}
template<class T>
__device__ __host__ static Vector2 operator * (T s, Vector2 v)
{
	return v *= s;
}
template <class T>
__device__ __host__ static Vector2 operator / (Vector2 v, T s)
{
	return v /= s;
}
__device__ __host__ static Vector2 operator - (const Vector2& v)
{
	return v * -1;
}
__device__ __host__ static Vector2& operator += (Vector2& v1, const Vector2& v2)
{
	v1.x += v2.x;
	v1.y += v2.y;
	return v1;
}
__device__ __host__ static Vector2& operator -= (Vector2& v1, const Vector2& v2)
{
	v1.x -= v2.x;
	v1.y -= v2.y;
	return v1;
}
__device__ __host__ static Vector2 operator + (Vector2 v1, const Vector2& v2)
{
	return v1 += v2;
}
__device__ __host__ static Vector2 operator - (Vector2 v1, const Vector2& v2)
{
	return v1 -= v2;
}
__device__ __host__ static bool operator == (const Vector2& lhs, const Vector2& rhs)
{
	return lhs.x == rhs.x && lhs.y == rhs.y;
}
__device__ __host__ static bool operator != (const Vector2& lhs, const Vector2& rhs)
{
	return !(lhs == rhs);
}

#endif
