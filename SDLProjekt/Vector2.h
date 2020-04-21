#pragma once

template <typename t>
class Vector2
{
public:
	static Vector2<t> lerp(Vector2<t> start, Vector2<t> end, double progress)
	{
		if (progress >= 1)
			return end;
		if (progress <= 0)
			return start;
		return (end - start)*progress + start;
	}

	Vector2()
	{
	}

	Vector2(t X, t Y)
	{
		x = X;
		y = Y;
	}
	Vector2<t>& operator=(const Vector2<t>& v)
	{
		x = v.x;
		y = v.y;
		return *this;
	}
	Vector2<t> operator+(const Vector2<t>& v2)const
	{
		return Vector2<t>(x + v2.x, y + v2.y);
	}
	Vector2<t> operator-(const Vector2<t>& v2)const
	{
		return Vector2<t>(x - v2.x, y - v2.y);
	}
	Vector2<t> operator*(const Vector2<t>& v2)const
	{
		return Vector2<t>(x*v2.x, y*v2.y);
	}
	Vector2<t> operator*(const t& val)
	{
		return Vector2<t>(x*val, y*val);
	}
	Vector2<t> operator/(const Vector2<t>& v2)const
	{
		return Vector2<t>(x / v2.x, y / v2.y);
	}
	Vector2<t>& operator+=(const Vector2<t>& v)
	{
		x += v.x;
		y += v.y;
		return (*this);
	}
	Vector2<t>& operator-=(const Vector2<t>& v)
	{
		x -= v.x;
		y -= v.y;
		return (*this);
	}
	Vector2<t>& operator*=(const Vector2<t>& v)
	{
		x *= v.x;
		y *= v.y;
		return (*this);
	}
	Vector2<t>& operator/=(const Vector2<t>& v)
	{
		x /= v.x;
		y /= v.y;
		return (*this);
	}
	bool operator==(const Vector2<t>& v)
	{
		return x == v.x && y == v.y;
	}
	bool operator!=(const Vector2<t>& v)
	{
		return x != v.x || y != v.y;
	}
	t x;
	t y;
};

using Vector2f = Vector2<float>;
using Vector2i = Vector2<int>;
