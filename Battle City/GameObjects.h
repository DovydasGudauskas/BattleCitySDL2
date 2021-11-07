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
	void FetchNewSprites();
	void DamageTank(int dmg);

	void Translate(Vector2 vec) override;

	void Tick() override;

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

	void OnCollision() override;
private:
	Direction direction;
	Vector2 goDir;
};

/*
using namespace std;

const double TankSpeed = 0.75;
const int MaxFireCooldown = 45;
class PlayerTank : public SpriteObject
{
private:
	int playerID, hp, fireCooldown, animationAdd;
	Direction lookDir;
public:
	PlayerTank() :SpriteObject(), playerID(0), hp(1), lookDir(Direction::Up), fireCooldown(0), animationAdd(0) {}
	PlayerTank(int ID) :SpriteObject(), playerID(ID), hp(1), lookDir(Direction::Up), fireCooldown(0), animationAdd(0) {}
	PlayerTank(int ID, Sprite sprite) :SpriteObject(sprite), playerID(ID), hp(1), lookDir(Direction::Up), fireCooldown(0), animationAdd(0) {}
	~PlayerTank() {}

	int GetFacingDirectionAdditive() { return animationAdd; }
	int GetFacingDirection() { return (int)lookDir; }
	int GetPlayerID() { return playerID; }
	int GetHealth() { return hp; }
	int GetCooldown() { return fireCooldown; }

	void SetFireCooldown(int newCooldown) { fireCooldown = newCooldown; }
	void ChangeDirection(int Dir) { lookDir = (Direction)Dir; }
	void TriggerAnimation()
	{
		if (animationAdd == 0) animationAdd = 1;
		else animationAdd = 0;
	}
};

PlayerTank* CreatePlayerTank(int PlayerID)
{
	PlayerTank* foo = new PlayerTank(PlayerID, GetSprite(0,0,0));
	if (PlayerID % 2 == 0) foo->SetPosition(Vector2(151, 208));
	else foo->SetPosition(Vector2(104, 208));
	foo->InitializeBoundingBox(13, 13);
	return foo;
}

class Bullet : public SpriteObject
{
private:
	Direction lookDir;
public:
	Bullet() :SpriteObject(), lookDir(Direction::Up) { ParentType = 1; }
	Bullet(Direction dir) :SpriteObject(), lookDir(dir) { ParentType = 1; }
	~Bullet() {}

	int GetFacingDirection() { return (int)lookDir; }

	void ChangeDirection(int Dir) { lookDir = (Direction)Dir; }
};

vector<Bullet*> bullets;
vector<Bullet*> nonInitializedBullets;

vector<Bullet*>* GetBulletsVector() { return &bullets; }

void SpawnABullet(Direction dir, Vector2 position)
{
	Bullet* foo = new Bullet(dir);
	foo->SetPosition(position);
	foo->InitializeBoundingBox(4, 4);
	foo->SetSprite(GetBulletSprite((int)dir));
	bullets.push_back(foo);
	nonInitializedBullets.push_back(foo);
}

vector<int> Player_One_MoveCodes = { VK_UP,VK_LEFT,VK_DOWN,VK_RIGHT,VK_RETURN };
vector<int> Player_Two_MoveCodes = { 'W','A','S','D',VK_SPACE };
vector<Vector2> directions = { Vector2(0., -1.), Vector2(-1., 0.), Vector2(0., 1.), Vector2(1., 0.) };
void HandlePlayerMovements(PlayerTank* player)
{
	vector<int> controls;
	if (player->GetPlayerID() % 2 == 0) controls = Player_One_MoveCodes;
	else controls = Player_Two_MoveCodes;

	bool moved = false;
	Vector2 moveDir(0., 0.);
	for (int i = 0; i < 4; i++) if (GetAsyncKeyState(controls[i]) && 0x8000) { player->ChangeDirection(i); moved = true; moveDir = directions[i]; }// movement

	if(player->GetCooldown() > 0) player->SetFireCooldown(player->GetCooldown() - 1);// Fire
	else if(GetAsyncKeyState(controls[4]) && 0x8000)
	{
		SpawnABullet((Direction)player->GetFacingDirection(), player->GetPosition() + directions[player->GetFacingDirection()] * 9);
		player->SetFireCooldown(MaxFireCooldown);
	}

	if (moved)
	{ 
		player->Translate(moveDir * TankSpeed); 
		player->TriggerAnimation();
		if (player->GetPlayerID() % 2 == 0)
			player->SetSprite(GetSprite(0, player->GetHealth() - 1, player->GetFacingDirection() * 2 + player->GetFacingDirectionAdditive()));
		else
			player->SetSprite(GetSprite(2, player->GetHealth() - 1, player->GetFacingDirection() * 2 + player->GetFacingDirectionAdditive()));
	}

	player->CheckIfIsInPlayArea();

	if (player->HasBeenHitByABullet())
	{
		player->ResetBulletHit();
		player->ResetPosition();
	}
}


class EnemyTank : public SpriteObject
{
private:
	int type, hp, fireCooldown, animationAdd;//Tipai priesu yra: (0123) default, fast, upgraded, heavy 
	Direction lookDir;
	Vector2 oldPos;

public:
	int looktime = 10;
	EnemyTank() :SpriteObject(), type(0), hp(1), lookDir(Direction::Down), fireCooldown(0), animationAdd(0), oldPos(){}
	EnemyTank(int Type) :SpriteObject(), type(Type), hp(1), lookDir(Direction::Down), fireCooldown(0), animationAdd(0), oldPos() {}
	EnemyTank(int Type, Sprite* sprite, int HP) :SpriteObject(sprite), type(Type), hp(HP), lookDir(Direction::Down), fireCooldown(0), animationAdd(0), oldPos() {}
	~EnemyTank() {}

	void ResetFireCoolDown() { fireCooldown = MaxFireCooldown+5; }
	void ReduceFireCoolDown() {if (fireCooldown > 0) fireCooldown--;}
	int GetFireCooldown() { return fireCooldown; }

	void ReduceHealth() { hp--; }
	int GetHealth() { return hp; }

	int GetFacingDirectionAdditive() { return animationAdd; }
	int GetFacingDirection() { return (int)lookDir; }
	int GetType() { return type; }
	bool HasPositionChanged()
	{ 
		return !(oldPos == GetPosition());
	}

	void RandomizeDirection()
	{
		int bar = rand() % 3 - 1;//0-2 -> -1 - 1
		int foo = (int)lookDir + bar;
		if (foo > 3) foo = 0;
		else if (foo < 0) foo = 3;
		lookDir = (Direction)foo;
		oldPos = Vector2();
	}
	void SetOldPos(Vector2 position) { oldPos = position; }
	void ChangeDirection(int Dir) { lookDir = (Direction)Dir; }
	void TriggerAnimation()
	{
		if (animationAdd == 0) animationAdd = 1;
		else animationAdd = 0;
	}
};

EnemyTank* CreateEnemyTank(int Type, int hp, Vector2 position)
{
	EnemyTank* foo = new EnemyTank(Type, GetSprite(1, 0, 4), hp);
	foo->SetPosition(position);
	foo->InitializeBoundingBox(14, 14);
	foo->SetParentType(2);
	return foo;
}

const int enemyFireSensitivity = 8;
bool ShouldFire(Vector2 position, Vector2 target, int facingDir)
{
	if (facingDir == 0 && position.y > target.y&& abs(position.x - target.x) < enemyFireSensitivity) return true;//up
	else if (facingDir == 1 && position.x > target.x&& abs(position.y - target.y) < enemyFireSensitivity) return true;//left
	else if (facingDir == 2 && position.y < target.y && abs(position.x - target.x) < enemyFireSensitivity) return true;//down
	else if (position.x < target.x && abs(position.y - target.y) < enemyFireSensitivity) return true;//right
	return false;
}

const double EnemyTankSpeed = 0.5;
const vector<Vector2> dir = { Vector2(0.,-1.),Vector2(-1.,0.),Vector2(0.,1.),Vector2(1.,0.) };//up, left, down, right
void HandleEnemyUnit(EnemyTank* enemy, vector<PlayerTank*>* playerTanks)
{	
	enemy->TriggerAnimation();

	Vector2 moveDir = dir[enemy->GetFacingDirection()];
	enemy->Translate(moveDir * EnemyTankSpeed);
	enemy->CheckIfIsInPlayArea();
	if (!enemy->HasPositionChanged()) enemy->RandomizeDirection();

	enemy->SetOldPos(enemy->GetPosition());
	if (enemy->HasBeenHitByABullet()) { enemy->ReduceHealth(); enemy->ResetBulletHit(); }
	enemy->SetSprite(GetSprite(enemy->GetHealth(), enemy->GetType() + 4, enemy->GetFacingDirection() * 2 + enemy->GetFacingDirectionAdditive()));

	if (enemy->GetFireCooldown() > 0)enemy->ReduceFireCoolDown();
	else
	{
		for (int i = 0; i < playerTanks->size(); i++)
		{
			PlayerTank* temp = (*playerTanks)[i];
			if (ShouldFire(enemy->GetPosition(), temp->GetPosition(), enemy->GetFacingDirection()))
			{
				SpawnABullet((Direction)enemy->GetFacingDirection(), enemy->GetPosition() + directions[enemy->GetFacingDirection()] * 9);
				enemy->ResetFireCoolDown();
			}
		}
	}

	if (enemy->GetHealth() <= 0) enemy->MarkForDeletion();
}

const double bulletSpeed = 2;
void handleBullet(Bullet* bullet)
{
	if (bullet->IsMarkedForDeletion())return;
	Vector2 moveDir = dir[bullet->GetFacingDirection()];
	bullet->Translate(moveDir * bulletSpeed);

	if (bullet->HasBeenHitByABullet() || bullet->CheckIfIsInPlayArea()) bullet->MarkForDeletion();
}
*/