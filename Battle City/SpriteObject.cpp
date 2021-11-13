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

void SpriteObject::SetOldPosition(Vector2 pos)
{
	oldPosition = pos;
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
	if (vec == Vector2::zero)
		return;

	oldPosition = position;
	position += vec;

	OnPositionChange();
}

void SpriteObject::SetPosition(Vector2 Position)
{
	if (Position == position)
		return;

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

bool CollidableSpriteObject::CheckGameBounds()
{
	if (IsOutOfBounds())
	{
		OnCollision(nullptr);
		SetPosition(GetOldPosition());

		return true;
	}

	return false;
}

bool CollidableSpriteObject::IsOutOfBounds()
{
	SDL_Rect* myTexture = GetTextureData();
	return position.x - myTexture->w / 2. <= 15 
		|| position.x + myTexture->w / 2. >= 226 
		|| position.y - myTexture->h / 2. <= 7 
		|| position.y + myTexture->h / 2. >= 218;
}

FinalObjectType CollidableSpriteObject::GetFinalObjectType()
{
	return FinalObjectType::None;
}

void CollidableSpriteObject::Initialize()
{
	allCollidables.push_back(this);

	localCollisionRect = *sprite.GetTextureData();
	localCollisionRect.x = 0;
	localCollisionRect.y = 0;

	velocity = Vector2::zero;

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
	if (!IsEnabled())
		return;

	CheckGameBounds();

	for (size_t i = 0; i < allCollidables.size(); i++)
		if(allCollidables[i]->IsEnabled())
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

void CollidableSpriteObject::Tick() // override SpriteObject
{
	SpriteObject::Tick();
	Translate(velocity); // Move object
}

void CollidableSpriteObject::OnCollision(CollidableSpriteObject* collision)
{
}

void CollidableSpriteObject::SetVelocity(Vector2 vel)
{
	velocity = vel;
}

void CollidableSpriteObject::SetCollisionOffset(Vector2 vec)
{
	localCollisionRect.x = (int)vec.x;
	localCollisionRect.y = (int)vec.y;
	UpdateGlobalCollisionRect();
}

Vector2 CollidableSpriteObject::GetVelocity()
{
	return velocity;
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

bool CollidableSpriteObject::CorrectIntersection(CollidableSpriteObject* obj)
{
	if (this == obj || !HasIntersection(&globalCollisionRect, obj->GetCollisionRect()))
		return false;

	OnCollision(obj);
	
	if (obj->IsTrigger())
	{
		obj->OnCollision(this);
		return true;
	}

	obj->OnCollision(this);

	if (obj->IsStatic())
	{
		Translate(-velocity);
		velocity = Vector2::zero;
	}
	else
	{
		Vector2 meToObj = obj->GetPosition() - position;
		if (meToObj.VectorAngle(velocity) * Rad2Deg < 45.)
		{
			Translate(-velocity);
			velocity = Vector2::zero;
		}

		Vector2 objToMe = -meToObj;
		if (objToMe.VectorAngle(obj->GetVelocity()) * Rad2Deg < 45.)
		{
			obj->Translate(-obj->GetVelocity());
			obj->SetVelocity(Vector2::zero);
		}
	}

	return true;
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

// ************************************************

bool TriggerCollidable::IsTrigger()
{
	return true;
}

TriggerCollidable::TriggerCollidable()
{
}

TriggerCollidable::TriggerCollidable(Sprite Sprite)
{
}

TriggerCollidable::TriggerCollidable(Sprite Sprite, int layer)
{
}

TriggerCollidable::~TriggerCollidable()
{
}

void TriggerCollidable::CheckCollision()
{
	bool collided;
	CollidableSpriteObject* lastCollision = nullptr;

	collided = CheckGameBounds();

	for (size_t i = 0; i < allCollidables.size(); i++)
		if (CorrectIntersection(allCollidables[i]))
		{
			collided = true;
			lastCollision = allCollidables[i];
		}

	if(collided)
		OnCollision(lastCollision);
}

bool TriggerCollidable::CorrectIntersection(CollidableSpriteObject* obj) // override CollidableSpriteObject
{
	if (this == obj || !HasIntersection(&globalCollisionRect, obj->GetCollisionRect()))
		return false;

	obj->OnCollision(this);

	return true;
}

bool TriggerCollidable::CheckGameBounds() // override CollidableSpriteObject
{
	return IsOutOfBounds();
}
