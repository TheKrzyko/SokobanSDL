#pragma once
#include "Vector.h"
#include "Vector2.h"
#include <SDL.h>

class MyRect
{
public:
	int x, y, w, h;
	MyRect()
	{	
	}
	MyRect(int x, int y, int w, int h)
	{
		this->x = x;
		this->y = y;
		this->w = w;
		this->h = h;
	}
	bool contain(const Vector2i& point) const
	{
		return point.x >= x && point.x <= x + w && point.y >= y && point.y <= y + h;
	}
	operator SDL_Rect() const
	{
		return { x, y, w, h };
	}
	~MyRect()
	{
	}
};
