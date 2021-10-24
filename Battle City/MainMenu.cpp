
#include <MainMenu.h>
#include <Vectors.h>
#include <Windows.h>
#include <Game.h>
#include <GameMap.h>

void MainMenu::InitializeTitle()
{
	Vector2 spritePositions[8] = {
		Vector2(256,192),
		Vector2(288,192),
		Vector2(320,192),
		Vector2(256,224),
		Vector2(280,224),
		Vector2(304,224),
		Vector2(328,224),
		Vector2(352,224), };
	Vector2 spriteSizes[8] = {
		Vector2(28,28),
		Vector2(28,28),
		Vector2(28,28),
		Vector2(24,28),
		Vector2(24,28),
		Vector2(20,28),
		Vector2(24,28),
		Vector2(24,28), };

	for (size_t i = 0; i < 8; i++)
		titleSprites[i] = Sprite(spritePositions[i], spriteSizes[i]);

	int lettersToUse[10] = { 0,1,3,3,4,5,2,6,3,7 };

	Vector2 objectPositions[10] = {
		Vector2(46, 58),
		Vector2(82, 58),
		Vector2(115,58),
		Vector2(147,58),
		Vector2(179,58),
		Vector2(209,58),
		Vector2(82, 94),
		Vector2(116,94),
		Vector2(148,94),
		Vector2(180,94), };

	for (size_t i = 0; i < 10; i++)
	{
		SpriteObject* letter = new SpriteObject(titleSprites[lettersToUse[i]]);
		letter->SetPosition(objectPositions[i]);
		titleLetters.push_back(letter);
	}
}

void MainMenu::InitializePages()
{
	Sprite pointerSprite = Sprite(Vector2(95, 0), 16, 16);

	std::vector<std::string> pageInfo;
	pageInfo.push_back("1 player");
	pageInfo.push_back("2 players");
	pageInfo.push_back("construction");
	pageInfo.push_back("multiplayer");
	pageInfo.push_back("quit");
	Page* mainMenu = new Page(pageInfo, pointerSprite);
	mainMenu->SetPosition(Vector2(92, 132));
	mainMenu->Enable(false);
	pages.push_back(mainMenu);

	pageInfo.clear();
	pageInfo.push_back("host");
	pageInfo.push_back("join");
	pageInfo.push_back("back");
	Page* multiplayer = new Page(pageInfo, pointerSprite);
	multiplayer->SetPosition(Vector2(92, 132));
	multiplayer->Enable(false);
	pages.push_back(mainMenu);
}


MainMenu::MainMenu():isAnimPlaying(false), moveAmount(0), moveSpeed(2.5), titleLetters(), currentPage(0), previousKeyState(0), enabled(true)
{
	InitializeTitle();
	InitializePages();

	PlayAnimation();
}

MainMenu::~MainMenu()
{
	for (size_t i = 0; i < titleLetters.size(); i++)
		delete titleLetters[i];

	for (size_t i = 0; i < pages.size(); i++)
		delete pages[i];
}

void MainMenu::PlayAnimation()
{
	if (isAnimPlaying)
		return;

	isAnimPlaying = true;
	moveAmount = 200;

	Vector2 move = Vector2(0, moveAmount);
	for (size_t i = 0; i < titleLetters.size(); i++)
		(titleLetters[i])->Translate(move);
}

void MainMenu::StopAnimation()
{
	if (!isAnimPlaying)
		return;

	if (moveAmount < 0)
		moveAmount = 0;

	Vector2 move = Vector2(0, -moveAmount);
	for (size_t i = 0; i < titleLetters.size(); i++)
		(titleLetters[i])->Translate(move);

	isAnimPlaying = false;
	moveAmount = 0;

	for (size_t i = 0; i < pages.size(); i++)
		pages[i]->Enable(false);

	pages[0]->Enable(true);
}

void MainMenu::TickMenuAnim()
{
	if (moveAmount <= 0)
	{
		StopAnimation();
		return;
	}

	moveAmount -= moveSpeed;

	Vector2 move = Vector2(0, -moveSpeed);
	for (size_t i = 0; i < titleLetters.size(); i++)
		(titleLetters[i])->Translate(move);
}

void MainMenu::Enable(bool var)
{
	if (enabled == var)
		return;

	enabled = var;

	for (size_t i = 0; i < titleLetters.size(); i++)
		titleLetters[i]->EnableRendering(enabled);

	for (size_t i = 0; i < pages.size(); i++)
		pages[i]->Enable(enabled);
}

void MainMenu::Tick()
{
	if (isAnimPlaying)
	{
		if (GetAsyncKeyState(VK_SPACE))
		{
			previousSpaceState = 1;
			StopAnimation();
			return;
		}

		TickMenuAnim();
		return;
	}

	if (GetAsyncKeyState('W') || GetAsyncKeyState(VK_UP))
	{
		if(previousKeyState != 1)
			pages[currentPage]->GoUp();
		previousKeyState = 1;
	}
	else if (GetAsyncKeyState('S') || GetAsyncKeyState(VK_DOWN))
	{
		if (previousKeyState != -1)
			pages[currentPage]->GoDown();

		previousKeyState = -1;
	}
	else
		previousKeyState = 0;

	if (GetAsyncKeyState(VK_SPACE))
	{
		if (previousSpaceState != 1)
		{
			int selection = pages[currentPage]->GetCurrentSelection();

			if (currentPage == 0)
			{
				switch (selection)
				{
				case 0:
					Game::GetReference()->StartNewGame(0);
					break;
				case 4:
					Game::GetReference()->QuitGame();
					break;
				default:
					break;
				}
			}
			else
			{
				switch (selection)
				{
				default:
					break;
				}
			}
		}

		previousSpaceState = 1;
	}
	else
		previousSpaceState = 0;
}
