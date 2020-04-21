#include "FrameAnimation.h"
#include <SDL.h>

FrameAnimation::FrameAnimation()
{
}

FrameAnimation::FrameAnimation(Frame frame)
{
	addFrame(frame);
}

FrameAnimation::FrameAnimation(const FrameAnimation& anim)
{
	baseSize = anim.baseSize;
	timer = anim.timer;
	state = anim.state;
	frame = anim.frame;
	fps = anim.fps;
	once = anim.once;
	frames = anim.frames;
}

FrameAnimation::~FrameAnimation()
{
}

void FrameAnimation::setFps(const double fps)
{
	this->fps = fps;
}

void FrameAnimation::setFrames(SDL_Texture* texture, SDL_Rect rects[], const int size)
{
	for(int i = 0; i < size; i++)
	{
		addFrame({ texture, rects[i] });
	}
}

///
//Frames are numbered from 0
void FrameAnimation::setFrames(SDL_Texture* texture, const SDL_Rect frameRect, const Vector2i firstFrame, const Vector2i lastFrame, SDL_Rect baseSize)
{
	this->baseSize = baseSize;
	if (baseSize.h == 0 && baseSize.w == 0 && baseSize.x == 0 && baseSize.y == 0)
	{
		SDL_QueryTexture(texture, nullptr, nullptr, &baseSize.w, &baseSize.h);
	}
	const int columns = baseSize.w / frameRect.w;
	int size = ((lastFrame.y - firstFrame.y) * columns) - firstFrame.x + lastFrame.x + 1;
	for (int i = 0; i < size; i++)
	{
		SDL_Rect rect;
		rect.w = frameRect.w;
		rect.h = frameRect.h;
		rect.x = baseSize.x + ((frameRect.w * (firstFrame.x + i)) % baseSize.w);
		rect.y = baseSize.y + (frameRect.h * (firstFrame.y + ((firstFrame.x + i) / columns)));
		frames.pushBack({ texture, rect });
	}
}

void FrameAnimation::addFrame(Frame frame)
{
	if(frame.rect.w == 0 && frame.rect.h == 0)
		SDL_QueryTexture(frame.texture, nullptr, nullptr, &frame.rect.w, &frame.rect.h);
	frames.pushBack(frame);
}

Frame FrameAnimation::getCurrentFrame()
{
	if (timer.getTimeAsSec() > (1 / fps))
	{
		frame = ++frame % frames.getSize();
		if (once == true && frame + 1 == frames.getSize())
		{
			pause();
			once = false;
		}
		timer.restart();
	}

	return frames[frame];
}

AnimationState FrameAnimation::getState() const
{
	return state;
}

void FrameAnimation::play()
{
	state = started;
	timer.restart();
	frame = 0;
}

void FrameAnimation::playOnce()
{
	state = started;
	frame = 0;
	timer.restart();
	once = true;
}

void FrameAnimation::stop()
{
	state = stopped;
	timer.stop();
	frame = 0;
	once = false;
}

void FrameAnimation::pause()
{
	timer.pause();
	state = paused;
}

void FrameAnimation::restart()
{
	timer.restart();
	state = started;
	frame = 0;
	once = false;
}
