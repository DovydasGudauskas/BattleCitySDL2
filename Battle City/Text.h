#pragma once

#include <SpriteObject.h>
#include <vector>
#include <string>
#include <vector>
#include <Animation.h>

using namespace std;

class Text
{
public:
	Text();
	Text(std::string text);
	Text(std::string text, bool active);
	Text(std::string text, Vector2 position);

	~Text();

	void SetText(std::string text);

	void SetPosition(Vector2 pos);
	Vector2 GetPosition();

	void Translate(Vector2 pos);

	void Enable(bool var);
	bool IsEnabled();
private:
	bool enabled;

	string originalText;

	Vector2 position;

	std::vector<SpriteObject*> myLetters;

	void ClearText();
};

class Page
{
public:
	Page();
	Page(std::vector<std::string> btnTex);
	Page(std::vector<std::string> btnText, vector<Sprite> pointerTextures);
	~Page();

	void Enable(bool var);

	void GoUp();
	void GoDown();

	int GetCurrentSelection();

	void SetPointerTextures(vector<Sprite> textures);
	void SetText(vector<string> btnText);

	void ClearText();

	void SetPosition(Vector2 pos);
	void Translate(Vector2 pos);
	Vector2 GetPosition();
private:
	Vector2 position;

	void InitializePointer();
	void SetPointerPosition(int which);

	int currentSelection;

	Animation pointer;
	std::vector<Text*> text;
};