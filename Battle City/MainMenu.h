#pragma once

#include <vector>
#include <Sprite.h>
#include <SpriteObject.h>
#include <Text.h>

class MainMenu
{
public:
	MainMenu();
	~MainMenu();

	void Tick();
	void Enable(bool var);
private:
	bool isAnimPlaying;
	bool enabled;

	int currentPage;
	int previousKeyState;
	int previousSpaceState;

	float moveAmount;
	float moveSpeed;

	std::vector<SpriteObject*> titleLetters;
	Sprite titleSprites[8];

	std::vector<Page*> pages;

	void InitializeTitle();
	void InitializePages();

	void TickMenuAnim();

	void PlayAnimation();
	void StopAnimation();
};