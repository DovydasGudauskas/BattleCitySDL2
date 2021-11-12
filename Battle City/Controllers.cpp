

#include <Controllers.h>
#include <Windows.h>
#include <stdlib.h>     /* srand, rand */

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

void TankController::Tick() // virtual
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
	lastPosition = Vector2::zero;
}

AIController::~AIController()
{
}

const int enemyFireSensitivity = 8;
bool AIController::ShouldFire(Vector2 targetPos)
{
	Vector2 position = controlTank->GetPosition();
	int facingDir = (int)controlTank->GetDirection();

	if (facingDir == 0 && position.y > targetPos.y && abs(position.x - targetPos.x) < enemyFireSensitivity) 
		return true; // uUp
	else if (facingDir == 1 && position.x > targetPos.x && abs(position.y - targetPos.y) < enemyFireSensitivity) 
		return true; // Left
	else if (facingDir == 2 && position.y < targetPos.y && abs(position.x - targetPos.x) < enemyFireSensitivity) 
		return true; // Down
	else if (position.x < targetPos.x && abs(position.y - targetPos.y) < enemyFireSensitivity) 
		return true; // Right

	return false;
}

bool AIController::IsStuck()
{
	bool ret = false;
	if (lastPosition == controlTank->GetPosition())
		ret = true;

	lastPosition = controlTank->GetPosition();

	return ret;
}

Vector2 DirectionToVec(Direction dir)
{
	switch (dir)
	{
	default:
	case Direction::Up:
		return Vector2::down;
	case Direction::Left:
		return Vector2::left;
	case Direction::Down:
		return Vector2::up;
	case Direction::Right:
		return Vector2::right;
	}
}

Direction RandomDirection()
{
	return (Direction)(rand() % 4);
}

void AIController::Tick() // override TankController
{
	TankController::Tick();

	if (controlTank == nullptr)
	{
		delete this;
		return;
	}

	if (!controlTank->IsEnabled() || !canControlTank)
		return;

	if (IsStuck())
		controlTank->SetDirection(RandomDirection());

	controlTank->GoDirection(DirectionToVec(controlTank->GetDirection()));
}