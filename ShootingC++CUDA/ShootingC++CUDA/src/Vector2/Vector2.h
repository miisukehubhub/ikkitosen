#ifndef VECTOR2_H_
#define VECTOR2_H_

#include <string>
#include <cmath>
#include <cuda_runtime.h>

struct Vector2
{
public:

	// �R���X�g���N�^
	constexpr Vector2() = default;
	constexpr Vector2(float value) : x(value), y(value) {}
	__device__ __host__ constexpr Vector2(float x, float y) : x(x), y(y) {}

public:

	// �w��x�N�g������P�ʃx�N�g�����쐬
	static Vector2 normalize(const Vector2& value);

	// 2�̃x�N�g���̂Ȃ��p��Ԃ�
	static float angle(const Vector2& vector1, const Vector2& vector2);

	// 2�̃x�N�g���̓��ς��v�Z
	static float dot(const Vector2& vector1, const Vector2& vector2);

	// 2�̃x�N�g���̊O�ς��v�Z
	static float cross(const Vector2& vector1, const Vector2& vector2);

	// 2�̃x�N�g���Ԃ̋������v�Z
	static float distance(const Vector2& vector1, const Vector2& vector2);

	// 2�̃x�N�g���Ԃ̐��`��Ԃ��s��
	static Vector2 lerp(const Vector2& value1, const Vector2& value2, float amount);

	// �l���w�肳�ꂽ�͈͓��ɐ�������
	static Vector2 clamp(const Vector2& value1, const Vector2& min, const Vector2& max);

	// �傫����maxLength�܂Ő��������l���擾����
	static Vector2 clampLength(const Vector2& vector1, float maxLength);

	// �����̃x�N�g���̐��������̃x�N�g�����擾
	static Vector2 perpendicular(const Vector2& inDirection);

	// �@������ɂ��ăx�N�g���ɔ��˂����x�N�g�����擾����
	static Vector2 reflect(const Vector2& inDirection, const Vector2& inNormal);

	// 2�̃x�N�g���̊e��������Z����
	static Vector2 scale(const Vector2& vector1, const Vector2& vector2);

public:

	// �x�N�g���̒���
	float length() const;

	// �x�N�g���̒����̕���
	__device__ __host__ float lengthSquared() const
	{
		return x * x + y * y;
	}

	// �P�ʃx�N�g�����擾����
	Vector2 normalized() const;

	// ���g�ƈ����̒l����֓�����������^��Ԃ�
	bool equals(const Vector2& other);

	// �l���Đݒ肷��
	void setValue(float x, float y);

	// �x�N�g���̒l�𕶎���ɋN���������̂��擾
	std::string toString() const;

public:

	// �e�v�f
	float x{ 0.0f };
	float y{ 0.0f };
};

// Vector2�\���̂̒萔�B
struct Vector2_v
{
	static constexpr Vector2 zero{ 0.0f };
	static constexpr Vector2 one{ 1.0f };
	static constexpr Vector2 up{ 0.0f,1.0f };
	static constexpr Vector2 down{ 0.0f,-1.0f };
	static constexpr Vector2 left{ -1.0f,0.0f };
	static constexpr Vector2 right{ 1.0f,0.0f };
};

// ���Z�q�I�[�o�[���[�h�B
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
