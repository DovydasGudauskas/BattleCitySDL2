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
	std::list<SpriteObject*> allObjects = SpriteObject::GetAllObjects();
	std::list<SpriteObject*>::iterator it = allObjects.begin();

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
	std::vector<SpriteObject*>* mapTiles = GameMap::GetReference()->GetMapTiles();
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
	RenderMap();

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
	std::string charSet = "0123456789abcdefghijklmnopqrstuvwxyz";

	Vector2 letterPositions[36];

	for (int i = 0; i < 10; i++) // 0123456789
		letterPositions[i] = Vector2(256 + i * 8, 48);

	for (int i = 10; i < 28; i++) // abcdefghijklmnopqr
		letterPositions[i] = Vector2(256 + (i-10) * 8, 56);

	for (int i = 28; i < 36; i++) // stuvwxyz
		letterPositions[i] = Vector2(256 + (i - 28) * 8, 64);

	Vector2 letterSize = Vector2(8, 8);

	for (size_t i = 0; i < 36; i++)
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

Rendering::~Rendering()
{
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
