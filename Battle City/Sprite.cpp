#include <Sprite.h>

Sprite::Sprite()
{
	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = 1;
	rect.h = 1;
	textureData = rect;
}
Sprite::Sprite(SDL_Rect data)
{
	textureData = data;
}
Sprite::Sprite(Vector2 texturePosition, int width, int height)
{
	SDL_Rect rect;
	rect.x = (int)texturePosition.x;
	rect.y = (int)texturePosition.y;
	rect.w = width;
	rect.h = height;
	textureData = rect;
}

Sprite::Sprite(Vector2 texturePosition, Vector2 widthHeight)
{
	SDL_Rect rect;
	rect.x = (int)texturePosition.x;
	rect.y = (int)texturePosition.y;
	rect.w = (int)widthHeight.x;
	rect.h = (int)widthHeight.y;
	textureData = rect;
}

Sprite::~Sprite()
{

}

SDL_Rect* Sprite::GetTextureData()
{
	return  &textureData;
}
Vector2 Sprite::GetTexturePosition()
{
	return Vector2(textureData.x, textureData.y);
}
int Sprite::GetTextureWidth()
{
	return textureData.w;
}
int Sprite::GetTextureHeight()
{
	return textureData.h;
}

/*

using namespace std;

vector<vector<vector<Sprite>>> tankSprites = vector<vector<vector<Sprite>>>();
vector<Sprite> bulletSprites = vector<Sprite>();

void LoadBulletSprites();

void InitializeAllSprites()
{
	LoadAllTankSprites();
	LoadBulletSprites();
}

Sprite* GetSprite(int colour, int line, int column) { return &tankSprites[colour][line][column]; }

void LoadAllTankSprites()
{
	tankSprites.clear();
	tankSprites.push_back(LoadOneTankMatrix(0, 0));//Yellow
	tankSprites.push_back(LoadOneTankMatrix(128, 0));//White
	tankSprites.push_back(LoadOneTankMatrix(0, 128));//Green
	tankSprites.push_back(LoadOneTankMatrix(128, 128));//Red
}

vector<vector<Sprite>> LoadOneTankMatrix(int start_x, int start_y)
{
	vector<vector<Sprite>> TextureMatrix;
	for (uint8_t y = 0; y < 128; y += 16)
	{
		vector<Sprite> TextureLine;
		for (uint8_t x = 0; x < 128; x += 16) TextureLine.push_back(Sprite(Vector2((double)x + start_x, (double)y + start_y), 16, 16));
		TextureMatrix.push_back(TextureLine);
	}
	return TextureMatrix;
}

Sprite* GetBulletSprite(int dir) { return &bulletSprites[dir]; }

void LoadBulletSprites()
{
	double x = 320;
	for (int i = 0; i < 4; i++)
	{
		bulletSprites.push_back(Sprite(Vector2(x,0.), 4,4));
		x += 4;
	}
}

*/