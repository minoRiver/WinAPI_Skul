#pragma once

struct Vector2
{
	float x;
	float y;

public:
	Vector2()
		: x(0.f)
		, y(0.f)
	{}

	Vector2(POINT pt)
		: x((float)pt.x)
		, y((float)pt.y)
	{}

	Vector2(float _x, float _y)
		: x(_x)
		, y(_y)
	{}

	Vector2(int _x, int _y)
		: x((float)_x)
		, y((float)_y)
	{}

public:
	Vector2& operator =(POINT pt)
	{
		this->x = (float)pt.x;
		this->y = (float)pt.y;

		return *this;
	}

	Vector2 operator -()
	{
		return Vector2(-x, -y);
	}

	Vector2 operator +(const Vector2& other)
	{
		return Vector2(x + other.x, y + other.y);
	}

	Vector2 operator -(const Vector2& other)
	{
		return Vector2(x - other.x, y - other.y);
	}

	Vector2 operator *(float scalar)
	{
		return Vector2(x * scalar, y * scalar);
	}

	Vector2 operator *(int scalar)
	{
		return Vector2(x * (float)scalar, y * (float)scalar);
	}

	Vector2 operator /(float scalar)
	{
		return Vector2(x / scalar, y / scalar);
	}

	Vector2 operator /(int scalar)
	{
		return Vector2(x / (float)scalar, y / (float)scalar);
	}

	Vector2& operator +=(Vector2 other)
	{
		x += other.x;
		y += other.y;

		return *this;
	}

	Vector2& operator -=(Vector2 other)
	{
		x -= other.x;
		y -= other.y;

		return *this;
	}

	Vector2& operator *=(float scalar)
	{
		x *= scalar;
		y *= scalar;

		return *this;
	}

public:
	bool IsZero()
	{
		if (0.f == x && y == 0.f)
			return true;

		return false;
	}

	float Length()
	{
		return sqrtf(x * x + y * y);
	}

	Vector2& Normalize()
	{
		float length = Length();

		assert(length != 0.f);

		x /= length;
		y /= length;

		return *this;
	}
};