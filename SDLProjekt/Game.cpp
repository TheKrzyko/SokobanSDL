#include "Game.h"
#include <SDL.h>
#include <cstring>
#include "Input.h"
#include <iostream>


SDL_Surface* Game::tryLoadSurface(String path) const
{
	SDL_Surface* loaded = IMG_Load(path);
	SDL_Surface* result = nullptr;
	if (loaded == nullptr)
	{
		String message = "Problem with loading image: " + path;
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", message, window);
		loaded = SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, 0);
		SDL_FillRect(result, nullptr, SDL_MapRGB(loaded->format, 255, 0, 255));
	}
	result = SDL_ConvertSurface(loaded, SDL_GetWindowSurface(window)->format, NULL);
	SDL_FreeSurface(loaded);
	return result;
}

SDL_Texture* Game::tryLoadTexture(String path) const
{
	SDL_Surface* surface = IMG_Load(path);
	SDL_Texture* result = nullptr;
	if (surface == nullptr)
	{
		String message = "Problem with loading image: " + path;
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", message, window);
		surface = SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, 0);
		SDL_FillRect(surface, nullptr, SDL_MapRGB(surface->format, 255, 0, 255));
	}
	result = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	return result;
}

void Game::showError(String title, String message) const
{
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title, message, window);
}

void Game::showInfo(String title, String message) const
{
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, title, message, window);
}

double Game::getFrameTime() const
{
	return frameTime;
}


Game::Game()
{
	board.setGame(this);
	title = "Default";
}

Game::~Game()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	renderer = nullptr;
	window = nullptr;
	IMG_Quit();
	SDL_Quit();
}

Game& Game::getInstance()
{
	static Game singleton;
	return singleton;
}

bool Game::init(const Vector2f screenSize, String title)
{
	this->title = title;
	this->screenSize = screenSize;
	screenCenter = screenSize / Vector2f(2,2);
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return false;


	window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenSize.x, screenSize.y, SDL_WINDOW_SHOWN);
	if (window == nullptr)
	{
		return false;	
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
	if (renderer == nullptr)
	{
		showError("Error!,", "Unable to create renderer!");
		return false;
	}
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	const int imgF = IMG_INIT_PNG;
	if (!(IMG_Init(imgF) & imgF))
	{
		showError("Error!", "Unable to initialize SDL_Image!");
		return false;
	}

	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0"))
	{
		showInfo("Info!", "Linear texture filtering not enabled!");
	}
	loadRes();
	player.init();
	menu.init(this);
	board.setPosition(screenCenter.x, screenCenter.y);
	board.setScale(1, 1);
	//board.setRotation(15);
	player.setScale(1, 1);

	frameClock.restart();
	//gameTime.restart();

	text.setCharset(surfaces["charset"], Vector2i(8, 8), Vector2i(128, 128));
	text.setString("Hello World", renderer);
	text.setPosition(screenCenter.x, screenCenter.y);
	text.setScale(5, 5);
	text.setRotation(15);
	text.setColor(Color(255, 0, 0));
	moveClock.setTimeAsSec(moveTime);
	
	Input::updateStates();
	return true;
}

bool Game::loadRes()
{
	surfaces["charset"] = tryLoadSurface("res/cs8x8.bmp");
	textures["playerDownStand"] = tryLoadTexture("res/Character4.png");
	textures["playerDown0"] = tryLoadTexture("res/Character5.png");
	textures["playerDown1"] = tryLoadTexture("res/Character6.png");
	textures["playerUpStand"] = tryLoadTexture("res/Character7.png");
	textures["playerUp0"] = tryLoadTexture("res/Character8.png");
	textures["playerUp1"] = tryLoadTexture("res/Character9.png");
	textures["playerLeftStand"] = tryLoadTexture("res/Character1.png");
	textures["playerLeft0"] = tryLoadTexture("res/Character10.png");
	textures["playerRightStand"] = tryLoadTexture("res/Character2.png");
	textures["playerRight0"] = tryLoadTexture("res/Character3.png");
	textures["wall"] = tryLoadTexture("res/Wall_Brown.png");
	textures["ground"] = tryLoadTexture("res/Ground_Grass.png");
	textures["crate"] = tryLoadTexture("res/Crate_Yellow.png");
	textures["crateDark"] = tryLoadTexture("res/CrateDark_Yellow.png");
	textures["endpoint"] = tryLoadTexture("res/EndPoint_Yellow.png");
	//SDL_SetTextureAlphaMod(textures["endpoint"], 200);
	return true;
}

void Game::run()
{
	while (isRunning)
	{
		frameTime = frameClock.getTimeAsSec();
		frameClock.restart();
		if (state == gameView)
		{
			handleEvents();
			updatePlayerMove();
			handleInput();
			text.rotate(1);
			//board.rotate(1);
		}
		else
		{
			menu.update(this);
		}
		Input::updateStates();		
		if (state == gameView)
			render();
		else
			menu.render(renderer);
	}
}

