#pragma once

#include <Sprite.h>
#include <SDL.h>
#include <Vectors.h>
#include <vector>
#include <SpriteObject.h>
#include <unordered_map>

using namespace std;

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

	vector<Sprite>* GetMapPrefabTiles();
	vector<Sprite>* GetLetterTextures();
	Sprite GetLetterTexture(char letter);
	vector<Sprite> GetTankTextures(int tankType, int HP, int playerType);

	void EnableGameOverlay(bool var);
	void RenderWindow();

private:
	static Rendering* singleton;

	SDL_Texture* tileset;
	SDL_Renderer* mainRenderer;

	const Vector2 renderScale = Vector2(4.0, 4.0);

	vector<Sprite> mapPrefabTiles;
	vector<SpriteObject*> overlayTextures;

	vector<Sprite> lettersData;
	unordered_map<char, size_t> lettersHashmap;

	vector<vector<vector<Sprite>>> tankMatrix;

	void InitializeMapTiles();
	void InitializeOverlay();
	void InitializeFont();
	void InitializeTankTextures();
	vector<vector<Sprite>> LoadOneTankMatrix(int start_x, int start_y);

	void DrawMapBackground();
	void RenderAllObjects();
};