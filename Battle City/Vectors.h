#pragma once

#include <string>

class Vector2
{
public:
	static Vector2 up, down, right, left;

	double x, y;

	Vector2();
	Vector2(double X, double Y);
	~Vector2();

	Vector2 operator +(Vector2 foo);
	Vector2 operator -(Vector2 foo);

	Vector2 operator *(double foo);
	double operator *(Vector2 foo);

	void operator +=(Vector2 foo);
	void operator -=(Vector2 foo);
	
	bool operator ==(Vector2 foo);

	Vector2 Normalize();

	double VectorAngle(Vector2 foo);

	double Magnitude();

	std::string toString();
};