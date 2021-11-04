#pragma once

#include <SDL.h>
#include <Vectors.h>
#include <Sprite.h>
#include <list>
#include <unordered_map>
#include <Transform.h>

using namespace std;

namespace layerType
{
	enum LayerType
	{
		Background = -1,
		Default = 0,
		MapTiles = 1,
		Overlay = 2,
		Text = 3,
		Debug = 4
	};
}

namespace anchorPoint
{
	enum AnchorPoint
	{
		Center = 0,
		Right,
		Left,
		Up,
		Down,
		UpRight,
		DownRight,
		UpLeft,
		DownLeft
	};
}

class SpriteObject
{
private:
	static vector<SpriteObject*> allObjects;
	static unordered_map<int, vector<SpriteObject*>> objectLayers;

	bool renderingEnabled;
	Vector2 oldPosition;

	int layer;
	void Initialize(int Layer);

	anchorPoint::AnchorPoint spriteAnchor;
protected:
	Sprite sprite;
	SDL_Rect tempRenderData;
	Vector2 position, objectScale;

	bool markedForDeletion;
	
public:
	SpriteObject();
	SpriteObject(Sprite Sprite);
	SpriteObject(Sprite Sprite, int layer);
	~SpriteObject();

	void SetAnchorPoint(anchorPoint::AnchorPoint var);

	static vector<SpriteObject*> GetAllObjects();
	static unordered_map<int, vector<SpriteObject*>>* GetAllLayers();

	void EnableRendering(bool var);

	bool IsEnabled();
	bool IsMarkedForDeletion();
	void MarkForDeletion();

	void SetScale(Vector2 Scale);

	Vector2 GetScale();
	Vector2 GetPosition();
	Vector2 GetOldPosition();

	SDL_Rect* GetTextureData();
	SDL_Rect* GetRenderData();
	void UpdateRenderData(Vector2 worldScale);

	virtual void OnPositionChange();

	virtual void Translate(Vector2 vec);
	void SetPosition(Vector2 Position);

	void SetSprite(Sprite SPRITE);
};

class CollidableSpriteObject : public SpriteObject
{
public:
	CollidableSpriteObject();
	CollidableSpriteObject(Sprite Sprite);
	CollidableSpriteObject(Sprite Sprite, int layer);

	~CollidableSpriteObject();

	virtual void CheckCollision();
	virtual bool IsStatic();
	virtual bool IsTrigger();

	static vector<CollidableSpriteObject*>* GetAllCollidables();

	void OnPositionChange() override;

	virtual void OnCollision();

	void SetCollisionOffset(Vector2 vec);
	void SetCollisionBounds(Vector2 vec);

	SDL_Rect* GetCollisionRect();
	SDL_Rect* GetLocalCollisionRect();
protected:
	SDL_Rect localCollisionRect, globalCollisionRect;
private:
	static vector<CollidableSpriteObject*> allCollidables;

	void Initialize();
	virtual bool CorrectIntersection(CollidableSpriteObject* obj);
	void UpdateGlobalCollisionRect();
};

class StaticCollidable : public CollidableSpriteObject
{
public:
	StaticCollidable();
	StaticCollidable(Sprite Sprite);
	StaticCollidable(Sprite Sprite, int layer);

	~StaticCollidable();

	void CheckCollision() override;
	bool IsStatic() override;
private:
};

class TriggerCollidable : public CollidableSpriteObject
{
public:
	TriggerCollidable();
	TriggerCollidable(Sprite Sprite);
	TriggerCollidable(Sprite Sprite, int layer);

	~TriggerCollidable();

	bool IsTrigger() override;
private:
	bool CorrectIntersection(CollidableSpriteObject* obj) override;
};