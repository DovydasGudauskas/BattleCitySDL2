#include <vector>
#include "Sprite.h"

using namespace std;

vector<vector<vector<Sprite>>> tankSprites;
vector<Sprite> bulletSprites;

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