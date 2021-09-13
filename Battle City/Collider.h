#include "Vectors.h"
#include "Sprite.h"

class BoxCollider
{
protected:
	Vector2 center, extents, size;
	SpriteObject* parent;
public:

	BoxCollider() :center(), extents(), size(), parent(nullptr){}
	BoxCollider(SpriteObject* Parent) :center(), extents(), size(), parent(Parent) {}
	~BoxCollider() { parent = nullptr; }

	void SetBounds(int width, int height)
	{
		extents = Vector2(width / 2., height / 2.);
		size = Vector2(width, height);
	}

	bool Intersects(BoxCollider *foo)
	{
		if (parent == nullptr || foo->parent == nullptr) return false;
		double distance = (parent->GetPosition()-foo->parent->GetPosition()).Magnitude();

	}
};