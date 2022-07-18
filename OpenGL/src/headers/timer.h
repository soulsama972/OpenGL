#pragma once
#include"typing.h"
#include <chrono>



class Timer
{
public:
	Timer();
	void Init();
	void Tick();
	uint GetFPS() const;
	float GetDeltaTime() const;
private:
	uint count, lastFPS;
	float delta;
	std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
};
