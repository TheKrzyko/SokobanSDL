#pragma once
class Clock
{
	long long lastTick;
	long long pausedTick;
public:
	Clock();
	~Clock();

	void restart();
	void pause();
	void resume();
	void stop();

	bool isPaused() const;

	double getTimeAsSec() const;
	long long getTimeAsMs() const;
	void setTimeAsSec(double time);
};
