#ifndef RENDERER_H
#define RENDERER_H
#include "Component.h"
#include "GameManager.h"
class Renderer : public Component
{
public:
	static const std::string name;
	Renderer(Object* _gameobject);
	std::string GetName()
	{
		return name;
	}
};
#endif
