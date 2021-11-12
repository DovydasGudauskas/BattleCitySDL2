#include <Game.h>

int main(int argc, char* argv[])
{
	Game* newGame = Game::GetReference();
	newGame->StartGame();

	return 0;
}