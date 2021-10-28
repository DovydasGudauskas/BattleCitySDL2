#pragma once

#include <SDL.h>
#include <MainMenu.h>
#include <Controllers.h>

enum class GameState
{
	MainMenu = 0,
	InGame
};

const Vector2 playerSpawnPoints[] = { Vector2(0,0), Vector2(0,0) };
const Vector2 enemySpawnPoints[] = { Vector2(0,0), Vector2(0,0), Vector2(0,0) };

class Game
{
public:

	Game();
	~Game();

	void StartGame();
	void StartNewGame(int mode);

	static Game* GetReference();

	void QuitGame();
private:
	MainMenu mainMenu;
	static Game* singleton;

	GameState currentGameState;

	SDL_Window* gameWindow;

	void TickControllers();
	void TickInGame();
	void TickMainMenu();

	void StartTicking();

	void LoadLevel(int lvl);
	void CreateNewPlayer(Vector2 spawnPos);
};