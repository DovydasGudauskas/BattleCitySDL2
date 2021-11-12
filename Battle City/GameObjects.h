#pragma once

#include <Sprite.h>
#include <SpriteObject.h>
#include <Vectors.h>
#include <Tick.h>

enum class Direction
{
	Up = 0,
	Left = 1,
	Down = 2,
	Right = 3
};

class Tank : public CollidableSpriteObject
{
public:
	Tank();
	Tank(int TankType, int HP, int PlayerType);
	~Tank();

	void GoDirection(Vector2 direction);
	void Fire();

	void SetDirection(Direction dir);
	Direction GetDirection();

	void FetchNewSprites();
	void DamageTank(int dmg);

	void Translate(Vector2 vec) override;

	void Tick() override;

	void DamageTank();

	bool IsTank() override;

	//void SetInvincibleFlag(bool var);
private:
	void Die();
	void Initialize();
	void SetStatsThroughType();
	void RefreshSprite();

	bool isDead; //invincible
	float speed, maxFireCooldown, fireTime, distanceTraveled;
	int animationState, tankType, hp, playerType;

	Direction lookDirection;

	std::vector<Sprite> tankSprites; // of single HP
};


class Bullet : public TriggerCollidable
{
public:
	Bullet(Direction dir, float speed);
	~Bullet();

	void OnCollision(CollidableSpriteObject* collision) override;
private:
	Direction direction;
	Vector2 goDir;
};
