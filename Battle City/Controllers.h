#pragma once

#include <Windows.h>
#include <GameObjects.h>
#include <list>

struct PlayerControllerKeymapping
{
	char up = 'W';
	char left = 'A';
	char down = 'S';
	char right = 'D';


	char fire = VK_SPACE;
};

class TankController
{
public:
	TankController();
	~TankController();

	void SetControlFlag(bool var);
	void SetControlTank(Tank* tank);
	virtual void Tick();

	Tank* GetControlTank();

	static std::list<TankController*>* GetAllControllers();
private:
	static std::list<TankController*> allControllers;
protected:
	Tank* controlTank;
	bool canControlTank;
};

class PlayerController : public TankController
{
public:
	PlayerController();
	PlayerController(PlayerControllerKeymapping KeyMap);
	~PlayerController();

	void Tick() override;

	static vector<PlayerController*>* GetAllLocalPlayers();
private:
	static vector<PlayerController*> allLocalPlayers;

	PlayerControllerKeymapping keymap;
};

class AIController : public TankController
{
public:
	AIController(Tank* tankToControl);
	~AIController();

	void Tick() override;
private:
	Vector2 lastPosition;

	bool ShouldFire(Vector2 targetPos);
	bool IsStuck();
};