#pragma once
#include <SDL.h>
#include "Vector2.h"
#include "Clock.h"
#include "Vector.h"

enum AnimationState
{
	stopped,
	started,
	paused
};

struct Frame
{
	SDL_Texture* texture;
	SDL_Rect rect = {0, 0, 0, 0};
};

class FrameAnimation
{
	Vector<Frame> frames;
	SDL_Rect baseSize = {0, 0, 0, 0};
	int frame = 0;
	bool once = false;
	double fps = 1;
	AnimationState state = stopped;
	Clock timer;
public:
	FrameAnimation();
	FrameAnimation(Frame frame);
	FrameAnimation(const FrameAnimation& anim);
	~FrameAnimation();

	void setFps(double fps);
	void setFrames(SDL_Texture* texture, SDL_Rect rects[], int size);
	void setFrames(SDL_Texture* texture, SDL_Rect frameRect, Vector2i firstFrame, Vector2i lastFrame, SDL_Rect baseSize = {0,0,0,0});
	void addFrame(Frame frame);
	Frame getCurrentFrame();
	AnimationState getState() const;

	void play();
	void playOnce();
	void stop();
	void pause();
	void restart();
};
