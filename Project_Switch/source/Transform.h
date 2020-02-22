#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "Component.h"
class Transform : public Component
{
public:
	static const std::string name;
	Vector2D position;
	Vector2D scale;
	Vector2D anchor;
	float rotation = 0;
	Transform(Object * _gameObject);
	void Update();
	void Render();
	std::string GetName()
	{
		return name;
	}
};
#endif