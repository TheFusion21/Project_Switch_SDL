#pragma once
#ifndef INPUT_H
#define INPUT_H
#include "SDL2/SDL.h"
class Input
{
private:
	static SDL_Event event;
	enum KeyState
	{
		NONE,
		PRESSED,
		DOWN,
		RELEASED,
	};
public:
	enum KeyCode
	{
		NX_A = 0,
		NX_B = 1,
		NX_X = 2,
		NX_Y = 3,
		NX_LSTICK = 4,
		NX_RSTICK = 5,
		NX_L = 6,
		NX_R = 7,
		NX_ZL = 8,
		NX_ZR = 9,
		NX_PLUS = 10,
		NX_MINUS = 11,
		NX_LEFT = 12,
		NX_UP = 13,
		NX_RIGHT = 14,
		NX_DOWN = 15,
		NX_COUNT = 127
	};
	enum AxisCode
	{
		AXIS_LSTICK_H = 0,
		AXIS_LSTICK_V = 1,
		AXIS_RSTICK_H = 2,
		AXIS_RSTICK_V = 3,
		AXIS_COUNT
	};
	//Returns true while the user holds down the key identified by name.
	static bool GetKey(KeyCode k)
	{
		return states[k] == PRESSED || states[k] == DOWN;
	}
	//Returns true during the frame the user starts pressing down the key identified by name.
	static bool GetKeyDown(KeyCode k)
	{
		return states[k] == PRESSED;
	}
	//Returns true during the frame the user releases the key identified by name.
	static bool GetKeyUp(KeyCode k)
	{
		return states[k] == RELEASED;
	}

	static float GetAxis(AxisCode a)
	{
		return axisValues[a] / (float)32768;
	}
	static float GetAxisRaw(AxisCode a)
	{
		return -GetAxis(a);
	}
	static void Update();
private:
	static float axisValues[];
	static KeyState states[];
};

#endif