#include <GameMap.h>
#include <Windows.h>
#include <fstream>
#include <Rendering.h>

GameMap* GameMap::singleton = nullptr;

GameMap::GameMap()
{
	if (singleton == nullptr)
		singleton = this;
	else
		return;
}

GameMap::~GameMap()
{
	ClearMap();
}

GameMap* GameMap::GetReference()
{
	if (singleton == nullptr)
		return new GameMap();

	return singleton;
}

std::vector<SpriteObject*>* GameMap::GetMapTiles()
{
	return &MapTiles;
}

void GameMap::AddNewTile(char* tileRead, int posX, int posY, vector<Sprite>* tiles)
{
	int whichTile = (int)(*tileRead - '0');

	if (whichTile == 0 || whichTile >= tiles->size())
		return;

	Sprite* sprite = &tiles->at(whichTile);
	SpriteObject* foo = new SpriteObject(*sprite, layerType::MapTiles);

	double X = posX, Y = posY;

	foo->SetPosition(Vector2(X * 8. + 20., Y * 8. + 12.));

	MapTiles.push_back(foo);
}

void GameMap::ReadMapLine(string* line, int posY, vector<Sprite>* tiles)
{
	for (int x = 0; x < line->size(); x++)
		AddNewTile(&line->at(x), x, posY, tiles);
}

void GameMap::LoadMap(int Level)
{
	vector<string> dataLines;

	ifstream Read ("Levels/" + to_string(Level) + ".txt");

	for (;;)
	{
		string a; 
		Read >> a;

		if (a == "") break;

		dataLines.push_back(a);
	}

	Read.close();

	vector<Sprite>* tiles = Rendering::GetReference()->GetMapPrefabTiles();

	for (int y = 0; y < dataLines.size(); y++)
		ReadMapLine(&dataLines[y], y, tiles);
}

void GameMap::ClearMap()
{
	for (size_t i = 0; i < MapTiles.size(); i++)
		delete MapTiles[i];

	MapTiles.clear();
}
