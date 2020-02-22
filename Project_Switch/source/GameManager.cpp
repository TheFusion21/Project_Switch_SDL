#include "GameManager.h"
#include "Time.h"
#include "SDL2/SDL_image.h"
#include "switch.h"
#include "Structs.h"
bool Debug::showCollider = false;
Color Debug::colliderColor = { 0.224f, 1, 0.078f, 1};
bool Debug::enableSocket = false;
GameManager::GameManager()
{}

GameManager::~GameManager()
{}

GameManager& GameManager::instance()
{
	static GameManager _instance;
	return _instance;
}

bool GameManager::Init()
{
	Time::Init();
	if (!InitRomFs())
		return false;
	if (!InitSDL())
		return false;
	if (!InitSwitchController())
		return false;
	return true;
}

bool GameManager::InitRomFs()
{
	Result rc = romfsInit();
	if (R_FAILED(rc))
	{
		SDL_Log("romfs: %s\n", SDL_GetError());
		return false;
	}
	return true;
}

bool GameManager::InitSDL()
{
	if (Debug::enableSocket)
	{
		Result rc = socketInitializeDefault();
		if (R_FAILED(rc))
		{
			return false;
		}
		if (nxlinkStdio() < 0)
		{
			return false;
		}
	}
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0) {
		SDL_Log("SDL_Init: %s\n", SDL_GetError());
		return false;
	}
	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		SDL_Log("IMG_Init: %s\n", IMG_GetError());
		return false;
	}
	SDL_Log("SDL Init: succeeded");
	return true;
}

bool GameManager::CreateWindow(std::string title, int w, int h)
{
	width = w;
	height = h;
	SDLwindow = SDL_CreateWindow(title.c_str(), 0, 0, w, h, 0);
	if (!SDLwindow) {
		SDL_Log("SDL_CreateWindow: %s\n", SDL_GetError());
		SDL_Quit();
		return false;
	}
	SDL_Log("Created Window");
	return true;
}

bool GameManager::CreateRenderer()
{
	SDLrenderer = SDL_CreateRenderer(SDLwindow, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!SDLrenderer) {
		SDL_Log("SDL_CreateRenderer: %s\n", SDL_GetError());
		SDL_Quit();
		return false;
	}
	SDL_Log("Created Renderer");
	return true;
}

bool GameManager::InitSwitchController()
{
	for (int i = 0; i < 2; i++) {
		if (SDL_JoystickOpen(i) == NULL) {
			SDL_Log("SDL_JoystickOpen: %s\n", SDL_GetError());
			SDL_Quit();
			return false;
		}
	}
	return true;
}

void GameManager::deInitSDL()
{
	SDL_DestroyRenderer(SDLrenderer);
	SDL_DestroyWindow(SDLwindow);
	IMG_Quit();
	SDL_Quit();
	socketExit();
}
