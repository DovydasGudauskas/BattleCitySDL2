#include <SDL.h>
#include <Vectors.h>

class Rendering
{
private:
	static Rendering* singleton;

	SDL_Texture* tileset;
	SDL_Renderer* mainRenderer;

	const Vector2 renderScale = Vector2(.4, .4);

	void DrawMapBackground();
	void RenderAllObjects();
	void RenderMap();

public:
	Rendering* GetRendering()
	{
		if (singleton == nullptr)
			singleton = new Rendering();

		return singleton;
	}

	Vector2 GetRenderScale();

	void SetTileset(SDL_Texture* tileset_);
	void SetRenderer(SDL_Renderer* renderer);

	void RenderGame();
};