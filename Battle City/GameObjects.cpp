#include <GameObjects.h>
#include <Rendering.h>

Tank::Tank()
{
	tankType = 0;
	playerType = -1;
	hp = 1;

	Initialize();
	SetStatsThroughType();
}

Tank::Tank(int TankType, int HP, int PlayerType) : tankType(TankType), playerType(PlayerType), hp(HP)
{
	Initialize();
	SetStatsThroughType();
}

void Tank::Initialize()
{
	isDead = false;
	animationState = 0;
	lookDirection = Direction::Up;
	fireTime = 0;

	FetchNewSprites();
}

void Tank::SetStatsThroughType()
{
	float speedMultiplier = 0.75;
	float fireRateMultiplier = 1;

	if (playerType >= 0) // PLAYER
	{
		switch (hp-1)
		{
		default: // Slow movement, slow fire
			speed = speedMultiplier;
			maxFireCooldown = fireRateMultiplier;
			break;

		case 1: // Medium movement, medium speed weapon
			speed = 2 * speedMultiplier;
			maxFireCooldown = 2 * fireRateMultiplier;
			break;

		case 2: // Medium movement, medium speed weapon (can destroy steel walls)
			speed = 2 * speedMultiplier;
			maxFireCooldown = 2 * fireRateMultiplier;
			break;

		case 3: // Medium movement, medium speed weapon (can double fire and destroy steel walls)
			speed = 2 * speedMultiplier;
			maxFireCooldown = 2 * fireRateMultiplier;
			break;
		}
	}
	else // ENEMIES
	{
		switch (tankType)
		{
		default: // Slow movement, slow fire
			speed = speedMultiplier;
			maxFireCooldown = fireRateMultiplier;
			break;

		case 1: // Super fast, slow fire
			speed = 3 * speedMultiplier;
			maxFireCooldown = fireRateMultiplier;
			break;

		case 2: // Medium movement, medium speed weapon
			speed = 2 * speedMultiplier;
			maxFireCooldown = 2 * fireRateMultiplier;
			break;

		case 3: // Medium movement, medium speed weapon (can double fire and destroy steel walls)
			speed = 2 * speedMultiplier;
			maxFireCooldown = 2 * fireRateMultiplier;
			break;
		}
	}
}

Tank::~Tank()
{
}

void Tank::GoDirection(Vector2 direction)
{
	if (direction.x > 0.1f)
	{
		SetDirection(Direction::Right);
		Translate(Vector2(1, 0) * speed);
	}
	else if (direction.x < -0.1f)
	{
		SetDirection(Direction::Left);
		Translate(Vector2(-1, 0) * speed);
	}
	else if (direction.y > 0.1f)
	{
		SetDirection(Direction::Down);
		Translate(Vector2(0, 1) * speed);
	}
	else if (direction.y < -0.1f)
	{
		SetDirection(Direction::Up);
		Translate(Vector2(0, -1) * speed);
	}
}

void Tank::Fire()
{
}

void Tank::SetDirection(Direction dir)
{
	if (dir == lookDirection)
		return;

	lookDirection = dir;

	RefreshSprite();
}

void Tank::RefreshSprite()
{
	SetSprite(tankSprites[((int)lookDirection) * 2 + animationState]);
}

void Tank::FetchNewSprites()
{
	tankSprites = Rendering::GetReference()->GetTankTextures(tankType, hp, playerType);
}

void Tank::DamageTank(int dmg)
{
	hp -= dmg;

	if (hp < 0)
	{
		Die();
		hp = 0;
	}
	else
		FetchNewSprites();
}

const float tankDistAnimChange = 1;
void Tank::Translate(Vector2 vec)
{
	SpriteObject::Translate(vec);
	distanceTraveled += vec.Magnitude();

	if (distanceTraveled > tankDistAnimChange)
	{
		distanceTraveled -= tankDistAnimChange;
		animationState++;

		if (animationState > 1)
			animationState = 0;

		RefreshSprite();
	}
}

void Tank::Die()
{
	if (isDead)
		return;
	isDead = true;
	EnableRendering(false);
}
