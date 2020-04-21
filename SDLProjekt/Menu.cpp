#include "Menu.h"
#include "Game.h"
#include "Input.h"

void Menu::addBoardInput(Game* game)
{

}

void Menu::chooseViewInput(Game* game)
{
	Vector2i mousePos = Input::getMousePos();

	for(int i = 0; i < boards.getSize(); i++)
	{
		if(boards[i].getBounds().contain(mousePos))
		{
			boards[i].setRotation(5);
			if(Input::getMouse(SDL_BUTTON_LEFT).isClickedDown())
			{
				state = MenuView;
				game->state = gameView;
				game->loadBoard("levels/"+boards[i].getPath());
				game->board.setPath(boards[i].getPath());
				Vector2f scale(1, 1);
				if(game->board.getBounds().w > game->screenSize.x || game->board.getBounds().h > game->screenSize.y)
				{
					scale.x = game->screenSize.x / game->board.getBounds().w;
					scale.y = game->screenSize.y / game->board.getBounds().h;
					if (scale.x < scale.y)
						scale.y = scale.x;
					else
						scale.x = scale.y;
				}
				game->board.setScale(scale);
				game->player.setScale(scale);
				game->player.applyBoardPosition(game->board);
				game->gameTime.restart();
				break;
			}
		}
		else
			boards[i].setRotation(0);
	}
}

void Menu::menuViewInput(Game* game)
{
	Vector2i mousePos = Input::getMousePos();

	if (exitButton.background.getBounds().contain(mousePos))
	{
		exitButton.setBackgroundColor(buttonHoverColor);
		if (Input::getMouse(SDL_BUTTON_LEFT).isClickedDown())
			game->isRunning = false;
	}
	else
		exitButton.setBackgroundColor(buttonColor);

	if (boardsButton.background.getBounds().contain(mousePos))
	{
		boardsButton.setBackgroundColor(buttonHoverColor);
		if (Input::getMouse(SDL_BUTTON_LEFT).isClickedDown())
		{
			state = ChooseView;
			loadBoards(game);
		}
	}
	else
		boardsButton.setBackgroundColor(buttonColor);

	if (addBoardButton.background.getBounds().contain(mousePos))
	{
		addBoardButton.setBackgroundColor(buttonHoverColor);
		if (Input::getMouse(SDL_BUTTON_LEFT).isClickedDown())
		{
			state = AddBoardView;
			SDL_StartTextInput();
		}
	}
	else
		addBoardButton.setBackgroundColor(buttonColor);
}

void Menu::loadBoards(Game* game)
{
	FILE* levelsCfg = fopen("levels.cfg", "r");
	if(levelsCfg != nullptr)
	{
		int size;
		fscanf(levelsCfg, "%i\n", &size);
		boards.clear();
		boards.setSize(size);
		for(int i = 0; i < size; i++)
		{
			char boardPath[50];
			fscanf(levelsCfg, "%s\n", boardPath);
			FILE* boardF = fopen(String("levels/")+String(boardPath), "r");
			if(boardF != nullptr)
			{
				boards[i].setGame(game);
				boards[i].loadFromFile(boardF);
				boards[i].setPath(boardPath);
				Vector2f scale = Vector2f((float)boardSizePx.x / boards[i].getBounds().w, (float)boardSizePx.y / boards[i].getBounds().h);
				boards[i].setScale(scale);
				int col = 50 * (i + 1) + i*boardSizePx.x + boardSizePx.x / 2;
				int row = 50 * (1 + col / 1250) + boardSizePx.y*(col / 1250) + boardSizePx.x / 2;
				col %= 1250;
				boards[i].setPosition(col, row + 80);
				fclose(boardF);
			}
		}
		fclose(levelsCfg);
	}
}

void Menu::prepareButton(Text& text, Game* game)
{
	text.setCharset(game->surfaces["charset"], Vector2i(8, 8), Vector2i(128, 128));
	text.setScale(buttonScale);
	text.setOffset(buttonOffset);
	text.setBackgroundColor(buttonColor);
	text.setColor(Color(0, 0, 0));
}

Menu::Menu()
{
	backgroundColor = Color(40, 80, 192);
	buttonColor = Color(40, 192, 40);
	buttonHoverColor = Color(20, 142, 20);
}


