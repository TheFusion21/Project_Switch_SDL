#ifndef STRUCTS_H
#define STRUCTS_H
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Vector2D.h"
#include "TextureManager.h"
#include <map>
#include <string>
#include <iostream>
struct Sprite
{
	SDL_Rect src_rect;
	SDL_Texture * src_Texture;
	
	static Sprite * SpriteFromFile(std::string filename)
	{
		Sprite * sprite = new Sprite();
		sprite->src_Texture = TextureManager::instance().GetTexture(filename);
		int w, h;
		SDL_QueryTexture(sprite->src_Texture, NULL, NULL, &w, &h);
		sprite->src_rect = { 0, 0, w, h };
		return sprite;
	}
};
struct SpriteSheet
{
	std::map<std::pair<int, int>, Sprite> sprites;

	Sprite* GetSpriteAt(int x, int y)
	{
		return &sprites[std::pair<int, int>(x, y)];
	}
	static SpriteSheet FromTileCount(std::string filename, int rows, int columns)
	{
		SpriteSheet sheet;
		SDL_Texture* src_Texture = TextureManager::instance().GetTexture(filename);
		int w, h;
		SDL_QueryTexture(src_Texture, NULL, NULL, &w, &h);
		if (h / rows != h / (float)rows
			|| w / columns != w / (float)columns)
		{
			//throw "Row or Column count does not fit pixel perfect into Image";
		}
		for (int x = 0; x < columns; x++)
		{
			for (int y = 0; y < rows; y++)
			{
				Sprite sprite;
				sprite.src_Texture = src_Texture;
				sprite.src_rect =
				{
					x * w / columns,
					y * h / rows,
					w / columns,
					h / rows
				};
				sheet.sprites.insert(std::pair<std::pair<int, int>, Sprite>(std::pair<int, int>(x, y), sprite));
			}
		}

		return sheet;

	}
	static SpriteSheet FromTileSize(std::string filename, int &width, int &height)
	{
		SpriteSheet sheet;
		SDL_Texture* src_Texture = TextureManager::instance().GetTexture(filename);
		int w, h;
		SDL_QueryTexture(src_Texture, NULL, NULL, &w, &h);
		SDL_Log("Loading Sheet: %s with size: %i, %i", filename.c_str(), w, h);
		SDL_Log("Loading Sheet: Tile Size requested: %i, %i", width, height);
		if (h / height != h / (float)height
			|| w / width != w / (float)width)
		{
			//throw "Row or Column count does not fit pixel perfect into Image";
			SDL_Log("Size does not fit into image");
			return sheet;
		}
		
		for (int x = 0; x < w; x+=width)
		{
			for (int y = 0; y < h; y+=height)
			{
				Sprite sprite;
				sprite.src_Texture = src_Texture;
				sprite.src_rect =
				{
					x,
					y,
					width,
					height
				};
				sheet.sprites.insert(std::pair<std::pair<int, int>, Sprite>(std::pair<int, int>(x/width, y/ height), sprite));
			}
		}
		return sheet;
	}
};
struct Color
{
	float r, g, b, a;
};

#endif