#pragma once
#include <SDL.h>
#include "Sprite.h"
#include "String.h"
#include "Color.h"
#include "MyRect.h"
#include "Rectangle.h"

class Text: public Transformable
{
	String string;
	Color color;
	SDL_Surface* charset;
	Vector2i charSize;
	Vector2i charsetSize;
	SDL_Surface* buffor = nullptr;
	SDL_Texture* texture = nullptr;
	int offset = 0;
public:
	Text();
	~Text();
	Rectangle background;

	String getString() const;
	void setString(const String& str, SDL_Renderer* renderer);
	void setCharset(SDL_Surface* charset, Vector2i charSize, Vector2i charsetSize);
	void setColor(Color color);
	void setBackgroundColor(Color color);
	void setOffset(int off);
	Color getColor();
	MyRect getBounds();
	void draw(SDL_Renderer* renderer);
};

