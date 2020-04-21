#pragma once
#include "Transformable.h"
#include "Sprite.h"
#include "Color.h"
#include "MyRect.h"

class Rectangle: public Transformable
{
	Color fillColor;
	Vector2i size;
public:
	MyRect getBounds();
	void setColor(Color color);
	Color getColor();
	void setSize(const Vector2i size);
	void setSize(int x, int y);
	void draw(SDL_Renderer* renderer);
	Rectangle();
	~Rectangle();
};

