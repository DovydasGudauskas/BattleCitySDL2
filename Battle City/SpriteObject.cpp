#include <SpriteObject.h>
#include <Rendering.h>

vector<SpriteObject*> SpriteObject::allObjects = vector<SpriteObject*>();
unordered_map<int, vector<SpriteObject*>> SpriteObject::objectLayers = unordered_map<int, vector<SpriteObject*>>();

void SpriteObject::Initialize(int Layer)
{
	oldPosition = position;

	tempRenderData = SDL_Rect();

	renderingEnabled = true;
	markedForDeletion = false;

	objectScale = Vector2(1, 1);
	position = Vector2(0, 0);

	allObjects.push_back(this);

	layer = Layer;
	objectLayers[layer].push_back(this);
}

SpriteObject::SpriteObject() : sprite(Sprite())
{
	Initialize(0);
}

SpriteObject::SpriteObject(Sprite Sprite) : sprite(Sprite)
{
	Initialize(0);
}

SpriteObject::SpriteObject(Sprite Sprite, int Layer) : sprite(Sprite)
{
	Initialize(Layer);
}

SpriteObject::~SpriteObject()
{
	allObjects.erase(remove(allObjects.begin(), allObjects.end(), this));
	
	vector<SpriteObject*>* myLayer = &objectLayers[layer];
	myLayer->erase(remove(myLayer->begin(), myLayer->end(), this));
}

vector<SpriteObject*> SpriteObject::GetAllObjects()
{
	return allObjects;
}

unordered_map<int, vector<SpriteObject*>>* SpriteObject::GetAllLayers()
{
	return &objectLayers;
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

Vector2 SpriteObject::GetOldPosition()
{
	return oldPosition;
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
	oldPosition = position;
	position += vec;
}

void SpriteObject::SetPosition(Vector2 Position)
{
	oldPosition = position;
	position = Position;
}

void SpriteObject::SetSprite(Sprite SPRITE)
{
	sprite = SPRITE;
}

//***********************************************************************************************

std::list<CollidableSpriteObject*> CollidableSpriteObject::allCollidables = std::list<CollidableSpriteObject*>();

CollidableSpriteObject::CollidableSpriteObject():isStatic(false)
{
	allCollidables.push_back(this);
}

CollidableSpriteObject::CollidableSpriteObject(bool staticFlag)
{
	allCollidables.push_back(this);

	isStatic = staticFlag;
}

CollidableSpriteObject::~CollidableSpriteObject()
{
	allCollidables.remove(this);
}

void CollidableSpriteObject::CheckCollision()
{
	std::list<CollidableSpriteObject*>::iterator it = allCollidables.begin();

	while (it != allCollidables.end())
	{
		CorrectIntersection(*it);

		it++;
	}
}

bool CollidableSpriteObject::IsStatic()
{
	return isStatic;
}

void CollidableSpriteObject::CorrectIntersection(CollidableSpriteObject* obj)
{
	Vector2 renderScale = Rendering::GetReference()->GetRenderScale();

	SDL_Rect result = SDL_Rect();
	SDL_bool boolRes = SDL_IntersectRect(GetRenderData(renderScale), obj->GetRenderData(renderScale), &result);

	if (!boolRes)
		return;

	if (isStatic)
	{
		if (obj->IsStatic()) // static with static
		{
			return;
		}
		else // static with object
		{
			obj->SetPosition(obj->GetOldPosition());
		}
	}
	else
	{
		if (obj->IsStatic()) // object with static
		{
			SetPosition(GetOldPosition());
		}
		else // object with object
		{
			obj->Translate((obj->GetOldPosition() - obj->GetPosition()) * 0.5);
			Translate((GetOldPosition() - GetPosition()) * 0.5);
		}
	}
}
