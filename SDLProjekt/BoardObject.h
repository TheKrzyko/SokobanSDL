#pragma once
#include "Sprite.h"

class Board;

class BoardObject: public Sprite
{
public:
	Vector2i boardPosition;
	void applyBoardPosition(const Board& board);
};
