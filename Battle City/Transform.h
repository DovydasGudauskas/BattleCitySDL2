#pragma once

#include <Vectors.h>

class Transform
{
public:
	Transform();
	Transform(Vector2 pos);
	Transform(Vector2 pos, Vector2 objectScale);
	~Transform();

	Vector2 GetPosition();
	Vector2 GetOldPosition();

	virtual void OnPositionChange();

	virtual void Translate(Vector2 vec);
	void SetPosition(Vector2 Position);
protected:
	Vector2 position, scale;
private:
	Vector2 oldPosition;
};