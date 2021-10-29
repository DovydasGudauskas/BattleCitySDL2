#pragma once

#include <SDL.h>
#include <Vectors.h>
#include <Sprite.h>
#include <list>
#include <unordered_map>

using namespace std;

namespace layerType
{
	enum LayerType
	{
		Background = -1,
		Default = 0,
		MapTiles = 1,
		Overlay = 2,
		Text = 3
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