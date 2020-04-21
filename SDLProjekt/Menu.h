#pragma once
#include <SDL.h>
#include "Color.h"
#include "Rectangle.h"
#include "Text.h"
#include "Board.h"

class Game;

class Menu
{
	Color backgroundColor;
	Color buttonColor;
	Color buttonHoverColor;
	Vector2f buttonScale = Vector2f(4, 4);
	int buttonOffset = 20;
	Text exitButton;
	Text boardsButton;
	Text addBoardButton;
	Text chooseBoardHeader;
	Text addBoardHeader;
	Text addBoardPath;
	String newBoardPath;
	Vector<Board> boards;
	Vector2i boardSizePx = Vector2i(200, 200);

	void addBoardInput(Game* game);
	void chooseViewInput(Game* game);
	void menuViewInput(Game* game);
	void loadBoards(Game* game);
	void prepareButton(Text& text, Game* game);
public:
	Menu();
	~Menu();
	void init(Game* game);
	void update(Game* game);
	void render(SDL_Renderer* renderer);
	enum MenuState
	{
		MenuView,
		ChooseView,
		AddBoardView
	};
	MenuState state = MenuView;
};

