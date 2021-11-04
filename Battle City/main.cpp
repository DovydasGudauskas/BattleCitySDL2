#include <Game.h>

/*

void HandleAllEnemyTanks()
{

				AllEnemyTanks[i].FireTime = 64;
				if(Dir == 0) FireBullet(Position.x+32-8, Position.y-8, Dir);//up
				else if (Dir == 1) FireBullet(Position.x-8, Position.y+32-8, Dir);//left
				else if (Dir == 2) FireBullet(Position.x+32-12, Position.y+44, Dir);//down
				else FireBullet(Position.x+32-8, Position.y+32-8, Dir);//right
}

void HandleCollision()
{
	vector<SpriteObject*>* MapTiles = nullptr;
	MapTiles = (vector<SpriteObject*>*)GetMapTiles();
	for (int i = 0; i < Objects.size(); i++)//objects with map objs
	{
		if (Objects[i]->IsMarkedForDeletion()) continue;
		for (int j = 0; j < MapTiles->size(); j++)
		{
			if ((*MapTiles)[j]->IsMarkedForDeletion()) continue;
			if (Objects[i]->Intersects((*MapTiles)[j]))
				Objects[i]->CorrectPosition((*MapTiles)[j]);
		}
	}

	for (int i = 0; i < Objects.size(); i++)//objects with objects
	{
		if (Objects[i]->IsMarkedForDeletion()) continue;
		for (int j = i + 1; j < Objects.size(); j++)
		{
			if (Objects[j]->IsMarkedForDeletion()) continue;
			if (Objects[i]->Intersects(Objects[j]))
				Objects[i]->CorrectPosition(Objects[j]);
		}
	}
}

void CheckForNewBullets()
{
	for (int i = 0; i < nonInitializedBullets.size(); i++)
	{
		Objects.push_back(nonInitializedBullets[i]);
		nonInitializedBullets[i] = nullptr;
		nonInitializedBullets.erase(nonInitializedBullets.begin());
		i--;
	}
}

void HandleAllBullets()
{
	CheckForNewBullets();
	for (int i = 0; i < bullets.size(); i++) handleBullet(bullets[i]);
}

void SpawnNewEnemies()
{
	if (Enemies.size() == 0)
	{
		int a = rand() % 3;//vieta
		int tipas = rand() % 4;
		int hp = rand() % 3 + 1;//1 iki 3
		if (a == 0) CreateNewEnemy(tipas, hp, Vector2(24, 16));
		else if (a == 1) CreateNewEnemy(tipas, hp, Vector2(118, 16));
		else CreateNewEnemy(tipas, hp, Vector2(216, 16));
	}
}*/

int main(int argc, char* argv[])
{
	Game* newGame = Game::GetReference();
	newGame->StartGame();

	return 0;
	/*
	for (;;)
	{
		HandleCollision();
		HandleAllBullets();
		SpawnNewEnemies();

	}*/
}