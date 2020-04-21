#pragma once
#include "FrameAnimation.h"
#include "Resources.h"
#include "String.h"

class Animator
{

	Resources<FrameAnimation> animations;
	String currentState;
public:
	Animator();
	~Animator();

	void addState(String name, const FrameAnimation& anim);
	//void addTransition(char* from, char* to, FrameAnimation anim, bool isBreakable);
	void setState(String name);
	//void gotoState(char* name);

	Frame getCurrentFrame();
};
