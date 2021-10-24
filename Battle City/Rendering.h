#pragma once

#include <Sprite.h>
#include <SDL.h>
#include <Vectors.h>
#include <vector>
#include <SpriteObject.h>
#include <unordered_map>

class Rendering
{
public:
	Rendering();
	~Rendering();

	static Rendering* GetReference();

	Vector2 GetRenderScale();

	void SetTileset(SDL_Texture* tileset_);
	void SetRenderer(SDL_Renderer* renderer);
	SDL_Renderer* GetRenderer();

	std::vector<Sprite>* GetMapPrefabTiles();
	std::vector<Sprite>* GetLetterTextures();
	Sprite GetLetterTexture(char letter);

	void RenderGame();
	void RenderMainMenu();

private:
	static Rendering* singleton;

	SDL_Texture* tileset;
	SDL_Renderer* mainRenderer;

	const Vector2 renderScale = Vector2(4.0, 4.0);

	std::vector<Sprite> mapPrefabTiles;
	std::vector<SpriteObject*> overlayTextures;

	std::vector<Sprite> lettersData;
	std::unordered_map<char, size_t> lettersHashmap;

	void InitializeMapTiles();
	void InitializeOverlay();
	void InitializeFont();

	void DrawMapBackground();
	void RenderAllObjects();
	void RenderMap();
};