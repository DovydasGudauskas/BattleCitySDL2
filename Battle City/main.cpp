#include <Game.h>

/*#include <SDL.h>
#include <vector>
#include <Windows.h>
#include <string>
#include "GameMap.h"
#include "GameObjects.h"

using namespace std;
*/
/*


void HandleAllEnemyTanks()
{

				AllEnemyTanks[i].FireTime = 64;
				if(Dir == 0) FireBullet(Position.x+32-8, Position.y-8, Dir);//up
				else if (Dir == 1) FireBullet(Position.x-8, Position.y+32-8, Dir);//left
				else if (Dir == 2) FireBullet(Position.x+32-12, Position.y+44, Dir);//down
				else FireBullet(Position.x+32-8, Position.y+32-8, Dir);//right
}
*/
/*
vector<SpriteObject*> Objects;
vector<EnemyTank*> Enemies;
vector<PlayerTank*> PlayerTanks;
Vector2 MainRes(255, 223), ResScale(4., 4.);

void RenderAllObjects(SDL_Renderer* Renderer, SDL_Texture* Tileset)
{
	for (int i = 0; i < Objects.size(); i++)
	{
		//if (SpriteRenderers[i].IsMarkedForDeletion)continue;
		//SpriteRenderers[i].ScalePosition();
		SDL_RenderCopy(Renderer, Tileset, Objects[i]->GetSourceRect(), Objects[i]->GetDestinationRect(ResScale));
	}
}

void Render(SDL_Renderer* Renderer, SDL_Texture* Tileset)
{
	SDL_RenderClear(Renderer);
	SDL_SetRenderDrawColor(Renderer, 132, 130, 132, 255);
	DrawMapBackground(Renderer);// Render juoda fona
	RenderAllObjects(Renderer, Tileset);// Render visus sprite objektus
	RenderMap(Renderer);// Render zemelapio objektus, pvz sienas
	SDL_RenderPresent(Renderer);
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

void CreateNewEnemy(int type, int hp, Vector2 position)
{
	EnemyTank* TestEnemy = CreateEnemyTank(type, hp ,position);
	Objects.push_back(TestEnemy);
	Enemies.push_back(TestEnemy);
}

void HandleEnemyUnits(vector<PlayerTank*>* playerTanks)
{
	for (int i = 0; i < Enemies.size(); i++) HandleEnemyUnit(Enemies[i], playerTanks);
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

void CheckForEmptyObjects()
{
	for (int i = 0; i < Objects.size(); i++)
	{
		if (!Objects[i]->IsMarkedForDeletion()) continue;
		if (Objects[i]->GetParentType() == 1)
		{
			for (int j = 0; j < bullets.size(); j++)
			{
				SpriteObject* foo = bullets[j];
				if (Objects[i] == foo)
				{
					bullets.erase(bullets.begin() + j);
					break;
				}
			}
		}
		else if (Objects[i]->GetParentType() == 2)
		{
			for (int j = 0; j < Enemies.size(); j++)
			{
				SpriteObject* foo = Enemies[j];
				if (Objects[i] == foo)
				{
					Enemies.erase(Enemies.begin() + j);
					break;
				}
			}
		}
		Objects.erase(Objects.begin() + i);
		i--;
	}


	vector<SpriteObject*>* MapTiles = (vector<SpriteObject*>*)GetMapTiles();
	for (int i = 0; i < MapTiles->size(); i++)
	{
		SpriteObject* foo = (*MapTiles)[i];
		if (!foo->IsMarkedForDeletion()) continue;
		RemoveMapTile(i);
		i--;
	}
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
}

void AddPlayer(int which)
{
	PlayerTank* PlayerOne = CreatePlayerTank(which);
	Objects.push_back(PlayerOne);
	PlayerTanks.push_back(PlayerOne);
}
*/
int main(int argc, char* argv[])
{
	Game* newGame = Game::GetReference();
	newGame->StartGame();

	return 0;
	/*
	InitializeAllSprites();

	AddPlayer(0);

	for (;;)
	{
		HandlePlayerMovements(PlayerTanks[0]);
		HandleEnemyUnits(&PlayerTanks);
		HandleCollision();
		HandleAllBullets();
		SpawnNewEnemies();

	}*/
}