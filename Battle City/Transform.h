#include "Vectors.h"

class Transform
{
public:
	Vector2 position, scale;

	Transform() :position(0., 0.), scale(1., 1.) {}
	Transform(Vector2 Position) :position(Position), scale(1., 1.) {}
	Transform(Vector2 Position, Vector2 Scale) :position(Position), scale(Scale) {}
	~Transform() {}
};