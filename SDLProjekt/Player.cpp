#include "Player.h"
#include "Game.h"


Player::Player()
{
}


Player::~Player()
{
}

void Player::init()
{
	const int fps = 15;
	game = &Game::getInstance();
	animator.addState("DownStand", FrameAnimation({ game->textures["playerDownStand"] }));
	animator.addState("LeftStand", FrameAnimation({ game->textures["playerLeftStand"] }));
	animator.addState("RightStand", FrameAnimation({ game->textures["playerRightStand"] }));
	animator.addState("UpStand", FrameAnimation({ game->textures["playerUpStand"] }));
	FrameAnimation down;
	down.addFrame({ game->textures["playerDown0"] });
	down.addFrame({game->textures["playerDown1"]});
	down.setFps(6);
	FrameAnimation right;
	right.addFrame({ game->textures["playerRightStand"] });
	right.addFrame({ game->textures["playerRight0"] });
	right.setFps(fps);
	FrameAnimation left;
	left.addFrame({ game->textures["playerLeftStand"] });
	left.addFrame({ game->textures["playerLeft0"] });
	left.setFps(fps);
	FrameAnimation up;
	up.addFrame({ game->textures["playerUp0"] });
	up.addFrame({ game->textures["playerUp1"] });
	up.setFps(fps);
	animator.addState("DownMove", down);
	animator.addState("UpMove", up);
	animator.addState("RightMove", right);
	animator.addState("LeftMove", left);
	animator.setState("DownStand");
}

void Player::draw(SDL_Renderer* renderer)
{
	setTexture(animator.getCurrentFrame().texture);
	Sprite::draw(renderer);
}