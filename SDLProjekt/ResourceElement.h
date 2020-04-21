#pragma once
#include "SDL.h"
#include "String.h"

template <typename T>
struct delHelper
{
	static void free(T* t) { delete t; }
};

template <>
struct delHelper<SDL_Surface>
{
	static void free(SDL_Surface* s)
	{
		SDL_FreeSurface(s);
	}
};

template <>
struct delHelper<SDL_Texture>
{
	static void free(SDL_Texture* t)
	{
		SDL_DestroyTexture(t);
	}
};

template <typename T>
struct ResourceElement
{
	~ResourceElement()
	{
		delHelper<T>::free(value);
	}

	String name;
	T* value;
	ResourceElement* prev = nullptr;
	ResourceElement* next = nullptr;
};
