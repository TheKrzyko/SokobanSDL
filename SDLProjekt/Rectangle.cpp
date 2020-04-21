#include "Rectangle.h"


MyRect Rectangle::getBounds()
{
	return MyRect((int)floor(position.x - origin.x*abs(scale.x)*size.x), (int)floor(position.y - origin.y*abs(scale.y)*size.y), (int)ceil(size.x*abs(scale.x)), (int)ceil(size.y*abs(scale.y)));
}

void Rectangle::setColor(Color color)
{
	this->fillColor = color;
}

Color Rectangle::getColor()
{
	return fillColor;
}

void Rectangle::setSize(const Vector2i size)
{
	this->size = size;
}

void Rectangle::setSize(int x, int y)
{
	setSize(Vector2i(x, y));
}

void Rectangle::draw(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, fillColor.r, fillColor.g, fillColor.b, fillColor.a);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_Rect rect = getBounds();
	SDL_RenderFillRect(renderer, &rect);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
}

Rectangle::Rectangle()
{
}


Rectangle::~Rectangle()
{
}
