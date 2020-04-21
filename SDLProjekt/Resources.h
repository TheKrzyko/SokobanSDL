#pragma once
#include "ResourceElement.h"
#include <cstring>
#include <SDL_image.h>

extern class Game;

template <typename T>
class Resources
{
	
public:
	ResourceElement<T>* first = nullptr;
	ResourceElement<T>* last = nullptr;

	Resources() 
	{
		
	}

	~Resources()
	{
		ResourceElement<T>* current = first;
		ResourceElement<T>* next;
		while (current)
		{
			next = current->next;
			delete current;
			current = next;
		}
	}

	T*& operator[](const String& str)
	{
		if (first == nullptr)
		{
			first = new ResourceElement<T>();
			first->name = str;
			last = first;
			return first->value;
		}
		//Search for existing resource
		ResourceElement<T>* current = first;
		while (current)
		{
			if (str == current->name)
				return current->value;
			current = current->next;
		}
		//Add resource
		current = new ResourceElement<T>();
		current->name = str;
		current->prev = last;
		last->next = current;
		last = current;
		return current->value;
	}
	
};

