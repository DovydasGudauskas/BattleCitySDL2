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
	bool paused, pressedPause, gameQuit;

	MainMenu mainMenu;
	static Game* singleton;

	GameState currentGameState;
	GameMode currentGameMode;

	SDL_Window* gameWindow;

	void TickAnimations();
	void TickTickables();
	void TickControllers();
	void TickInGame();
	void TickMainMenu();
	void TickCollision();

	void SpawnPlayers();

	void StartTicking();

	void LoadLevel(int lvl);
	void CreateNewPlayer(int player);
};