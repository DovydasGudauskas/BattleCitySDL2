#include <Text.h>
#include <Rendering.h>

Text::Text() :position(Vector2()), enabled(true)
{
	originalText = "";
}

Text::Text(std::string text) :position(Vector2()), enabled(true)
{
	SetText(text);
}

Text::Text(std::string text, bool active) : position(Vector2()), enabled(true)
{
	SetText(text);
	Enable(active);
}

Text::Text(std::string text, Vector2 position) :position(position), enabled(true)
{
	SetText(text);
}

Text::~Text()
{
	ClearText();
}

void Text::SetText(std::string text)
{
	if (originalText == text)
		return;

	originalText = text;

	ClearText();

	Rendering* rendering = Rendering::GetReference();
	
	for (int i = 0; i < text.size(); i++)
	{
		Sprite letterSprite = rendering->GetLetterTexture(text[i]);
		SpriteObject* newLetter = new SpriteObject(letterSprite, layerType::Text);
		newLetter->SetPosition(Vector2(i * 8, 0) + position);
		myLetters.push_back(newLetter);
	}
}

void Text::SetPosition(Vector2 pos)
{
	Vector2 translationPos = pos - position;

	position = pos;

	for (size_t i = 0; i < myLetters.size(); i++)
		myLetters[i]->Translate(translationPos);
}

Vector2 Text::GetPosition()
{
	return position;
}

void Text::Translate(Vector2 pos)
{
	position += pos;

	for (size_t i = 0; i < myLetters.size(); i++)
		myLetters[i]->Translate(pos);
}

void Text::Enable(bool var)
{
	if (enabled == var)
		return;

	enabled = var;

	for (size_t i = 0; i < myLetters.size(); i++)
		myLetters[i]->EnableRendering(enabled);
}

void Text::ClearText()
{
	for (size_t i = 0; i < myLetters.size(); i++)
		delete myLetters[i];

	myLetters.clear();
}

// ******************* PAGE

Page::Page() : currentSelection(0), position(Vector2())
{
	InitializePointer();
	SetPointerTexture(Sprite());
}

Page::Page(std::vector<std::string> btnText) : currentSelection(0), position(Vector2())
{
	InitializePointer();
	SetPointerTexture(Sprite());
	SetText(btnText);
}

Page::Page(std::vector<std::string> btnText, Sprite pointerTexture) : currentSelection(0), position(Vector2())
{
	InitializePointer();
	SetPointerTexture(pointerTexture);
	SetText(btnText);
}

Page::~Page()
{
}

void Page::Enable(bool var)
{
	for (size_t i = 0; i < text.size(); i++)
		text[i]->Enable(var);

	pointer->EnableRendering(var);
}

void Page::GoUp()
{
	if (currentSelection - 1 < 0)
		return;

	SetPointerPosition(currentSelection - 1);
}

void Page::GoDown()
{
	if (currentSelection + 1 >= text.size())
		return;

	SetPointerPosition(currentSelection + 1);
}

void Page::SetPointerPosition(int which)
{
	currentSelection = which;
	
	Vector2 pos = pointer->GetPosition();
	pos.y = text[which]->GetPosition().y;
	pointer->SetPosition(pos);
}

int Page::GetCurrentSelection()
{
	return currentSelection;
}

void Page::SetPointerTexture(Sprite texture)
{
	pointer->SetSprite(texture);
}

void Page::InitializePointer()
{
	pointer = new SpriteObject(Sprite());
	pointer->SetPosition(Vector2(-16, 0));
}

void Page::SetText(std::vector<std::string> btnText)
{
	ClearText();

	for (int i = 0; i < btnText.size(); i++)
	{
		Text* newText = new Text(btnText[i]);
		newText->SetPosition(position + Vector2(0, i * 16));
		text.push_back(newText);
	}
}

void Page::ClearText()
{
	for (size_t i = 0; i < text.size(); i++)
		delete text[i];

	text.clear();
}

void Page::SetPosition(Vector2 pos)
{
	Vector2 translationPos = pos - position;

	position = pos;

	for (size_t i = 0; i < text.size(); i++)
		text[i]->Translate(translationPos);

	pointer->Translate(translationPos);
}

void Page::Translate(Vector2 pos)
{
	position += pos;

	for (size_t i = 0; i < text.size(); i++)
		text[i]->Translate(pos);

	pointer->Translate(pos);
}

Vector2 Page::GetPosition()
{
	return position;
}
