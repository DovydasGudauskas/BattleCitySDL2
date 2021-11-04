#include "Debug.h"

DebugInfo::DebugInfo()
{
}

DebugInfo::~DebugInfo()
{
}

void DebugInfo::Tick() // virtual
{
}

void DebugInfo::SetDebugPosition(Vector2 pos)
{
}

// *********************************************

TankDebug::TankDebug():myDebugTank(nullptr)
{
}

TankDebug::TankDebug(Tank* debugTank) : myDebugTank(debugTank)
{
}

TankDebug::TankDebug(Tank* debugTank, Vector2 pos) : myDebugTank(debugTank)
{
	SetDebugPosition(pos);
}

TankDebug::~TankDebug()
{
}

void TankDebug::Tick() // override DebugInfoText
{
	DebugInfoText::Tick();

	if (myDebugTank == nullptr)
		return;

	debugText->SetText(myDebugTank->GetPosition().toString());
}

// *********************************************

Debug* Debug::singleton = nullptr;

Debug* Debug::GetReference()
{
	if (singleton == nullptr)
		return new Debug();
	return singleton;
}

void Debug::ClearAllDebugs()
{
	for (size_t i = 0; i < debugs.size(); i++)
		delete debugs[i];

	debugs.clear();
}

void Debug::DebugTank(Tank* tank)
{
	DebugTank(tank, Vector2(4, 4));
}

void Debug::DebugTank(Tank* tank, Vector2 textPos)
{
	TankDebug* db = new TankDebug(tank, textPos);
	debugs.push_back(db);
}

void Debug::DebugCollision(CollidableSpriteObject* var)
{
	CollisionBoxDebug* db = new CollisionBoxDebug(var);
	debugs.push_back(db);
}

void Debug::Tick()
{
	for (size_t i = 0; i < debugs.size(); i++)
		debugs[i]->Tick();
}

Debug::Debug()
{
	singleton = this;
}

Debug::~Debug()
{
	ClearAllDebugs();
}

// **************************************

DebugInfoText::DebugInfoText() :debugText(new Text())
{
}

DebugInfoText::~DebugInfoText()
{
	delete debugText;
}

void DebugInfoText::Tick() // Override DebugInfo
{
	DebugInfo::Tick();
}

void DebugInfoText::SetDebugPosition(Vector2 pos) // Override DebugInfo
{
	debugText->SetPosition(pos);
}

// *************************************

CollisionBoxDebug::CollisionBoxDebug(CollidableSpriteObject* spriteObj) : myBox(new SpriteObject(Sprite(), layerType::Debug))
{
	SetTrackObject(spriteObj);
}

void CollisionBoxDebug::SetTrackObject(CollidableSpriteObject* spriteObj)
{
	myObj = spriteObj;

	SDL_Rect texture = SDL_Rect();
	texture.x = 9;
	texture.y = 137;
	texture.w = 1;
	texture.h = 1;
	myBox->SetSprite(texture);
	myBox->SetPosition(myObj->GetPosition());

	SDL_Rect* colRect = myObj->GetLocalCollisionRect();
	myBox->SetScale(Vector2(colRect->w, colRect->h));
}

CollisionBoxDebug::~CollisionBoxDebug()
{
	delete myBox;
}

void CollisionBoxDebug::Tick()
{
	DebugInfo::Tick();

	if (myObj == nullptr)
		return;

	myBox->SetPosition(myObj->GetPosition());
}
