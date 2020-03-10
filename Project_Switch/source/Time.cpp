#include "Time.h"

Uint64 Time::NOW;
Uint64 Time::LAST;

float Time::timeScale = 1;
float Time::fixedTimeStep = 0.02;

float Time::_deltaTime = 0;
float Time::_unscaledDeltaTime = 0;
float Time::_frameCount = 0;
float Time::_time = 0;

//READ ONLY
const float &Time::deltaTime = Time::_deltaTime;
const float &Time::unscaledDeltaTime = Time::_unscaledDeltaTime;
const float &Time::frameCount = Time::_frameCount;
const float &Time::time = Time::_time;

void Time::Init()
{
	NOW = SDL_GetPerformanceCounter();
	LAST = 0;
}

void Time::Update()
{
	LAST = NOW;
	NOW = SDL_GetPerformanceCounter();
	_unscaledDeltaTime = (float)((NOW - LAST) / (float)SDL_GetPerformanceFrequency());
	_deltaTime = _unscaledDeltaTime * timeScale;
	_time += _unscaledDeltaTime;
}
