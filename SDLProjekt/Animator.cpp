#include "Animator.h"
#include <string.h>
Animator::Animator()
{
}

Animator::~Animator()
{
}

void Animator::addState(String name, const FrameAnimation& anim)
{
	animations[name] = new FrameAnimation(anim);
}

void Animator::setState(String name)
{
	if (currentState == name)
		return;
	if(currentState != String(""))
		animations[currentState]->stop();
	currentState = name;
	animations[currentState]->play();
}

Frame Animator::getCurrentFrame()
{
	return animations[currentState]->getCurrentFrame();
}
