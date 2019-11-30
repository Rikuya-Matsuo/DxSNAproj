#pragma once
#include <cmath>

struct Vector2D
{
	// コンストラクタ
	Vector2D(float in_x = 0.0f, float in_y = 0.0f):
		x(in_x),
		y(in_y)
	{
	}

	// メンバ
	float x, y;



	// 静的値
	static const Vector2D zero;
	static const Vector2D axisX;
	static const Vector2D axisY;



	// 関数
	float LengthSq() const { return x * x + y * y; }

	float Length() const { return sqrtf(LengthSq()); }



	// 演算子
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
