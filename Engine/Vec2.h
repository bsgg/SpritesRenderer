#pragma once

#include <cmath>

template<typename T>  
class Vec2
{
public:
	Vec2() = default;
	Vec2(T x_in, T y_in)
		:
		x(x_in),
		y(y_in)
	{
	}

	Vec2 operator+(const Vei2& rhs) const
	{
		return Vei2(x + rhs.x, y + rhs.y);
	}

	Vec2& operator+=(const Vei2& rhs)
	{
		return *this = *this + rhs;
	}

	Vec2 operator*(int rhs) const
	{
		return Vei2(x * rhs, y * rhs);
	}

	Vec2& operator*=(int rhs)
	{
		return *this = *this * rhs;
	}

	Vec2 operator-(const Vei2& rhs) const
	{
		return Vei2(x - rhs.x, y - rhs.y);
	}

	Vec2& operator-=(const Vei2& rhs)
	{
		return *this = *this - rhs;
	}

	Vec2 operator/(int rhs) const
	{
		return Vei2(x / rhs, y / rhs);
	}

	Vec2& operator/=(int rhs)
	{
		return *this = *this / rhs;
	}

	T GetLength() const
	{
		return std::sqrt(T(GetLengthSq()));
	}

	int GetLengthSq() const
	{
		return x * x + y * y;
	}

	Vec2& Normalize()
	{
		return *this = GetNormalized();
	}

	Vec2_ GetNormalized() const
	{
		const T len = GetLength();
		if (len != (T)0)
		{
			return *this * ((T)1 / len);
		}
		return *this;
	}

public:
	T x;
	T y;
};