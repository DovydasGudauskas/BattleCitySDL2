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