#include "Vector2.h"

// 指定ベクトルから単位ベクトルを作成
Vector2 Vector2::normalize(const Vector2& value)
{
	return value.normalized();
}

// 2つのベクトルのなす角を返す
float Vector2::angle(const Vector2& vector1, const Vector2& vector2)
{
	float cos = dot(vector1, vector2) / (vector1.length() * vector2.length());
	return std::acosf(cos);
}

// 2つのベクトルの内積を計算
float Vector2::dot(const Vector2& vector1, const Vector2& vector2)
{
	float dot = vector1.x * vector2.y + vector1.y * vector2.x;
	return dot;
	// cosθ = dot() / vector1.length() * vector2.length()
}

// 2つのベクトルの外積を計算
float Vector2::cross(const Vector2& vector1, const Vector2& vector2)
{
	float cross = vector1.x * vector2.y - vector1.y * vector2.x;
	return cross;
	// sinθ = cross() / vector1.length() * vector2.length()
}

// 2つのベクトル間の距離を計算
float Vector2::distance(const Vector2& vector1, const Vector2& vector2)
{
	return (vector1 - vector2).length();
}

// 2つのベクトル間の線形補間を行う
Vector2 Vector2::lerp(const Vector2& value1, const Vector2& value2, float amount)
{
	return (1 - amount) * value1 + amount * value2;
}

// 値を指定された範囲内に制限する
Vector2 Vector2::clamp(const Vector2& value1, const Vector2& min, const Vector2& max)
{
	Vector2 clampVector = value1;
	if (clampVector.x < min.x)
	{
		clampVector.setValue(min.x, clampVector.y);
	}
	else if (clampVector.x > max.x)
	{
		clampVector.setValue(max.x, clampVector.y);
	}

	if (clampVector.y < min.y)
	{
		clampVector.setValue(clampVector.x, min.y);
	}
	else if (clampVector.y > max.y)
	{
		clampVector.setValue(clampVector.x, max.y);
	}

	return clampVector;
}

// 大きさをmaxLengthまで制限した値を取得する
Vector2 Vector2::clampLength(const Vector2& vector1, float maxLength)
{
	Vector2 clampVector = vector1;
	if (clampVector.lengthSquared() > maxLength * maxLength)
	{
		clampVector *= maxLength / clampVector.length();
	}
	return clampVector;
}

// 引数のベクトルの垂直方向のベクトルを取得
Vector2 Vector2::perpendicular(const Vector2& inDirection)
{
	Vector2 perpVec = Vector2_v::zero;
	perpVec.x = inDirection.y;
	perpVec.y = -inDirection.x;
	return perpVec;
}

// 法線を基準にしてベクトルに反射したベクトルを取得する
Vector2 Vector2::reflect(const Vector2& inDirection, const Vector2& inNormal)
{
	Vector2 reflectVector = inDirection + 2 * dot(-inDirection, inNormal) * inNormal;
	return reflectVector;
}

// 2つのベクトルの各成分を乗算する
Vector2 Vector2::scale(const Vector2& vector1, const Vector2& vector2)
{
	Vector2 scaleVector = vector1;
	scaleVector.x *= vector2.x;
	scaleVector.y *= vector2.y;
	return scaleVector;
}

// ベクトルの長さ
float Vector2::length() const
{
	return std::sqrtf(x * x + y * y);
}

// 単位ベクトルを取得する
Vector2 Vector2::normalized() const
{
	return Vector2(x / length(), y / length());
}

// 自身と引数の値が代替同じだったら真を返す
bool Vector2::equals(const Vector2& other)
{
	bool equalX = x * 1.005f >= other.x && x * 0.995f <= other.x;
	bool equalY = y * 1.005f >= other.y && y * 0.995f <= other.y;
	return equalX && equalY;
}

// 値を再設定する
void Vector2::setValue(float x, float y)
{
	this->x = x;
	this->y = y;
}

// ベクトルの値を文字列に起こしたものを取得
std::string Vector2::toString() const
{
	return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
}