Menu::~Menu()
{
}

void Menu::init(Game* game)
{
	prepareButton(exitButton, game);
	exitButton.setString("Wyjscie", game->renderer);
	exitButton.setPosition(game->screenCenter.x, game->screenSize.y - 200);
	prepareButton(boardsButton, game);
	boardsButton.setString("Wybierz plansze", game->renderer);
	boardsButton.setPosition(game->screenCenter.x, 200);
	prepareButton(addBoardButton, game);
	addBoardButton.setString("Dodaj wlasna plansze", game->renderer);
	addBoardButton.setPosition(game->screenCenter.x, game->screenCenter.y);

	chooseBoardHeader.setCharset(game->surfaces["charset"], Vector2i(8, 8), Vector2i(128, 128));
	chooseBoardHeader.setString("Wybierz plansze:", game->renderer);
	chooseBoardHeader.setScale(4, 4);
	chooseBoardHeader.setPosition(game->screenCenter.x, 50);

	addBoardHeader.setCharset(game->surfaces["charset"], Vector2i(8, 8), Vector2i(128, 128));
	addBoardHeader.setString("Wpisz nazwe planszy:", game->renderer);
	addBoardHeader.setScale(4, 4);
	addBoardHeader.setPosition(game->screenCenter.x, game->screenCenter.y-50);
	addBoardPath.setCharset(game->surfaces["charset"], Vector2i(8, 8), Vector2i(128, 128));
	addBoardPath.setScale(4, 4);
	addBoardPath.setString("", game->renderer);
	addBoardPath.setPosition(game->screenCenter.x, game->screenCenter.y);

}

void Menu::update(Game* game)
{
	SDL_Event ev;
	while (SDL_PollEvent(&ev))
	{
		if (ev.type == SDL_QUIT)
		{
			game->isRunning = false;
		}
		if(state == AddBoardView && ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_RETURN)
		{
			
			SDL_StopTextInput();
			FILE* cfgw = fopen("levels.cfg", "r");
			if(cfgw != nullptr)
			{
				int size;
				fscanf(cfgw, "%i\n", &size);
				String* boards = new String[size];
				for(int i = 0; i < size; i++)
				{
					char str[50];
					fscanf(cfgw, "%s\n", str);
					boards[i] = str;
				}
				fclose(cfgw);
				FILE* cfgr = fopen("levels.cfg", "w");
				if(cfgr != nullptr)
				{
					size++;
					fprintf(cfgw, "%i\n", size);
					for(int i = 0; i < size - 1; i++)
					{
						fprintf(cfgw, "%s\n", boards[i].getCstr());
					}
					fprintf(cfgw, "%s\n", newBoardPath.getCstr());
				}
			}


			state = MenuView;
			loadBoards(game);
			newBoardPath = "";
		}
		if(ev.type == SDL_TEXTINPUT)
		{
			
			newBoardPath += ev.text.text;
			addBoardPath.setString(newBoardPath, game->renderer);
		}
	}

	if (Input::getKey(SDL_SCANCODE_ESCAPE).isClickedDown())
	{
		if (state == MenuView)
			game->isRunning = false;
		else if (state == ChooseView)
			state = MenuView;
		else if (state == AddBoardView)
		{
			state = MenuView;
			addBoardPath.setString("", game->renderer);
			newBoardPath = "";
		}
	}
	if (state == MenuView)
		menuViewInput(game);
	else if (state == ChooseView)
		chooseViewInput(game);
	else if (state == AddBoardView)
		addBoardInput(game);
	
}

void Menu::render(SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
	SDL_RenderClear(renderer);
	if (state == MenuView)
	{
		exitButton.draw(renderer);
		boardsButton.draw(renderer);
		addBoardButton.draw(renderer);
	}
	else if(state == ChooseView)
	{
		for(int i = 0; i < boards.getSize(); i++)
		{
			boards[i].draw(renderer);
		}
		chooseBoardHeader.draw(renderer);
	}
	else if(state == AddBoardView)
	{
		addBoardHeader.draw(renderer);
		addBoardPath.draw(renderer);
	}
	SDL_RenderPresent(renderer);
}
