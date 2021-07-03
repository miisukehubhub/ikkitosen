#include "Vector2.h"

// �w��x�N�g������P�ʃx�N�g�����쐬
Vector2 Vector2::normalize(const Vector2& value)
{
	return value.normalized();
}

// 2�̃x�N�g���̂Ȃ��p��Ԃ�
float Vector2::angle(const Vector2& vector1, const Vector2& vector2)
{
	float cos = dot(vector1, vector2) / (vector1.length() * vector2.length());
	return std::acosf(cos);
}

// 2�̃x�N�g���̓��ς��v�Z
float Vector2::dot(const Vector2& vector1, const Vector2& vector2)
{
	float dot = vector1.x * vector2.y + vector1.y * vector2.x;
	return dot;
	// cos�� = dot() / vector1.length() * vector2.length()
}

// 2�̃x�N�g���̊O�ς��v�Z
float Vector2::cross(const Vector2& vector1, const Vector2& vector2)
{
	float cross = vector1.x * vector2.y - vector1.y * vector2.x;
	return cross;
	// sin�� = cross() / vector1.length() * vector2.length()
}

// 2�̃x�N�g���Ԃ̋������v�Z
float Vector2::distance(const Vector2& vector1, const Vector2& vector2)
{
	return (vector1 - vector2).length();
}

// 2�̃x�N�g���Ԃ̐��`��Ԃ��s��
Vector2 Vector2::lerp(const Vector2& value1, const Vector2& value2, float amount)
{
	return (1 - amount) * value1 + amount * value2;
}

// �l���w�肳�ꂽ�͈͓��ɐ�������
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

// �傫����maxLength�܂Ő��������l���擾����
Vector2 Vector2::clampLength(const Vector2& vector1, float maxLength)
{
	Vector2 clampVector = vector1;
	if (clampVector.lengthSquared() > maxLength * maxLength)
	{
		clampVector *= maxLength / clampVector.length();
	}
	return clampVector;
}

// �����̃x�N�g���̐��������̃x�N�g�����擾
Vector2 Vector2::perpendicular(const Vector2& inDirection)
{
	Vector2 perpVec = Vector2_v::zero;
	perpVec.x = inDirection.y;
	perpVec.y = -inDirection.x;
	return perpVec;
}

// �@������ɂ��ăx�N�g���ɔ��˂����x�N�g�����擾����
Vector2 Vector2::reflect(const Vector2& inDirection, const Vector2& inNormal)
{
	Vector2 reflectVector = inDirection + 2 * dot(-inDirection, inNormal) * inNormal;
	return reflectVector;
}

// 2�̃x�N�g���̊e��������Z����
Vector2 Vector2::scale(const Vector2& vector1, const Vector2& vector2)
{
	Vector2 scaleVector = vector1;
	scaleVector.x *= vector2.x;
	scaleVector.y *= vector2.y;
	return scaleVector;
}

// �x�N�g���̒���
float Vector2::length() const
{
	return std::sqrtf(x * x + y * y);
}

// �P�ʃx�N�g�����擾����
Vector2 Vector2::normalized() const
{
	return Vector2(x / length(), y / length());
}

// ���g�ƈ����̒l����֓�����������^��Ԃ�
bool Vector2::equals(const Vector2& other)
{
	bool equalX = x * 1.005f >= other.x && x * 0.995f <= other.x;
	bool equalY = y * 1.005f >= other.y && y * 0.995f <= other.y;
	return equalX && equalY;
}

// �l���Đݒ肷��
void Vector2::setValue(float x, float y)
{
	this->x = x;
	this->y = y;
}

// �x�N�g���̒l�𕶎���ɋN���������̂��擾
std::string Vector2::toString() const
{
	return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
}