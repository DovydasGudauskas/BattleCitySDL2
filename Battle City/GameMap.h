#pragma once

#include <string>
#include <Sprite.h>
#include <SpriteObject.h>
#include <vector>

using namespace std;

enum class MapTileType
{
	Brick = 0,
	Stone,
	Bush,
	Ice,
	Water
};

class MapTile : public StaticCollidable
{
public:
	MapTile(Sprite sprite, MapTileType tileType);
	~MapTile();

	FinalObjectType GetFinalObjectType() override;
	MapTileType GetMapTileType();
private:
	MapTileType mapTileType;
};

class GameMap
{
public:
	GameMap();
	~GameMap();

	static GameMap* GetReference();

	vector<MapTile*>* GetMapTiles();

	void LoadMap(int Level);
	void ClearMap();
private:
	static GameMap* singleton;

	vector<MapTile*> MapTiles;

	void AddNewTile(char* tileRead, int posX, int posY, vector<Sprite>* tiles);
	void ReadMapLine(string* line, int posY, vector<Sprite>* tiles);
};