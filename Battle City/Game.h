#include <SDL.h>

enum class GameState
{
	MainMenu = 0,
	InGame
};

#define MainMenu GameState::MainMenu
#define InGame GameState::InGame

class Game
{
public:
	Game():gameWindow(nullptr), currentGameState(MainMenu)
	{
		if(singleton == nullptr)
			singleton = this;
	}
	~Game();

	void InitializeGame();
	void StartTicking();
	void QuitGame();

private:
	static Game* singleton;

	GameState currentGameState;

	SDL_Window* gameWindow;

	void RenderGame();
	void TickInGame();
	void TickMainMenu();
};