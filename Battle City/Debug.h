#pragma once

#include <GameObjects.h>
#include <Text.h>
#include <vector>

using namespace std;

class DebugInfo
{
public:
	DebugInfo();
	~DebugInfo();

	virtual void Tick();
	virtual void SetDebugPosition(Vector2 pos);
};

class DebugInfoText : public DebugInfo
{
public:
	DebugInfoText();
	~DebugInfoText();

	void Tick() override;
	void SetDebugPosition(Vector2 pos) override;
protected:
	Text* debugText;
};

class TankDebug : public DebugInfoText
{
public:
	TankDebug();
	TankDebug(Tank* debugTank);
	TankDebug(Tank* debugTank, Vector2 pos);
	~TankDebug();

	void Tick() override;
private:
	Tank* myDebugTank;
};

class CollisionBoxDebug : public DebugInfo
{
public:
	CollisionBoxDebug(CollidableSpriteObject* spriteObj);
	~CollisionBoxDebug();

	void Tick() override;
	void SetTrackObject(CollidableSpriteObject* spriteObj);
private:
	SpriteObject* myBox;
	CollidableSpriteObject* myObj;
};

class Debug
{
public:
	static Debug* GetReference();

	void ClearAllDebugs();

	void DebugTank(Tank* tank);
	void DebugTank(Tank* tank, Vector2 textPos);

	void DebugCollision(CollidableSpriteObject* tank);

	void Tick();
private:
	Debug();
	~Debug();

	vector<DebugInfo*> debugs;

	static Debug* singleton;
};