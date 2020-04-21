// SDLProjekt.cpp : Defines the entry point for the console application.
//
#include "Game.h"

int main(int argc, char* argv[])
{
	Game& game = Game::getInstance();
	game.init(Vector2f(1280, 720), "Sokoban - Krzysztof Dubanowicz 172029");
	game.run();
	return 0;
}

