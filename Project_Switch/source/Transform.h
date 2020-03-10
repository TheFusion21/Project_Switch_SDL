#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "Component.h"
class Transform : public Component
{
public:
	Transform * parent;
	static const std::string name;
	Vector2D localPosition;
	Vector2D scale;
	Vector2D anchor;
	float localRotation = 0;
	Transform(Object * _gameObject);
	std::string GetName()
	{
		return name;
	}
	Vector2D GetGlobalPosition();
};
#endif