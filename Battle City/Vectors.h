#include <math.h>

class Vector2
{
public:
	// Taip daryti yra BUTINA, nes kitaip bus tragista programuoti V
	double x, y;// Vektoriaus x ir y

	Vector2() :x(0.), y(0.) {}
	Vector2(double X, double Y) :x(X), y(Y) {}
	~Vector2() {}

	Vector2 operator +(Vector2 foo) { return Vector2(x + foo.x, y + foo.y); }
	Vector2 operator -(Vector2 foo) { return Vector2(x - foo.x, y - foo.y); }

	Vector2 operator *(double foo) { return Vector2(x * foo, y * foo); }
	double operator *(Vector2 foo) { return x * foo.x + y * foo.y; }

	void operator +=(Vector2 foo) { x += foo.x; y += foo.y; }
	void operator -=(Vector2 foo) { x -= foo.x; y -= foo.y; }
	
	bool operator ==(Vector2 foo)
	{
		if (x == foo.x && y == foo.y) return true;
		return false;
	}

	Vector2 Normalize()
	{
		Vector2 normalizedVec = *this;
		double magnitude = normalizedVec.Magnitude();
		normalizedVec.x /= magnitude;
		normalizedVec.y /= magnitude;
		return normalizedVec;
	}

	double VectorAngle(Vector2 foo)
	{
		return acos((*this * foo) / (Magnitude() * foo.Magnitude()));
	}

	double Magnitude() { return sqrt(x * x + y * y); }
};