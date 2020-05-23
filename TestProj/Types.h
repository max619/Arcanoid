#pragma once
#include "stdafx.h"

template<typename T>
struct Vector
{
	Vector() : x(0), y(0) {};
	Vector(T x, T y) : x(x), y(y) {}

	T x, y;

	Vector<T> operator+ (const Vector<T>& lhs)
	{
		return Vector<T>(x + lhs.x, y + lhs.y);
	}
	Vector<T> operator- (const Vector<T>& lhs)
	{
		return Vector<T>(x - lhs.x, y - lhs.y);
	}

	T operator* (const Vector<T>& lhs)
	{
		return lhs.x * x + lhs.y * y;
	}

	Vector<T> operator*(T value)
	{
		return Vector<T>(x * value, y * value);
	}

	Vector<T> operator/(T value)
	{
		return Vector<T>(x / value, y / value);
	}

	T Cross(const Vector<T>& lhs)
	{		
		return x * lhs.y - y * lhs.x;
	}

	T SqrMagnitude()
	{
		return x * x + y * y;
	}
	T Magnitude()
	{
		return static_cast<T>(std::sqrtf(SqrMagnitude()));
	}

	void operator+=(const Vector<T>& lhs)
	{
		*this = *this + lhs;
	}

	Vector<T> Normalized()
	{
		return *this / Magnitude();
	}

	template<typename Dt>
	operator Vector<Dt>()
	{
		return Vector<Dt>(static_cast<Dt>(x), static_cast<Dt>(y));
	}
};

template<typename T>
struct Rectangle2D
{
	Rectangle2D() : left(0), top(0), right(0), bottom(0){}
	Rectangle2D(T left, T top, T right, T bottom) : left(left), top(top), right(right), bottom(bottom){}
	Rectangle2D(Vector<T> a, Vector<T> b) : left(std::min(a.x, b.x)), top(std::min(a.y, b.y)), right(std::max(a.x, b.x)), bottom(std::max(a.y, b.y)) {}
	T left, top, right, bottom;

	bool Intersects(const Rectangle2D<T>& other)
	{
		return !(left > other.right
			|| right < other.left
			|| top > other.bottom
			|| bottom < other.top
			);
	}

};

struct Color
{
	union
	{
		uint32_t i;
		unsigned char data[4];
	};

	Color(unsigned char r, unsigned char g, unsigned char b)
	{
		data[0] = r;
		data[1] = g;
		data[2] = b;
		data[3] = 255;
	}
	Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
	{
		data[0] = r;
		data[1] = g;
		data[2] = b;
		data[3] = a;
	}
};
