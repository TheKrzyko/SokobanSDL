#include "Clock.h"
#include <SDL.h>

Clock::Clock()
{
	lastTick = 0;
	pausedTick = 0;
}


Clock::~Clock()
{
}

void Clock::restart()
{
	pausedTick = 0;
	lastTick = SDL_GetTicks();
}

void Clock::pause()
{
	if (!isPaused())
		pausedTick = SDL_GetTicks();
}

void Clock::resume()
{
	if (isPaused())
	{
		lastTick += (SDL_GetTicks() - pausedTick);
		pausedTick = 0;
	}
}

void Clock::stop()
{
	lastTick = 0;
	pausedTick = 0;
}

bool Clock::isPaused() const
{
	return (pausedTick != 0);
}

double Clock::getTimeAsSec() const
{
	return getTimeAsMs() / 1000.0;
}

long long Clock::getTimeAsMs() const
{
	if (pausedTick == 0 && lastTick == 0)
		return 0;
	if (pausedTick != 0)
		return (pausedTick - lastTick);

	return (SDL_GetTicks() - lastTick);
}

void Clock::setTimeAsSec(double time)
{
	lastTick = SDL_GetTicks() - time * 10000;
	//long long current = SDL_GetTicks();
	pausedTick = 0;
}
