#include <Controllers.h>
#include <Windows.h>

std::list<TankController*> TankController::allControllers = std::list<TankController*>();

TankController::TankController()
{
	controlTank = nullptr;
	canControlTank = true;

	allControllers.push_back(this);
}

TankController::~TankController()
{
	allControllers.remove(this);
}

void TankController::SetControlFlag(bool var)
{
	canControlTank = var;
}

void TankController::SetControlTank(Tank* tank)
{
	controlTank = tank;
}

void TankController::Tick()
{
}

Tank* TankController::GetControlTank()
{
	return controlTank;
}

std::list<TankController*>* TankController::GetAllControllers()
{
	return &allControllers;
}

// ************************************

PlayerController::PlayerController()
{
}

PlayerController::PlayerController(PlayerControllerKeymapping KeyMap):keymap(KeyMap)
{
}

PlayerController::~PlayerController()
{
}


void PlayerController::Tick()
{
	if (!canControlTank || controlTank == nullptr)
		return;

	if (GetAsyncKeyState(keymap.up))
		controlTank->GoDirection(Vector2(0, -1));
	else if (GetAsyncKeyState(keymap.down))
		controlTank->GoDirection(Vector2(0, 1));
	else if (GetAsyncKeyState(keymap.right))
		controlTank->GoDirection(Vector2(1, 0));
	else if (GetAsyncKeyState(keymap.left))
		controlTank->GoDirection(Vector2(-1, 0));
	else
		controlTank->SetVelocity(Vector2::zero);

	if (GetAsyncKeyState(keymap.fire))
		controlTank->Fire();
}

// ***********************************

AIController::AIController(Tank* tankToControl)
{
	controlTank = tankToControl;
	canControlTank = true;
}

AIController::~AIController()
{
}

void AIController::Tick()
{
	if (controlTank == nullptr)
	{
		delete this;
		return;
	}

	if (!controlTank->IsEnabled() || !canControlTank)
		return;
}