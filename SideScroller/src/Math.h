#pragma once


namespace Math
{
	const float Pi = 3.1415926535f;

	inline float ToDegrees(float radians)
	{
		return radians * 180.0f / Pi;
	}
};

class Vector2
{
public:

	Vector2() : x(0.f), y(0.f)
	{
	}

	explicit Vector2(float inX, float inY) : x(inX), y(inY)
	{ }

	float x;
	float y;

};