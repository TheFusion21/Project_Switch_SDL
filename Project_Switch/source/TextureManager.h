#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
struct SDL_Texture;
#include <string>
#include <map>
class TextureManager
{
public:
	static TextureManager& instance();
	SDL_Texture * GetTexture(std::string name);

private:
	TextureManager() {}
	~TextureManager() {}
	std::map<std::string, SDL_Texture*> _textureMap;
};
#endif