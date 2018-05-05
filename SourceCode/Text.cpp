#include "Text.h"
#include "SDLFramework.h"


Text::Text()
{
}

Text::~Text()
{
}

void Text::SetText(int fontIndex, string _text, SDL_Color * color)
{
	Name = _text;
	font = SDLFramework::Instance()->GetFont(fontIndex);
	SDL_Renderer* renderer = SDLFramework::Instance()->GetRenderer();
	texture = SDLFramework::LoadTextureFromFont(font, _text, color);
	SDL_QueryTexture(texture, NULL, NULL,
		&(textureWidth), &(textureHeight));
}
