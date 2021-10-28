#include "Debug.h"

DebugInfo::DebugInfo():debugText(new Text())
{
}

DebugInfo::~DebugInfo()
{
	delete debugText;
}

void DebugInfo::Tick()
{
}

void DebugInfo::SetDebugPosition(Vector2 pos)
{
	debugText->SetPosition(pos);
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

void TankDebug::Tick()
{
	DebugInfo::Tick();

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
