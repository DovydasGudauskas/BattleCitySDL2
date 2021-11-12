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

	SetCollisionBounds(Vector2(13,13));

	FetchNewSprites();
	RefreshSprite();
}

void Tank::SetStatsThroughType()
{
	float speedMultiplier = 0.7f;
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
			speed = speedMultiplier;
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
		SetVelocity(Vector2(1, 0) * speed);
	}
	else if (direction.x < -0.1f)
	{
		SetDirection(Direction::Left);
		SetVelocity(Vector2(-1, 0) * speed);
	}
	else if (direction.y > 0.1f)
	{
		SetDirection(Direction::Down);
		SetVelocity(Vector2(0, 1) * speed);
	}
	else if (direction.y < -0.1f)
	{
		SetDirection(Direction::Up);
		SetVelocity(Vector2(0, -1) * speed);
	}
}

void Tank::Fire()
{
	if (fireTime > 0)
		return;

	fireTime = maxFireCooldown;

	Bullet* bullet = new Bullet(lookDirection, 2);
	bullet->SetPosition(position);

	float offset = 8;

	switch (lookDirection)
	{
	default:
	case Direction::Up:
		bullet->Translate(Vector2(0, -offset));
		break;

	case Direction::Left:
		bullet->Translate(Vector2(-offset, 0));
		break;

	case Direction::Down:
		bullet->Translate(Vector2(0, offset));
		break;

	case Direction::Right:
		bullet->Translate(Vector2(offset, 0));
		break;
	}
}

void Tank::SetDirection(Direction dir)
{
	if (dir == lookDirection)
		return;

	lookDirection = dir;

	RefreshSprite();
}

Direction Tank::GetDirection()
{
	return lookDirection;
}

void Tank::RefreshSprite()
{
	SetSprite(tankSprites[((size_t)lookDirection) * 2 + animationState]);
}

void Tank::DamageTank()
{
	hp--;
	if (hp <= 0)
	{
		hp = 0;
		isDead = true;
		EnableRendering(false);
	}
}

bool Tank::IsTank()
{
	return true;
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
	distanceTraveled += (float)vec.Magnitude();

	if (distanceTraveled > tankDistAnimChange)
	{
		distanceTraveled -= tankDistAnimChange;
		animationState++;

		if (animationState > 1)
			animationState = 0;

		RefreshSprite();
	}
}

void Tank::Tick() // Override CollidableSpriteObject
{
	CollidableSpriteObject::Tick();

	if (fireTime > 0)
		fireTime -= 1.f / 60.f;
}

void Tank::Die()
{
	if (isDead)
		return;
	isDead = true;
	EnableRendering(false);
}

// ****************************

Bullet::Bullet(Direction dir, float speed) : direction(dir)
{
	switch (dir)
	{
	default:
	case Direction::Up:
		SetSprite(Sprite(Vector2(320, 0), Vector2(4, 4)));
		velocity = Vector2(0, -1) * speed;
		break;

	case Direction::Left:
		SetSprite(Sprite(Vector2(324, 0), Vector2(4, 4)));
		velocity = Vector2(-1, 0) * speed;
		break;

	case Direction::Down:
		SetSprite(Sprite(Vector2(328, 0), Vector2(4, 4)));
		velocity = Vector2(0, 1) * speed;
		break;

	case Direction::Right:
		SetSprite(Sprite(Vector2(332, 0), Vector2(4, 4)));
		velocity = Vector2(1, 0) * speed;
		break;
	}
}

Bullet::~Bullet()
{
}

void Bullet::OnCollision(CollidableSpriteObject* collision) // override CollidableSpriteObject
{
	CollidableSpriteObject::OnCollision(collision);

	if (collision != nullptr && collision->IsTank())
	{
		Tank* tank = (Tank*)collision;
		tank->DamageTank();
	}

	delete this;
}
