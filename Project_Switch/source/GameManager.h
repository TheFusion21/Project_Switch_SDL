#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <string>
#include "SDL2/SDL.h"
#include "Vector2D.h"
#include "Camera.h"
struct Color;
class Debug
{
public:
	static bool showCollider;
	static Color colliderColor;
	static bool enableSocket;
};
class GameManager
{
public:
	Camera camera;

	static GameManager& instance();

	bool Init();

	bool InitRomFs();

	bool InitSDL();

	bool CreateWindow(std::string title, int w, int h);

	bool CreateRenderer();

	bool InitSwitchController();

	void deInitSDL();

	inline SDL_Renderer * GetRenderer() { return SDLrenderer; }

	inline SDL_Window * GetWindow() { return SDLwindow; }

	inline Vector2D GetSize() { return Vector2D(width, height); }

	inline float GetRatio() { return width / (float)height; }
private:
	friend class Component;
	SDL_Window * SDLwindow;
	SDL_Renderer * SDLrenderer;
	
	int width, height;
	GameManager();
	~GameManager();

};
#endif