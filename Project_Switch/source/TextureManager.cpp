#include "TextureManager.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "GameManager.h"
TextureManager& TextureManager::instance()
{
	static TextureManager _instance;
	return _instance;
}

SDL_Texture * TextureManager::GetTexture(std::string name)
{
	if (_textureMap.find(name) != _textureMap.end())
	{
		return _textureMap[name];
	}
	SDL_Surface * image = IMG_Load(name.c_str());
	_textureMap[name] = SDL_CreateTextureFromSurface(GameManager::instance().GetRenderer(), image);
	return _textureMap[name];
}
