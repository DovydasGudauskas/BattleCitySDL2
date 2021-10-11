#include "Game.h"
/*#include "Vectors.h"
#include "Sprite.h"
#include "Rendering.cpp"*/

Game::~Game()
{
}

void Game::InitializeGame()
{
	/*Vector2 MainRes(255, 223), ResScale(4., 4.);

	// Create window
	SDL_Init(SDL_INIT_EVERYTHING);
	gameWindow = SDL_CreateWindow("Battle city", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, (int)(MainRes.x * ResScale.x), (int)(MainRes.y * ResScale.y), SDL_WINDOW_SHOWN);
	SDL_Renderer* mainRenderer = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_ACCELERATED);
	Rendering::SetRenderer(mainRenderer);

	// Load window icon
	SDL_Surface* Icon = SDL_LoadBMP("Icon.bmp");
	SDL_SetWindowIcon(gameWindow, Icon);
	SDL_FreeSurface(Icon);

	// Load tileset
	SDL_Surface* Surface = SDL_LoadBMP("Tileset.bmp");
	Rendering::SetTileset(SDL_CreateTextureFromSurface(mainRenderer, Surface));
	SDL_FreeSurface(Surface);

	InitializeAllSprites();*/
}

void Game::TickMainMenu()
{

}

void Game::TickInGame()
{
	/*if (GetAsyncKeyState(VK_ESCAPE) && 0x8000) break;

	HandlePlayerMovements(PlayerTanks[0]);
	HandleEnemyUnits(&PlayerTanks);
	HandleCollision();
	HandleAllBullets();
	CheckForEmptyObjects();
	SpawnNewEnemies();	*/
}

void Game::StartTicking()
{
	for (;;)
	{
		SDL_Delay(17);

		switch (currentGameState)
		{
		case MainMenu:
			TickMainMenu();
			break;

		case InGame:
			TickInGame();
			break;

		default:
			break;
		}

		//Rendering::RenderGame(mainRenderer);
	}

	QuitGame();
}

void Game::QuitGame()
{
	//UnloadMemory();

	/*SDL_DestroyRenderer(mainRenderer);
	SDL_DestroyWindow(gameWindow);
	SDL_Quit();*/
}