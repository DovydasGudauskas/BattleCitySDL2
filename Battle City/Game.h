#pragma once

#include <SDL.h>
#include <MainMenu.h>
#include <Controllers.h>

enum class GameState
{
	MainMenu = 0,
	InGame
};

enum class GameMode
{
	Singleplayer = 0,
	LocalMultiplayer,
	NetworkMultiplayer
};

const Vector2 playerSpawnPoints[] = { Vector2(150,205), Vector2(87,205) };
const Vector2 enemySpawnPoints[] = { Vector2(0,0), Vector2(0,0), Vector2(0,0) };

class Game
{
public:

	Game();
	~Game();

	void StartGame();
	void StartNewGame(GameMode mode);

	static Game* GetReference();

	void QuitGame();
private:
	MainMenu mainMenu;
	static Game* singleton;

	GameState currentGameState;
	GameMode currentGameMode;

	SDL_Window* gameWindow;

	void TickAnimations();
	void TickControllers();
	void TickInGame();
	void TickMainMenu();
	void TickCollision();

	void StartTicking();

	void LoadLevel(int lvl);
	void CreateNewPlayer(int player);
};