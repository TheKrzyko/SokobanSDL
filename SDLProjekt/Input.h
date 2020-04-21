#pragma once
#include <SDL.h>
#include "Vector2.h"


class KeyState
{
	bool clickedDown;
	bool clickedUp;
	bool pressed;
public:
	bool isClickedDown() const { return clickedDown; }
	bool isClickedUp() const { return clickedUp; }
	bool isPressed() const { return pressed; }
	KeyState(bool clickDown, bool clickUp, bool press) { clickedDown = clickDown; clickedUp = clickUp; pressed = press; }
};

class Input
{
	static Uint8 lastKeyStates[SDL_NUM_SCANCODES];
	static const Uint8* currentKeyStates;
	static Vector2i mousePos;
	static Uint32 lastMouseState;
	static Uint32 currentMouseState;
	static bool init;
	static int size;
	Input();
	~Input();
public:

	static void updateStates();
	static KeyState getKey(const SDL_Scancode code);
	static Vector2i getMousePos();
	static KeyState getMouse(int X);

};
