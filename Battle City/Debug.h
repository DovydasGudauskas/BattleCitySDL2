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
	void SetDebugPosition(Vector2 pos);
protected:
	Text* debugText;
};

class TankDebug : public DebugInfo
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

class Debug
{
public:
	static Debug* GetReference();

	void ClearAllDebugs();

	void DebugTank(Tank* tank);
	void DebugTank(Tank* tank, Vector2 textPos);

	void Tick();
private:
	Debug();
	~Debug();

	vector<DebugInfo*> debugs;

	static Debug* singleton;
};