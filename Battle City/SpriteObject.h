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
	Vector2 oldPosition;

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
	Vector2 GetOldPosition();

	SDL_Rect* GetTextureData();
	SDL_Rect* GetRenderData(Vector2 worldScale);

	virtual void Translate(Vector2 vec);
	void SetPosition(Vector2 Position);

	void SetSprite(Sprite SPRITE);
};

class CollidableSpriteObject : public SpriteObject
{
public:
	CollidableSpriteObject();
	CollidableSpriteObject(bool staticFlag);
	~CollidableSpriteObject();

	void CheckCollision();
	bool IsStatic();
private:
	bool isStatic;

	static std::list<CollidableSpriteObject*> allCollidables;

	void CorrectIntersection(CollidableSpriteObject* obj);
};