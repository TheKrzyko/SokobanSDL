#include "BoardObject.h"
#include "Board.h"

void BoardObject::applyBoardPosition(const Board& board)
{
	setPosition(board.convertBoardPos(boardPosition));
}
