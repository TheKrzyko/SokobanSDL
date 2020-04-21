#pragma once
#include "String.h"
#include "Vector2.h"
#include "Resources.h"
#include "Transformable.h"
#include "Vector.h"
#include "Sprite.h"
#include "BoardObject.h"
#include "MyRect.h"

extern class Game;

class Board: public Transformable
{
	Vector2i boardSize;
	char** board;
	Vector<BoardObject> boxes;
	Vector<BoardObject> endPoints;
	String path;
	Game* game;
	SDL_Texture* buffor;

	void addBox(Vector2i pos);
	void addEndPoint(Vector2i pos);
	void updateBoxTexture();
	void destroyBoard();
	void createBoard(Vector2i size);
public:
	char* const groundPath = "ground";
	char* const wallPath = "wall";
	char* const cratePath = "crate";
	char* const crateCompletePath = "crateDark";
	char* const endPointPath = "endpoint";
	char const wallChar = 'w';
	char const groundChar = 'g';
	const int boxSize = 64;

	String getPath() const;
	void setPath(String path);
	bool loadFromFile(FILE* file);
	Vector2f getLeftTopCorner() const;
	bool isWall(int x, int y);
	bool isWall(Vector2i pos);
	BoardObject* isBox(int x, int y);
	BoardObject* isBox(Vector2i pos);
	bool isEmpty(int x, int y);
	bool isEmpty(Vector2i pos);
	bool isEndPoint(Vector2i pos);
	bool isGameCompleted();

	MyRect getBounds() const;

	Vector2f convertBoardPos(const Vector2i pos) const;
	Vector2f convertBoardPosLocal(const Vector2i pos) const;

	void draw(SDL_Renderer* renderer);
	Board(Game* game);
	Board();
	void setGame(Game* game);
	~Board();
};

