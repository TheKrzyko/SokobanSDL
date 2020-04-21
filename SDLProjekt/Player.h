#pragma once
#include "Vector2.h"
#include <SDL.h>
#include "Animator.h"
#include "Sprite.h"
#include "BoardObject.h"

extern class Game;

class Player: public BoardObject
{
	Game* game;
	
public:
	Animator animator;
	Player();
	~Player();
	void init();
	void draw(SDL_Renderer* renderer);
};