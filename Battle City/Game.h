#pragma once

#include <SDL.h>
#include <MainMenu.h>

enum class GameState
{
	MainMenu = 0,
	InGame
};

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

	void RenderGame();

	void TickInGame();
	void TickMainMenu();

	void StartTicking();
};