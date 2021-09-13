#include <SDL.h>
#include <Windows.h>
#include <string>
#include <fstream>
#include "Sprite.h"

using namespace std;

SDL_Texture* Tileset;
Vector2 CoordScale;

void ScaleRect(SDL_Rect &rect)
{
	rect.x *= (int)CoordScale.x;
	rect.y *= (int)CoordScale.y;
	rect.w *= (int)CoordScale.x;
	rect.h *= (int)CoordScale.y;
}

vector<Sprite> TileSpritePrefabs;
vector<SpriteObject*> MapTiles;

void* GetMapTiles() { return &MapTiles; }

void LoadMap(int Level)
{
	vector<string> MapData;
	ifstream Read ("Levels/" + to_string(Level) + ".txt");
	for (;;)
	{
		string a; Read >> a;
		if (a == "") break;
		MapData.push_back(a);
	}
	Read.close();

	for (int y = 0; y < MapData.size(); y++)
		for (int x = 0; x < MapData[y].length(); x++)
		{
			int Which = (int)(MapData[y][x] - '0');// Paverciam is "string" skaicius i "int" skaicius
			if (Which == 0) continue;
			SpriteObject* foo = new SpriteObject(&TileSpritePrefabs[Which]);
			double X=x, Y=y;
			foo->SetPosition(Vector2(X * 8. + 20., Y * 8. + 12.));
			foo->InitializeBoundingBox(8, 8);
			foo->SetParentType(3);
			MapTiles.push_back(foo);
		}
}

void DrawMapBackground(SDL_Renderer* Renderer)
{
	SDL_Rect background = SDL_Rect();
	background.x = 16 * (int)CoordScale.x;
	background.y = 8 * (int)CoordScale.y;
	background.w = 208 * (int)CoordScale.x;
	background.h = 208 * (int)CoordScale.y;
	SDL_RenderCopy(Renderer, Tileset, TileSpritePrefabs[0].ExtractSourceRect(), &background);
}

vector<SpriteObject> OverlayMask;
void RenderOverlay(SDL_Renderer* Renderer)
{
	for (int i = 0; i < OverlayMask.size(); i++) SDL_RenderCopy(Renderer, Tileset, OverlayMask[i].GetSourceRect(), OverlayMask[i].GetDestinationRect(CoordScale));
}

void RenderMap(SDL_Renderer* Renderer)
{
	for (int i = 0; i < MapTiles.size(); i++) SDL_RenderCopy(Renderer, Tileset, MapTiles[i]->GetSourceRect(), MapTiles[i]->GetDestinationRect(CoordScale));
	RenderOverlay(Renderer);
}

void CreateBlockPrefabs()// Niekas, plytos, gelezine_seina, krumai, gelezines_grindys, 3 tipu vanduo
{
	for (int i = 0; i < 7; i++)
	{
		int x, y;
		if (i < 4) { x = i * 8; y = 0; }
		else { x = (i - 4) * 8; y = 8; }
		double X = x;
		TileSpritePrefabs.push_back(Sprite(Vector2(256. + X, y),8,8));
	}
}

void CreateOverlay()
{
	OverlayMask.resize(4);
	vector<Vector2> Positions = { Vector2(4., 4.),Vector2(4.,4.),Vector2(4.,220.),Vector2(228.,4.) };
	vector<Vector2> Scales = { Vector2(32., 1.),Vector2(2., 28.),Vector2(32., 1.),Vector2(4., 28.) };
	for (int i = 0; i < 4; i++)
	{
		OverlayMask[i] = SpriteObject(&TileSpritePrefabs[5]);
		OverlayMask[i].SetPosition(Positions[i]);
		OverlayMask[i].SetScale(Scales[i]);
	}
}

void InitializeMap(SDL_Texture* TilesetPtr, double scale_x, double scale_y)
{
	Tileset = TilesetPtr;
	CoordScale = Vector2(scale_x, scale_y);
	CreateBlockPrefabs();
	CreateOverlay();
}

void RemoveMapTile(int tileID)
{
	MapTiles.erase(MapTiles.begin() + tileID);
}