void Game::handleEvents()
{
	SDL_Event ev;
	while (SDL_PollEvent(&ev))
	{
		if (ev.type == SDL_QUIT)
		{
			isRunning = false;
		}
	}
}

void Game::handleInput()
{
	if(Input::getKey(SDL_SCANCODE_ESCAPE).isClickedDown())
	{
		state = menuView;
	}
	if(Input::getKey(SDL_SCANCODE_N).isClickedDown())
	{
		loadBoard("levels/"+board.getPath());
		gameTime.restart();
		moveVector = Vector2i(0, 0);
		moveClock.setTimeAsSec(moveTime + 1);
		player.animator.setState("DownStand");
		movingBox = nullptr;
	}
	
	if (Input::getKey(SDL_SCANCODE_RIGHT).isPressed())
	{
		reactOnPlayerMove(Vector2i(1, 0));
	}
	else if (Input::getKey(SDL_SCANCODE_LEFT).isPressed())
	{
		reactOnPlayerMove(Vector2i(-1, 0));
	}
	else if (Input::getKey(SDL_SCANCODE_UP).isPressed())
	{
		reactOnPlayerMove(Vector2i(0, -1));
	}
	else if (Input::getKey(SDL_SCANCODE_DOWN).isPressed())
	{
		reactOnPlayerMove(Vector2i(0, 1));
	}
}

void Game::render()
{
	SDL_RenderClear(renderer);
	text.setString(toString((int)gameTime.getTimeAsSec())+"s", renderer);
	
	board.draw(renderer);
	player.draw(renderer);
	text.draw(renderer);
	SDL_RenderPresent(renderer);
}

bool Game::loadBoard(String boardPath)
{
	FILE* file = fopen(boardPath, "r");
	if (file != nullptr)
	{
		board.loadFromFile(file);
		fscanf(file, "(%i,%i)", &player.boardPosition.x, &player.boardPosition.y);
		player.applyBoardPosition(board);
		fclose(file);
		return true;
	}
	return false;
}
String getAnimation(Vector2i vec)
{
	if (vec == Vector2i(1, 0))
		return "Right";
	if (vec == Vector2i(-1, 0))
		return "Left";
	if (vec == Vector2i(0, 1))
		return "Down";
	if (vec == Vector2i(0, -1))
		return "Up";
	return "";
}
void Game::reactOnPlayerMove(Vector2i move)
{
	if (moveClock.getTimeAsSec() <= moveTime || moveVector != Vector2i(0,0))
		return;
	BoardObject* box = nullptr;
	Vector2i nextPos = player.boardPosition + move;
	if ((box = board.isBox(nextPos)) != nullptr && board.isEmpty(nextPos + move))
	{
		moveVector = move;
		moveClock.restart();
		movingBox = box;
		player.animator.setState(String(getAnimation(moveVector) + "Move"));
	}
	else if (board.isEmpty(nextPos))
	{
		moveClock.restart();
		moveVector = move;
		player.animator.setState(String(getAnimation(moveVector) + "Move"));
	}
}

void Game::updatePlayerMove()
{
	if (moveClock.getTimeAsSec() <= moveTime || moveVector != Vector2i(0, 0))
	{
		Vector2f pos = Vector2f::lerp(board.convertBoardPos(player.boardPosition), board.convertBoardPos(player.boardPosition + moveVector), moveClock.getTimeAsSec() / moveTime);
		player.setPosition(pos);
		if (movingBox != nullptr)
			movingBox->setPosition(Vector2f::lerp(board.convertBoardPosLocal(movingBox->boardPosition), board.convertBoardPosLocal(movingBox->boardPosition + moveVector), moveClock.getTimeAsSec() / moveTime));
		if(pos == board.convertBoardPos(player.boardPosition+moveVector))
		{
			player.boardPosition += moveVector;
			if(movingBox != nullptr)
			{
				movingBox->boardPosition += moveVector;
				if (board.isEndPoint(movingBox->boardPosition))
				{
					movingBox->setTexture(textures[board.crateCompletePath]);
					if (board.isGameCompleted())
					{
						gameTime.pause();
						showInfo("Gratulacje!", "Wygrales! Osiagajac czas: " + toString(gameTime.getTimeAsSec()) + "s.");
						state = menuView;
						menu.state = Menu::ChooseView;
					}
				}
				else 
					movingBox->setTexture(textures[board.cratePath]);
				
			}
			player.animator.setState(String(getAnimation(moveVector)+"Stand"));
			movingBox = nullptr;
			moveVector = Vector2i(0, 0);
			
		}
		
	}
	else
		movingBox = nullptr;
}

SDL_Window* Game::getWindow() const
{
	return window;
}

SDL_Renderer* Game::getRenderer() const
{
	return renderer;
}

