#pragma once
#include <SDL_hints.h>

class Color
{
public:
	Uint8 r;
	Uint8 g;
	Uint8 b;
	Uint8 a;
	Color()
	{
		this->r = 255;
		this->g = 255;
		this->b = 255;
		this->a = 255;
	}
	Color(Uint8 r, Uint8 g, Uint8 b)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = 255;
	}
	Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}
	~Color()
	{
		
	}
};

