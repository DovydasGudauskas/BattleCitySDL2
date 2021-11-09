#include <Game.h>
#include <Windows.h> // GetAsyncKeyState

#include <Rendering.h>
#include <Vectors.h>

#include <GameMap.h>
#include <Debug.h>
#include <Animation.h>
#include <EnemySpawner.h>

//#include <SDL_image.h>

Game* Game::singleton = nullptr;

Game::Game()
{
	gameWindow = nullptr;
	currentGameState = GameState::MainMenu;
	currentGameMode = GameMode::Singleplayer;
	paused = false;
	pressedPause = false;
	gameQuit = false;

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
	//SDL_Surface* Surface = IMG_Load("Tileset.png");
	rendering->SetTileset(SDL_CreateTextureFromSurface(mainRenderer, Surface));
	SDL_FreeSurface(Surface);

	StartTicking();
}

void Game::StartNewGame(GameMode mode)
{
	currentGameState = GameState::InGame;
	currentGameMode = mode;

	Rendering::GetReference()->EnableGameOverlay(true);
	mainMenu.Enable(false);

	LoadLevel(0);
}

void Game::SpawnPlayers()
{
	switch (currentGameMode)
	{
	case GameMode::Singleplayer:
		CreateNewPlayer(0);
		break;
	case GameMode::LocalMultiplayer:
		CreateNewPlayer(0);
		CreateNewPlayer(1);
		break;
	case GameMode::NetworkMultiplayer:
		CreateNewPlayer(0);
		break;
	default:
		break;
	}
}

void Game::LoadLevel(int lvl)
{
	GameMap::GetReference()->LoadMap(lvl);

	SpawnPlayers();
	EnemySpawner::GetReference()->StartSpawning(lvl);
}

void Game::CreateNewPlayer(int player)
{
	if (player > 1 || player < 0)
		return;

	Tank* playerTank = new Tank(0, 1, player);
	playerTank->SetPosition(playerSpawnPoints[player]);
	//Debug::GetReference()->DebugCollision(playerTank);

	if (player == 1)
	{
		PlayerControllerKeymapping newKeymap;
		newKeymap.up = VK_UP;
		newKeymap.right = VK_RIGHT;
		newKeymap.down = VK_DOWN;
		newKeymap.left = VK_LEFT;
		newKeymap.fire = VK_NUMPAD0;

		PlayerController* player = new PlayerController(newKeymap);
		player->SetControlTank(playerTank);
	}
	else
	{
		PlayerController* player = new PlayerController();
		player->SetControlTank(playerTank);
	}

	//Debug::GetReference()->DebugTank(playerTank, playerSpawnPoints[player]);
}

void Game::TickMainMenu()
{
	mainMenu.Tick();
	TickAnimations();
}

void Game::TickControllers()
{
	list<TankController*>* controllers = TankController::GetAllControllers();
	list<TankController*>::iterator it = controllers->begin();

	while (it != controllers->end())
	{
		(*it)->Tick();
		it++;
	}
}

void Game::TickCollision()
{
	vector<CollidableSpriteObject*>* colls = CollidableSpriteObject::GetAllCollidables();

	for (size_t i = 0; i < colls->size(); i++)
		colls->at(i)->CheckCollision();
}

void Game::TickAnimations()
{
	vector<Animation*>* anims = Animation::GetAllAnimations();

	for (size_t i = 0; i < anims->size(); i++)
		anims->at(i)->Tick();
}

void Game::TickTickables()
{
	vector<Tickable*>* ticks = Tickable::GetAllTicks();

	for (size_t i = 0; i < ticks->size(); i++)
		ticks->at(i)->Tick();
}

void Game::TickInGame()
{
	TickControllers();
	TickAnimations();
	TickTickables();
	TickCollision();

	Debug::GetReference()->Tick();

	/*
	SpawnNewEnemies();	*/
}

void Game::StartTicking()
{
	while (!gameQuit && !GetAsyncKeyState(VK_ESCAPE))
	{
		bool run = true;
		SDL_Event event;
		while (SDL_PollEvent(&event))
			if (event.type == SDL_QUIT) run = false;

		if (!run)
			break;

		SDL_Delay(17);

		if (GetAsyncKeyState('P'))
		{
			if(pressedPause != true)
				paused = !paused;

			pressedPause = true;
		}
		else
			pressedPause = false;

		if (!paused)
		{
			switch (currentGameState)
			{
			case GameState::MainMenu:
				TickMainMenu();
				break;

			case GameState::InGame:
				TickInGame();
				break;

			default:
				break;
			}

			Rendering::GetReference()->RenderWindow();
		}
	}

	if(!gameQuit)
		QuitGame();
}

void Game::QuitGame()
{
	gameQuit = true;

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