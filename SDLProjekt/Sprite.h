#pragma once
#include "Vector2.h"
#include <SDL.h>
#include <SDL_image.h>
#include "FrameAnimation.h"
#include "Transformable.h"
#include <cmath>

class Sprite: public Transformable
{
	Frame frame;
public:
	Sprite();
	~Sprite();
	void setTexture(SDL_Texture* texture);
	SDL_Texture* getTexture() const;

	void setFrame(Frame frame);
	Frame getFrame() const;


	Vector2f getLocalSize() const;
	Vector2f getGlobalSize() const;

	void draw(SDL_Renderer* renderer) const;
};
