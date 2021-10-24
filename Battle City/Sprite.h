#pragma once

#include <SDL.h>
#include <Vectors.h>
#include <vector>

class Sprite // Data conainer for texture location
{
private:
	SDL_Rect textureData; // Position and dimensions

public:

	Sprite();
	Sprite(SDL_Rect data);
	Sprite(Vector2 texturePosition, int Width, int Height);
	Sprite(Vector2 texturePosition, Vector2 widthHeight);

	~Sprite();

	SDL_Rect* GetTextureData();
	Vector2 GetTexturePosition();
	int GetTextureWidth();
	int GetTextureHeight();
};

/*
//Colour yellow-white-green-red
//Line 0-7
//Collum 0-7
Sprite* GetSprite(int colour, int line, int column);
Sprite* GetBulletSprite(int dir);

void InitializeAllSprites();
void LoadAllTankSprites();
vector<vector<Sprite>> LoadOneTankMatrix(int start_x, int start_y);
*/