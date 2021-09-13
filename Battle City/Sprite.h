#include <SDL.h>
#include "Vectors.h"
#include <vector>

using namespace std;

class Sprite;
class SpriteObject;

class Sprite
{
private:
	SDL_Rect Source;
public:
	Vector2 texturePosition;
	int width, height;

	Sprite() :texturePosition(0., 0.), width(0), height(0), Source(){ }
	Sprite(Vector2 TexturePosition, int Width, int Height) :texturePosition(TexturePosition), width(Width), height(Height), Source(){  }
	~Sprite() {}

	SDL_Rect* ExtractSourceRect()
	{
		Source.x = (int)texturePosition.x;
		Source.y = (int)texturePosition.y;
		Source.w = (int)width;
		Source.h = (int)height;
		return &Source;
	}
};

//Colour yellow-white-green-red
//Line 0-7
//Collum 0-7
Sprite* GetSprite(int colour, int line, int column);
Sprite* GetBulletSprite(int dir);

const vector<Vector2> Directions = { Vector2(0.,-1.),Vector2(-1.,0.),Vector2(0.,1.),Vector2(1.,0.) };//up, left, down, right

class SpriteObject
{
private:
	SDL_Rect Source, Destination;//tileset rect, destination rect
	Vector2 extents, size;
	Vector2 position, scale, oldPosition;
	Sprite* sprite;
protected:
	bool MarkedForDeletion;
	bool BulletHitDetected;
	int ParentType;// 0 - none, 1 - Bullet, 2 - wall
public:
	SpriteObject() :sprite(nullptr), Source(), Destination(), position(0.,0.), scale(1., 1.), ParentType(0), MarkedForDeletion(false), BulletHitDetected(false), oldPosition(){}
	SpriteObject(Sprite* Sprite) :sprite(Sprite), Source(), Destination(), position(0., 0.), scale(1., 1.), ParentType(0), MarkedForDeletion(false), BulletHitDetected(false), oldPosition(){ }
	~SpriteObject() { }

	void ResetPosition() { position = oldPosition; }

	bool HasBeenHitByABullet() { return BulletHitDetected; }
	void ResetBulletHit() { BulletHitDetected = false; }

	int GetParentType() { return ParentType; }
	void SetParentType(int set) { ParentType = set; }
	bool IsMarkedForDeletion() { return MarkedForDeletion; }
	void MarkForDeletion() { MarkedForDeletion = true; }

	void InitializeBoundingBox(int width, int height)
	{
		if (width < 0 || height < 0) return;
		extents = Vector2(width / 2., height / 2.);
		size = Vector2(width, height);
	}

	void SetScale(Vector2 Scale) { scale = Scale; }
	Vector2 GetScale() { return scale; }
	Vector2 GetPosition() { return position; }

	SDL_Rect* GetSourceRect()
	{
		if (sprite == nullptr) return nullptr;
		Source.x = (int)sprite->texturePosition.x;
		Source.y = (int)sprite->texturePosition.y;
		Source.w = (int)sprite->width;
		Source.h = (int)sprite->height;
		return &Source;
	}

	SDL_Rect* GetDestinationRect(Vector2 Scale)
	{
		if (sprite == nullptr) return nullptr;
		Destination.x = (int)((position.x - sprite->width * 0.5) * Scale.x);
		Destination.y = (int)((position.y - sprite->height * 0.5) * Scale.y);
		Destination.w = (int)(sprite->width * Scale.x * scale.x);
		Destination.h = (int)(sprite->height * Scale.y * scale.y);
		return &Destination;
	}

	void Translate(Vector2 vec) { position += vec; }// Pajudinti position vektoriaus pusen ir ilgiu
	void SetPosition(Vector2 Position) { position = Position; oldPosition = Position; }
	void SetSprite(Sprite* SPRITE) { sprite = SPRITE; }

	//***********************Collision*********************
	bool CheckIfIsInPlayArea()
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
	}
};

void InitializeAllSprites();
void LoadAllTankSprites();
vector<vector<Sprite>> LoadOneTankMatrix(int start_x, int start_y);