#pragma once

#include <Tick.h>
#include <GameObjects.h>
#include <vector>

using namespace std;

class EnemySpawner : public Tickable
{
public:
	void Tick() override;

	void StartSpawning(int level);

	static EnemySpawner* GetReference();
private:
	static EnemySpawner* singleton;

	bool isSpawning;

	int ticksToSpawn, tickCount, maxTankCount;

	vector<Tank*> spawnBuffer;

	void ClearBuffer();
	void SpawnNextTank();

	EnemySpawner();
	~EnemySpawner();
};