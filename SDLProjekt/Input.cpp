#include "Input.h"

bool Input::init = true;
Uint8 Input::lastKeyStates[SDL_NUM_SCANCODES];
const Uint8* Input::currentKeyStates;
int Input::size;
Vector2i Input::mousePos;
Uint32 Input::currentMouseState;
Uint32 Input::lastMouseState;


Input::Input()
{
}


Input::~Input()
{
}

void Input::updateStates()
{
	if(init)
	{
		currentKeyStates = SDL_GetKeyboardState(&size);
		currentMouseState = SDL_GetMouseState(NULL, NULL);
		init = false;
	}
	for(int i = 0; i < size; i++)
	{
		lastKeyStates[i] = currentKeyStates[i];
	}
	lastMouseState = currentMouseState;
	currentMouseState = SDL_GetMouseState(&mousePos.x, &mousePos.y);
}

KeyState Input::getKey(const SDL_Scancode code)
{
	return KeyState(
		lastKeyStates[code] == false && currentKeyStates[code] == true,
		lastKeyStates[code] == true && currentKeyStates[code] == false,
		lastKeyStates[code] == true && currentKeyStates[code] == true);
}

Vector2i Input::getMousePos()
{
	return mousePos;
}

KeyState Input::getMouse(int X)
{
	return KeyState(
		(lastMouseState&SDL_BUTTON(X)) == false && (currentMouseState&SDL_BUTTON(X)) == true,
		(lastMouseState&SDL_BUTTON(X)) == true && (currentMouseState&SDL_BUTTON(X)) == false,
		(lastMouseState&SDL_BUTTON(X)) == true && (currentMouseState&SDL_BUTTON(X)) == true);
}
