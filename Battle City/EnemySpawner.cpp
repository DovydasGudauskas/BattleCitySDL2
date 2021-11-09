

#include <EnemySpawner.h>
#include <Controllers.h>
#include <Animation.h>

EnemySpawner* EnemySpawner::singleton = nullptr;

const Vector2 enemySpawnPoints[] = { Vector2(24, 16), Vector2(120, 16), Vector2(216, 16) };

void EnemySpawner::Tick()
{
	if (!isSpawning)
		return;

	if (tickCount > 0)
		tickCount--;
	else
	{
		tickCount = ticksToSpawn;
		SpawnNextTank();
	}
}

void EnemySpawner::SpawnNextTank()
{
	if (spawnBuffer.size() == 0)
	{
		isSpawning = false;
		return;
	}

	SpawnAnimation* newAnim = new SpawnAnimation(spawnBuffer[0]);

	spawnBuffer.erase(spawnBuffer.begin());

	if (spawnBuffer.size() == 0)
		isSpawning = false;
}

void EnemySpawner::StartSpawning(int level)
{
	isSpawning = true;

	ClearBuffer();

	for (size_t i = 0; i < 2; i++)
	{
		Tank* newTank = new Tank(3, 4,-1);

		newTank->SetPosition(enemySpawnPoints[(int)(spawnBuffer.size() % 3)]);
		newTank->EnableRendering(false);
		newTank->SetDirection(Direction::Down);

		AIController* controller = new AIController(newTank);

		spawnBuffer.push_back(newTank);
	}
}

EnemySpawner* EnemySpawner::GetReference()
{
	if (singleton == nullptr)
		return new EnemySpawner();

	return singleton;
}

void EnemySpawner::ClearBuffer()
{
	for (size_t i = 0; i < spawnBuffer.size(); i++)
	{
		delete spawnBuffer[i];
	}

	spawnBuffer.clear();
}

EnemySpawner::EnemySpawner()
{
	if (singleton == nullptr)
		singleton = this;

	isSpawning = false;
	maxTankCount = 5;
	ticksToSpawn = 300;
	tickCount = 0;
}

EnemySpawner::~EnemySpawner()
{
	ClearBuffer();
}
