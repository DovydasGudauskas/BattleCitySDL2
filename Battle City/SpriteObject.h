#pragma once

#include <SDL.h>
#include <Vectors.h>
#include <Sprite.h>
#include <list>

class SpriteObject
{
private:
	static std::list<SpriteObject*> allObjects;
	bool renderingEnabled;

protected:
	Sprite sprite;
	SDL_Rect tempRenderData;
	Vector2 position, objectScale;

	bool markedForDeletion;
	
public:
	SpriteObject();
	SpriteObject(Sprite Sprite);
	SpriteObject(Sprite Sprite, bool addToList);
	~SpriteObject();

	static std::list<SpriteObject*> GetAllObjects();

	void EnableRendering(bool var);

	bool IsEnabled();
	bool IsMarkedForDeletion();
	void MarkForDeletion();

	void SetScale(Vector2 Scale);

	Vector2 GetScale();
	Vector2 GetPosition();

	SDL_Rect* GetTextureData();
	SDL_Rect* GetRenderData(Vector2 worldScale);

	void Translate(Vector2 vec);

	void SetPosition(Vector2 Position);
	void SetSprite(Sprite SPRITE);
};

class CollidableSpriteObject : public SpriteObject
{
public:
	CollidableSpriteObject();
	~CollidableSpriteObject();

private:
	Vector2 extents;

	/*bool CheckIfIsInPlayArea()
	{
		bool corrected = false;
		if (position.x - extents.x < 16) { position.x = 16 + extents.x; corrected = true; }
		if (position.y - extents.y < 8) { position.y = 8 + extents.y; corrected = true; }
		if (position.x + extents.x > 223) { position.x = 223 - extents.x; corrected = true; }
		if (position.y + extents.y > 215) { position.y = 215 - extents.y; corrected = true; }
		return corrected;
	}

	Vector2 ClosestPointOnBounds(Vector2 pos)// pos yra lokalus! PS. veikia TIK jeigu kvadratas
	{
		double xTimes = abs(pos.x / extents.x);
		double yTimes = abs(pos.y / extents.y);
		if (yTimes > xTimes) xTimes = yTimes;
		return Vector2(pos.x / xTimes, pos.y / xTimes);
	}

	double GetCrosssectionExtent() { return sqrt(extents.x * extents.x + extents.y * extents.y); }

	bool Intersects(SpriteObject* foo)
	{
		double distance = (position - foo->position).Magnitude();
		double twoCross = GetCrosssectionExtent() + foo->GetCrosssectionExtent();
		if (distance > twoCross) return false;

		Vector2 toTarget = foo->position - position;// <-
		Vector2 targetToSelf = position - foo->position;// <-

		Vector2 ClosestBoundLookAtTarget = ClosestPointOnBounds(toTarget);
		Vector2 ClosestBoundLookAtSelf = foo->ClosestPointOnBounds(targetToSelf);

		double closestPointDistance = ClosestBoundLookAtTarget.Magnitude() + ClosestBoundLookAtSelf.Magnitude();
		if (closestPointDistance > distance)
		{
			if (ParentType == 1 || foo->ParentType == 1)
			{
				BulletHitDetected = true;
				foo->BulletHitDetected = true;
				if (ParentType == 3) MarkForDeletion();
				if (foo->ParentType == 3) foo->MarkForDeletion();
			}
			return true;
		}
		return false;
	}

	void CorrectPosition(SpriteObject* foo)
	{
		double distance = (position - foo->position).Magnitude();

		Vector2 toTarget = foo->position - position;// <-
		Vector2 targetToSelf = position - foo->position;// <-

		Vector2 ClosestBoundLookAtTarget = ClosestPointOnBounds(toTarget);
		Vector2 ClosestBoundLookAtSelf = foo->ClosestPointOnBounds(targetToSelf);

		double distanceCorrection = ClosestBoundLookAtTarget.Magnitude() + ClosestBoundLookAtSelf.Magnitude() - distance;

		double min = 360.;
		int which = 0;
		for (int i = 0; i < 4; i++)
		{
			double angle = targetToSelf.VectorAngle(Directions[i]);
			if (angle < min)
			{
				min = angle;
				which = i;
			}
		}

		ClosestBoundLookAtSelf = Directions[which];
		Translate(ClosestBoundLookAtSelf * distanceCorrection);
		CheckIfIsInPlayArea();
	}*/
};