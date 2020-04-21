#include "Board.h"
#include "conio.h"
#include "Game.h"


Board::Board(Game* game)
{
	this->game = game;
	board = nullptr;
	buffor = nullptr;
}

Board::Board()
{
	board = nullptr;
	buffor = nullptr;
}

void Board::setGame(Game* game)
{
	this->game = game;
}


void Board::addBox(Vector2i pos)
{
	BoardObject box;
	box.setTexture(game->textures[cratePath]);
	box.boardPosition = pos;
	box.setPosition(convertBoardPosLocal(pos));
	
	boxes.pushBack(box);
}

void Board::addEndPoint(Vector2i pos)
{
	BoardObject endpoint;
	endpoint.setTexture(game->textures[endPointPath]);
	endpoint.boardPosition = pos;
	endpoint.setPosition(convertBoardPosLocal(pos));

	endPoints.pushBack(endpoint);
}

void Board::updateBoxTexture()
{
	for(int i = 0; i < boxes.getSize(); i++)
	{
		for(int j = 0; j < endPoints.getSize(); j++)
		{
			if (boxes[i].boardPosition == endPoints[j].boardPosition)
				boxes[i].setTexture(game->textures[crateCompletePath]);
		}
	}
}

void Board::destroyBoard()
{
	if(board != nullptr)
	{
		for (int i = 0; i < boardSize.y; i++)
			delete[] board[i];
		delete[] board;
	}
}

void Board::createBoard(Vector2i size)
{
	if (board != nullptr)
		destroyBoard();
	boardSize = size;
	board = new char*[size.y];
	for(int i = 0; i < size.y; i++)
		board[i] = new char[size.x];
	
}

String Board::getPath() const
{
	return path;
}

void Board::setPath(String path)
{
	this->path = path;
}

bool Board::loadFromFile(FILE* file)
{
	if (file == nullptr)
		return false;
	if (buffor != nullptr)
		SDL_DestroyTexture(buffor);
	Vector2i size;
	fscanf(file, "(%i,%i)\n", &size.x, &size.y);
	createBoard(size);
	buffor = SDL_CreateTexture(game->getRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, boxSize*boardSize.x, boxSize*boardSize.y);

	for(int y = 0; y < boardSize.y; y++)
	{
		for(int x = 0; x < boardSize.x; x++)
		{
			board[y][x] = fgetc(file);
		}
		fgetc(file);
	}
	int boxesSize;
	fscanf(file, "%i\n", &boxesSize);
	boxes.clear();
	endPoints.clear();
	for(int i = 0; i < boxesSize; i++)
	{
		Vector2i pos;
		fscanf(file, "(%i,%i)", &pos.x, &pos.y);
		addBox(pos);
	}
	fscanf(file, "\n");
	for (int i = 0; i < boxesSize; i++)
	{
		Vector2i pos;
		fscanf(file, "(%i,%i)", &pos.x, &pos.y);
		addEndPoint(pos);
	}
	fscanf(file, "\n");
	updateBoxTexture();
}

Vector2f Board::getLeftTopCorner() const
{
	return Vector2f(position.x - origin.x*boxSize*boardSize.x*scale.x, position.y - origin.y*boxSize*boardSize.y*scale.y);
}

bool Board::isWall(int x, int y)
{
	return isWall(Vector2i(x, y));
}

bool Board::isWall(Vector2i pos)
{
	if(board[pos.y][pos.x] == wallChar)
	{
		return true;
	}
	return false;
}

BoardObject* Board::isBox(int x, int y)
{
	return isBox(Vector2i(x, y));
}

BoardObject* Board::isBox(Vector2i pos)
{
	for(int i = 0; i < boxes.getSize(); i++)
	{
		if (boxes[i].boardPosition == pos)
			return &boxes[i];
	}
	return nullptr;
}

bool Board::isEmpty(int x, int y)
{
	return isEmpty(Vector2i(x, y));
}

bool Board::isEmpty(Vector2i pos)
{
	return isBox(pos) == nullptr && isWall(pos) == false;
}

bool Board::isEndPoint(Vector2i pos)
{
	for(int i = 0; i < endPoints.getSize(); i++)
	{
		if (endPoints[i].boardPosition == pos)
			return true;
	}
	return false;
}

bool Board::isGameCompleted()
{
	for(int i = 0; i < boxes.getSize(); i++)
	{
		bool boxCompleted = false;
		for(int j = 0; j < endPoints.getSize(); j++)
		{
			if(boxes[i].boardPosition == endPoints[j].boardPosition)
			{
				boxCompleted = true;
				break;
			}
		}
		if (boxCompleted == false)
			return false;
	}
	return true;
}

MyRect Board::getBounds() const
{
	return MyRect((int)floor(position.x - origin.x*scale.x*boxSize*boardSize.x), (int)floor(position.y - origin.y*scale.y*boxSize*boardSize.y), (int)ceil(scale.x*boxSize*boardSize.x), (int)ceil(scale.y*boxSize*boardSize.y));
}

Vector2f Board::convertBoardPos(const Vector2i pos) const
{
	return Vector2f(pos.x*boxSize*scale.x + boxSize*scale.x / 2 + getLeftTopCorner().x, pos.y*boxSize*scale.y + boxSize*scale.y / 2 + getLeftTopCorner().y);
}

Vector2f Board::convertBoardPosLocal(const Vector2i pos) const
{
	return Vector2f(boxSize*pos.x + boxSize/2, boxSize*pos.y + boxSize/2);
}

void Board::draw(SDL_Renderer* renderer)
{
	SDL_SetRenderTarget(renderer, buffor);
	for(int y = 0; y < boardSize.y; y++)
	{
		for(int x = 0; x < boardSize.x; x++)
		{
			String texPath = (board[y][x] == groundChar ? groundPath : wallPath);

			SDL_Rect dstRect = {
				floor(x*boxSize),
				floor(y*boxSize),
				ceil(boxSize),
				ceil(boxSize)
			};
			SDL_RenderCopy(renderer, game->textures[texPath], NULL, &dstRect);
		}
	}
	for(int i = 0; i < endPoints.getSize(); i++)
	{
		endPoints[i].draw(renderer);
	}
	for (int i = 0; i < boxes.getSize(); i++)
	{
		boxes[i].draw(renderer);
	}
	SDL_SetRenderTarget(renderer, NULL);
	SDL_Rect dstRect = {
		floor(position.x - origin.x*boxSize*boardSize.x*abs(scale.x)),
		floor(position.y - origin.y*boxSize*boardSize.y*abs(scale.y)),
		ceil(boardSize.x*boxSize*abs(scale.x)),
		ceil(boardSize.y*boxSize*abs(scale.y))
	};
	const SDL_RendererFlip flip = static_cast<SDL_RendererFlip>((scale.x >= 0 ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL) | (
		scale.y >= 0 ? SDL_FLIP_NONE : SDL_FLIP_VERTICAL));
	SDL_Point center = { origin.x*dstRect.w, origin.y*dstRect.h };
	SDL_RenderCopyEx(renderer, buffor, NULL, &dstRect, angle, &center, flip);
}

Board::~Board()
{
	destroyBoard();
	if (buffor != nullptr)
		SDL_DestroyTexture(buffor);
}
