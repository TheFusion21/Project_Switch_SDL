#pragma once
#include "Renderer.h"
#include "SDL2/SDL.h"
#include "Structs.h"
class SpriteRenderer : public Renderer
{
public:
	Sprite * sprite;
	bool flipX = false;
	bool flipY = false;
	Color color = { 1, 1, 1, 1 };
	static const std::string name;

	SpriteRenderer(Object* _gameObject);

	void Render();

	std::string GetName() override
	{
		return name;
	}
};