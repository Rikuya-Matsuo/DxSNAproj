#pragma once
#include <cmath>

struct Vector2D
{
	// �R���X�g���N�^
	Vector2D(float in_x = 0.0f, float in_y = 0.0f):
		x(in_x),
		y(in_y)
	{
	}

	// �����o
	float x, y;



	// �ÓI�l
	static const Vector2D zero;
	static const Vector2D axisX;
	static const Vector2D axisY;



	// �֐�
	float LengthSq() const { return x * x + y * y; }

	float Length() const { return sqrtf(LengthSq()); }



	// ���Z�q
	Vector2D operator+ (Vector2D & rhs)
	{
		return Vector2D(this->x + rhs.x, this->y + rhs.y);
	}

	Vector2D operator- (Vector2D & rhs)
	{
		return Vector2D(this->x - rhs.x, this->y - rhs.y);
	}

	Vector2D operator* (float f)
	{
		return Vector2D(this->x * f, this->y * f);
	}

	Vector2D & operator+= (Vector2D & rhs)
	{
		this->x += rhs.x;
		this->y += rhs.y;
		return *this;
	}

	Vector2D & operator-= (Vector2D & rhs)
	{
		this->x -= rhs.x;
		this->y -= rhs.y;
		return *this;
	}

	Vector2D & operator*= (float f)
	{
		this->x *= f;
		this->y *= f;
		return *this;
	}
};
