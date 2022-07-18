#include "timer.h"


Timer::Timer() : count(0),lastFPS(0), delta(0.0f)
{
    start = std::chrono::high_resolution_clock::now();
}

void Timer::Init()
{
}

void Timer::Tick()
{
    auto currentFrame = std::chrono::high_resolution_clock::now();
    delta = std::chrono::duration<float, std::milli>(currentFrame - end).count() / 1000.0f;
    end = currentFrame;
    if (std::chrono::duration_cast<std::chrono::seconds>(currentFrame - start) >= std::chrono::seconds{ 1 })
    {
        start = std::chrono::high_resolution_clock::now();
        lastFPS = count;
        count = 0;
    }
    count++;
}

uint Timer::GetFPS() const
{
	return lastFPS;
}

float Timer::GetDeltaTime() const
{
    return delta;
}
