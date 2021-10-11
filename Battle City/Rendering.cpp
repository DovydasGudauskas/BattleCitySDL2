#include <Rendering.h>
//#include <GameMap.h>

void Rendering::DrawMapBackground()
{
	SDL_Rect background = SDL_Rect();

	background.x = 16 * (int)renderScale.x;
	background.y = 8 * (int)renderScale.y;
	background.w = 208 * (int)renderScale.x;
	background.h = 208 * (int)renderScale.y;

	//SDL_RenderCopy(mainRenderer, tileset, GetTilePrefab(0)->ExtractSourceRect(), &background);
}

void Rendering::RenderAllObjects()
{
}

void Rendering::RenderMap()
{
}

void Rendering::RenderGame()
{
	/*SDL_RenderClear(mainRenderer);

	// Draw background
	SDL_SetRenderDrawColor(mainRenderer, 132, 130, 132, 255);
	DrawMapBackground();

	RenderAllObjects();
	RenderMap();

	SDL_RenderPresent(mainRenderer);*/
}

/*Vector2 GetRenderScale()
{
	return renderScale;
}*/

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