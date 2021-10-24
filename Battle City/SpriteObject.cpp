#include "SpriteObject.h"

std::list<SpriteObject*> SpriteObject::allObjects = std::list<SpriteObject*>();

SpriteObject::SpriteObject() : sprite(Sprite()), position(.0, .0), objectScale(1.0, 1.0), markedForDeletion(false), renderingEnabled(true)
{
	tempRenderData = SDL_Rect();

	allObjects.push_back(this);
}

SpriteObject::SpriteObject(Sprite Sprite) : sprite(Sprite), position(.0, .0), objectScale(1.0, 1.0), markedForDeletion(false), renderingEnabled(true)
{
	tempRenderData = SDL_Rect();

	allObjects.push_back(this);
}

SpriteObject::SpriteObject(Sprite Sprite, bool addToList) : sprite(Sprite), position(.0, .0), objectScale(1.0, 1.0), markedForDeletion(false), renderingEnabled(true)
{
	tempRenderData = SDL_Rect();

	if(addToList)
		allObjects.push_back(this);
}

SpriteObject::~SpriteObject()
{
	allObjects.remove(this);
}

std::list<SpriteObject*> SpriteObject::GetAllObjects()
{
	return allObjects;
}

void SpriteObject::EnableRendering(bool var)
{
	renderingEnabled = var;
}

bool SpriteObject::IsEnabled()
{
	return renderingEnabled;
}

bool SpriteObject::IsMarkedForDeletion()
{
	return markedForDeletion;
}

void SpriteObject::MarkForDeletion()
{
	markedForDeletion = true;
}

void SpriteObject::SetScale(Vector2 Scale)
{
	objectScale = Scale;
}

Vector2 SpriteObject::GetScale()
{
	return objectScale;
}

Vector2 SpriteObject::GetPosition()
{
	return position;
}

SDL_Rect* SpriteObject::GetTextureData()
{
	return sprite.GetTextureData();
}

SDL_Rect* SpriteObject::GetRenderData(Vector2 worldScale)
{
	tempRenderData.x = (int)((position.x - sprite.GetTextureWidth() * 0.5) * worldScale.x);
	tempRenderData.y = (int)((position.y - sprite.GetTextureHeight() * 0.5) * worldScale.y);
	tempRenderData.w = (int)(sprite.GetTextureWidth() * worldScale.x * objectScale.x);
	tempRenderData.h = (int)(sprite.GetTextureHeight() * worldScale.y * objectScale.y);

	return &tempRenderData;
}

void SpriteObject::Translate(Vector2 vec)
{
	position += vec;
}

void SpriteObject::SetPosition(Vector2 Position)
{
	position = Position;
}

void SpriteObject::SetSprite(Sprite SPRITE)
{
	sprite = SPRITE;
}

//***********************************************************************************************

CollidableSpriteObject::CollidableSpriteObject()
{
	extents = Vector2(sprite.GetTextureWidth() / 2.0, sprite.GetTextureHeight() / 2.0);
}

CollidableSpriteObject::~CollidableSpriteObject()
{
}
