#include <Transform.h>

Transform::Transform() : position(Vector2()), scale(Vector2(1,1))
{
}

Transform::Transform(Vector2 pos) : position(pos), scale(Vector2(1, 1))
{
}

Transform::Transform(Vector2 pos, Vector2 objectScale) : position(pos), scale(objectScale)
{
}

Transform::~Transform()
{
}

Vector2 Transform::GetPosition()
{
	return position;
}

Vector2 Transform::GetOldPosition()
{
	return oldPosition;
}

void Transform::OnPositionChange()
{
}

void Transform::Translate(Vector2 vec)
{
	oldPosition = position;
	position += vec;

	OnPositionChange();
}

void Transform::SetPosition(Vector2 Position)
{
	oldPosition = position;
	position = Position;

	OnPositionChange();
}
