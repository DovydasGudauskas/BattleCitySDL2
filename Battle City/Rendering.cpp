#include <Rendering.h>
#include <list>
#include <GameMap.h>
#include <string>

Rendering* Rendering::singleton = nullptr;

void Rendering::DrawMapBackground()
{
	SDL_SetRenderDrawColor(mainRenderer, 0, 0, 0, 255);
	SDL_RenderDrawRect(mainRenderer, NULL);
}

void Rendering::RenderAllObjects()
{
	list<SpriteObject*> allObjects = SpriteObject::GetAllObjects();
	list<SpriteObject*>::iterator it = allObjects.begin();

	while (it != allObjects.end())
	{
		SpriteObject* obj = *it;

		// Render object
		if(obj->IsEnabled())
			SDL_RenderCopy(mainRenderer, tileset, obj->GetTextureData(), obj->GetRenderData(renderScale));

		it++;
	}
}

void Rendering::RenderMap()
{
	vector<SpriteObject*>* mapTiles = GameMap::GetReference()->GetMapTiles();
	for (int i = 0; i < mapTiles->size(); i++)
		SDL_RenderCopy(mainRenderer, tileset, (*mapTiles)[i]->GetTextureData(), (*mapTiles)[i]->GetRenderData(renderScale));

	for (int i = 0; i < overlayTextures.size(); i++)
		SDL_RenderCopy(mainRenderer, tileset, overlayTextures[i]->GetTextureData(), overlayTextures[i]->GetRenderData(renderScale));
}

void Rendering::RenderGame()
{
	SDL_RenderClear(mainRenderer);

	DrawMapBackground();
	RenderAllObjects();
	//RenderMap();

	SDL_RenderPresent(mainRenderer);
}

void Rendering::RenderMainMenu()
{
	SDL_RenderClear(mainRenderer);

	DrawMapBackground();
	RenderAllObjects();

	SDL_RenderPresent(mainRenderer);
}

Rendering::Rendering()
{
	if (singleton == nullptr)
	{
		singleton = this;
		InitializeMapTiles();
		InitializeOverlay();
		InitializeFont();
		InitializeTankTextures();
	}

	mainRenderer = nullptr;
	tileset = nullptr;
}

void Rendering::InitializeOverlay()
{
	overlayTextures.resize(4);

	std::vector<Vector2> Positions = { Vector2(4., 4.), Vector2(4.,4.), Vector2(4.,220.), Vector2(228.,4.) };
	std::vector<Vector2> Scales = { Vector2(32., 1.), Vector2(2., 28.), Vector2(32., 1.), Vector2(4., 28.) };

	for (int i = 0; i < 4; i++)
	{
		overlayTextures[i] = new SpriteObject(mapPrefabTiles[5], false);
		overlayTextures[i]->SetPosition(Positions[i]);
		overlayTextures[i]->SetScale(Scales[i]);
	}
}

void Rendering::InitializeFont()
{
	std::string charSet = "0123456789abcdefghijklmnopqrstuvwxyz-";

	Vector2 letterPositions[37];

	for (int i = 0; i < 10; i++) // 0123456789
		letterPositions[i] = Vector2(256 + i * 8, 48);

	for (int i = 10; i < 28; i++) // abcdefghijklmnopqr
		letterPositions[i] = Vector2(256 + (i-10) * 8, 56);

	for (int i = 28; i < 37; i++) // stuvwxyz-
		letterPositions[i] = Vector2(256 + (i - 28) * 8, 64);

	Vector2 letterSize = Vector2(8, 8);

	for (size_t i = 0; i < 37; i++)
	{
		lettersData.push_back(Sprite(letterPositions[i], letterSize));
		lettersHashmap[charSet[i]] = i;
	}
}

void Rendering::InitializeMapTiles() // Niekas, plytos, gelezine_seina, krumai, gelezines_grindys, 3 tipu vanduo
{
	for (int i = 0; i < 7; i++)
	{
		int x, y;

		if (i < 4)
		{
			x = i * 8;
			y = 0;
		}
		else
		{
			x = (i - 4) * 8;
			y = 8;
		}

		double X = x;

		mapPrefabTiles.push_back(Sprite(Vector2(256. + X, y), 8, 8));
	}
}

std::vector<Sprite> Rendering::GetTankTextures(int tankType, int HP, int playerType)
{
	if (HP - 1 < 0)
		HP = 1;

	switch (playerType)
	{
	case 0:
		return tankMatrix[1][HP-1];
		break;
	case 1:
		return tankMatrix[2][HP-1];
		break;

	default:
		return tankMatrix[HP-1][tankType + 4];
		break;
	}

	return std::vector<Sprite>();
}

vector<vector<Sprite>> Rendering::LoadOneTankMatrix(int start_x, int start_y)
{
	vector<vector<Sprite>> TextureMatrix;

	for (uint8_t y = 0; y < 128; y += 16)
	{
		vector<Sprite> TextureLine;

		for (uint8_t x = 0; x < 128; x += 16) 
			TextureLine.push_back(Sprite(Vector2((double)x + start_x, (double)y + start_y), 16, 16));

		TextureMatrix.push_back(TextureLine);
	}

	return TextureMatrix;
}

void Rendering::InitializeTankTextures()
{
	tankMatrix.push_back(LoadOneTankMatrix(128, 0));   // White
	tankMatrix.push_back(LoadOneTankMatrix(0, 0));     // Yellow
	tankMatrix.push_back(LoadOneTankMatrix(0, 128));   // Green
	tankMatrix.push_back(LoadOneTankMatrix(128, 128)); // Red
}

Rendering::~Rendering()
{
	for (size_t i = 0; i < overlayTextures.size(); i++)
		delete overlayTextures[i];
}

Rendering* Rendering::GetReference()
{
	if (singleton == nullptr)
		return new Rendering();

	return singleton;
}

Vector2 Rendering::GetRenderScale()
{
	return renderScale;
}

void Rendering::SetTileset(SDL_Texture* tileset_)
{
	tileset = tileset_;
}

void Rendering::SetRenderer(SDL_Renderer* renderer)
{
	mainRenderer = renderer;
}

SDL_Renderer* Rendering::GetRenderer()
{
	return mainRenderer;
}

std::vector<Sprite>* Rendering::GetMapPrefabTiles()
{
	return &mapPrefabTiles;
}

std::vector<Sprite>* Rendering::GetLetterTextures()
{
	return &lettersData;
}

Sprite Rendering::GetLetterTexture(char letter)
{
	if (!lettersHashmap.count(letter))
		return Sprite();

	return lettersData[lettersHashmap[letter]];
}
