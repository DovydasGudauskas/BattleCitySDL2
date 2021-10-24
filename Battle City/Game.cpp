#include <Game.h>
#include <Windows.h> // GetAsyncKeyState

#include <Rendering.h>
#include <Vectors.h>

#include <GameMap.h>

/*#include "Vectors.h"
#include "Sprite.h"
#include "Rendering.cpp"*/

Game* Game::singleton = nullptr;

Game::Game():gameWindow(nullptr), currentGameState(GameState::MainMenu), mainMenu(MainMenu())
{
	if (singleton == nullptr)
		singleton = this;
}

Game::~Game()
{
}

void Game::StartGame()
{
	Vector2 MainRes(256, 224);

	Rendering* rendering = Rendering::GetReference();
	Vector2 ResScale = rendering->GetRenderScale();

	// Initialize SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	// Create window
	gameWindow = SDL_CreateWindow("Battle city",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		(int)(MainRes.x * ResScale.x), (int)(MainRes.y * ResScale.y),
		SDL_WINDOW_SHOWN);

	// Set renderer
	SDL_Renderer* mainRenderer = SDL_CreateRenderer(gameWindow, -1, SDL_RENDERER_ACCELERATED);
	rendering->SetRenderer(mainRenderer);

	// Load window icon
	SDL_Surface* Icon = SDL_LoadBMP("Icon.bmp");
	SDL_SetWindowIcon(gameWindow, Icon);
	SDL_FreeSurface(Icon);

	// Load tileset
	SDL_Surface* Surface = SDL_LoadBMP("Tileset.bmp");
	rendering->SetTileset(SDL_CreateTextureFromSurface(mainRenderer, Surface));
	SDL_FreeSurface(Surface);

	//InitializeAllSprites();

	StartTicking();
}

void Game::StartNewGame(int mode)
{
	currentGameState = GameState::InGame;
	mainMenu.Enable(false);
	GameMap::GetReference()->LoadMap(0);
}

void Game::TickMainMenu()
{
	mainMenu.Tick();
}

void Game::RenderGame()
{
}

void Game::TickInGame()
{
	/*
	HandlePlayerMovements(PlayerTanks[0]);
	HandleEnemyUnits(&PlayerTanks);
	HandleCollision();
	HandleAllBullets();
	CheckForEmptyObjects();
	SpawnNewEnemies();	*/
}

void Game::StartTicking()
{
	while (!GetAsyncKeyState(VK_ESCAPE))
	{
		bool run = true;
		SDL_Event event;
		while (SDL_PollEvent(&event))
			if (event.type == SDL_QUIT) run = false;

		if (!run)
			break;


		SDL_Delay(17);

		switch (currentGameState)
		{
		case GameState::MainMenu:
			TickMainMenu();
			Rendering::GetReference()->RenderMainMenu();
			break;

		case GameState::InGame:
			TickInGame();
			Rendering::GetReference()->RenderGame();
			break;

		default:
			break;
		}	
	}

	QuitGame();
}

void Game::QuitGame()
{
	//UnloadMemory();

	SDL_Renderer* renderer = Rendering::GetReference()->GetRenderer();

	if(renderer != nullptr)
		SDL_DestroyRenderer(renderer);

	SDL_DestroyWindow(gameWindow);
	SDL_Quit();
}

Game* Game::GetReference()
{
	if (singleton == nullptr)
		return new Game();

	return singleton;
}