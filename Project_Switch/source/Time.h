#pragma once
#include <SDL2/SDL.h>
class Time
{
private:
	static Uint64 NOW;
	static Uint64 LAST;

	static float _deltaTime;
	static float _unscaledDeltaTime;
	static float _frameCount;

	Time(){}
public:
	static const float &deltaTime;
	static const float &unscaledDeltaTime;
	static const float &frameCount;

	static float timeScale;
	static float fixedTimeStep;
	
	static void Init();

	static void Update();
};

