#include "Input.h"

SDL_Event Input::event;
float Input::axisValues[Input::AxisCode::AXIS_COUNT];
Input::KeyState Input::states[Input::KeyCode::NX_COUNT];

void Input::Update()
{
	for (int i = 0; i < NX_COUNT; i++)
	{
		if (states[i] == PRESSED)
			states[i] = DOWN;
		else if (states[i] == RELEASED)
			states[i] = NONE;
	}
	while (SDL_PollEvent(&event))
	{
		switch (event.type) {
		case SDL_JOYAXISMOTION:
			/*SDL_Log("Joystick %d axis %d value: %d\n",
				event.jaxis.which,
				event.jaxis.axis, event.jaxis.value);*/
			axisValues[event.jaxis.axis] = event.jaxis.value;
			break;

		case SDL_JOYBUTTONDOWN:
			//SDL_Log("Joystick %d button %d down\n", event.jbutton.which, event.jbutton.button);
			// https://github.com/devkitPro/SDL/blob/switch-sdl2/src/joystick/switch/SDL_sysjoystick.c#L52
			// seek for joystick #0
			if (event.jbutton.which == 0)
			{
				states[event.jbutton.button] = PRESSED;
			}
			break;
		case SDL_JOYBUTTONUP:
			//SDL_Log("Joystick %d button %d up\n", event.jbutton.which, event.jbutton.button);
			if (event.jbutton.which == 0)
			{
				states[event.jbutton.button] = RELEASED;
			}
			break;
		default:
			break;
		}
	}
}
