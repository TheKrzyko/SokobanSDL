#pragma once
#include <SDL.h>
#include "Vector2.h"
#include "Resources.h"
#include "FrameAnimation.h"
#include "Sprite.h"
#include "Player.h"
#include "String.h"
#include "Text.h"
#include "Board.h"
#include "Rectangle.h"
#include "Menu.h"

using namespace std;

enum GameState
{
	menuView,
	gameView
};

class Game
{	
	SDL_Window* window;
	SDL_Renderer* renderer;
	double frameTime;
	String title;
	bool isRunning = true;

	const double moveTime = 0.2;//as seconds
	Clock moveClock;
	Menu menu;

	bool loadRes();
	void handleEvents();
	void handleInput();
	void render();
	bool loadBoard(String boardPath);

	void reactOnPlayerMove(Vector2i move);
	void updatePlayerMove();
	BoardObject* movingBox;
	Vector2i moveVector;

	Text text;
	
	Board board;
	Player player;
	Clock frameClock;
	Clock gameTime;
	Vector2f screenSize;
	Vector2f screenCenter;
public:

	Game();
	~Game();
	bool init(Vector2f screenSize, String title);
	void run();

	static Game& getInstance();

	Resources<SDL_Texture> textures;
	Resources<SDL_Surface> surfaces;
	GameState state = menuView;

	SDL_Surface* tryLoadSurface(String path) const;
	SDL_Texture* tryLoadTexture(String path) const;
	void showError(String title, String message) const;
	void showInfo(String title, String message) const;

	double getFrameTime() const;
	SDL_Window* getWindow() const;
	SDL_Renderer* getRenderer() const;

	friend class Menu;
};
