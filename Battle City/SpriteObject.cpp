#include <SpriteObject.h>
#include <Rendering.h>

vector<SpriteObject*> SpriteObject::allObjects = vector<SpriteObject*>();
unordered_map<int, vector<SpriteObject*>> SpriteObject::objectLayers = unordered_map<int, vector<SpriteObject*>>();

void SpriteObject::Initialize(int Layer)
{
	spriteAnchor = anchorPoint::Center;
	oldPosition = position;

	tempRenderData = SDL_Rect();

	renderingEnabled = true;
	markedForDeletion = false;

	objectScale = Vector2(1, 1);
	position = Vector2(0, 0);

	allObjects.push_back(this);

	layer = Layer;
	objectLayers[layer].push_back(this);

	OnPositionChange();
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

void SpriteObject::SetAnchorPoint(anchorPoint::AnchorPoint var)
{
	spriteAnchor = var;
	UpdateRenderData(Rendering::GetReference()->GetRenderScale());
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
	OnPositionChange();
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

void SpriteObject::UpdateRenderData(Vector2 worldScale)
{
	switch (spriteAnchor)
	{
	case anchorPoint::Center:
		tempRenderData.x = (int)((position.x - sprite.GetTextureWidth() * 0.5 * objectScale.x) * worldScale.x);
		tempRenderData.y = (int)((position.y - sprite.GetTextureHeight() * 0.5 * objectScale.y) * worldScale.y);
		break;

	case anchorPoint::Right:
		break;

	case anchorPoint::Left:
		break;

	case anchorPoint::Up:
		break;

	case anchorPoint::Down:
		break;

	case anchorPoint::UpRight:
		break;

	case anchorPoint::DownRight:
		break;

	case anchorPoint::UpLeft:
		tempRenderData.x = (int)((position.x - sprite.GetTextureWidth() * 0.5) * worldScale.x);
		tempRenderData.y = (int)((position.y - sprite.GetTextureHeight() * 0.5) * worldScale.y);
		break;

	case anchorPoint::DownLeft:
		break;

	default:
		break;
	}

	tempRenderData.w = (int)(sprite.GetTextureWidth() * worldScale.x * objectScale.x);
	tempRenderData.h = (int)(sprite.GetTextureHeight() * worldScale.y * objectScale.y);
}

void SpriteObject::OnPositionChange()
{
	UpdateRenderData(Rendering::GetReference()->GetRenderScale());
}

SDL_Rect* SpriteObject::GetRenderData()
{
	return &tempRenderData;
}

void SpriteObject::Translate(Vector2 vec)
{
	oldPosition = position;
	position += vec;

	OnPositionChange();
}

void SpriteObject::SetPosition(Vector2 Position)
{
	oldPosition = position;
	position = Position;

	OnPositionChange();
}

void SpriteObject::SetSprite(Sprite SPRITE)
{
	sprite = SPRITE;
	OnPositionChange();
}

//***********************************************************************************************

vector<CollidableSpriteObject*> CollidableSpriteObject::allCollidables = vector<CollidableSpriteObject*>();

void CollidableSpriteObject::Initialize()
{
	allCollidables.push_back(this);

	isTrigger = false;

	localCollisionRect = *sprite.GetTextureData();
	localCollisionRect.x = 0;
	localCollisionRect.y = 0;

	UpdateGlobalCollisionRect();
}

CollidableSpriteObject::CollidableSpriteObject()
{
	Initialize();
}

CollidableSpriteObject::CollidableSpriteObject(Sprite Sprite) : SpriteObject(Sprite)
{
	Initialize();
}

CollidableSpriteObject::CollidableSpriteObject(Sprite Sprite, int layer) : SpriteObject(Sprite, layer)
{
	Initialize();
}

CollidableSpriteObject::~CollidableSpriteObject()
{
	allCollidables.erase(remove(allCollidables.begin(), allCollidables.end(),this));
}

void CollidableSpriteObject::CheckCollision()
{
	for (size_t i = 0; i < allCollidables.size(); i++)
		CorrectIntersection(allCollidables[i]);
}

bool CollidableSpriteObject::IsStatic()
{
	return false;
}

bool CollidableSpriteObject::IsTrigger()
{
	return false;
}

void CollidableSpriteObject::SetTriggerFlag(bool var)
{
	isTrigger = var;
}

vector<CollidableSpriteObject*>* CollidableSpriteObject::GetAllCollidables()
{
	return &allCollidables;
}

void CollidableSpriteObject::UpdateGlobalCollisionRect()
{
	globalCollisionRect = localCollisionRect;

	globalCollisionRect.w *= (int)objectScale.x;
	globalCollisionRect.h *= (int)objectScale.y;

	globalCollisionRect.x += (int)position.x;
	globalCollisionRect.y += (int)position.y;
}

void CollidableSpriteObject::OnPositionChange() // override SpriteObject
{
	SpriteObject::OnPositionChange();
	UpdateGlobalCollisionRect();
}

void CollidableSpriteObject::OnCollision()
{
}

void CollidableSpriteObject::SetCollisionOffset(Vector2 vec)
{
	localCollisionRect.x = (int)vec.x;
	localCollisionRect.y = (int)vec.y;
	UpdateGlobalCollisionRect();
}

void CollidableSpriteObject::SetCollisionBounds(Vector2 vec)
{
	localCollisionRect.w = (int)vec.x;
	localCollisionRect.h = (int)vec.y;
	UpdateGlobalCollisionRect();
}

SDL_Rect* CollidableSpriteObject::GetCollisionRect()
{
	return &globalCollisionRect;
}

SDL_Rect* CollidableSpriteObject::GetLocalCollisionRect()
{
	return &localCollisionRect;
}

bool HasIntersection(SDL_Rect *a, SDL_Rect *b) {
	return (abs(a->x - b->x) * 2 < (a->w + b->w)) &&
		(abs(a->y - b->y) * 2 < (a->h + b->h));
}

void CollidableSpriteObject::CorrectIntersection(CollidableSpriteObject* obj)
{
	if (this == obj || !HasIntersection(&globalCollisionRect, obj->GetCollisionRect()))
		return;

	OnCollision();
	obj->OnCollision();

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

// ***********************************************

StaticCollidable::StaticCollidable() : CollidableSpriteObject()
{
}

StaticCollidable::StaticCollidable(Sprite Sprite) : CollidableSpriteObject(Sprite)
{
}

StaticCollidable::StaticCollidable(Sprite Sprite, int layer) : CollidableSpriteObject(Sprite, layer)
{
}

StaticCollidable::~StaticCollidable()
{
}

void StaticCollidable::CheckCollision()
{
}

bool StaticCollidable::IsStatic()
{
	return true;
}
