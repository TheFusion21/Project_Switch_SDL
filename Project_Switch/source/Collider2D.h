#pragma once
#include "Component.h"
class Collider2D : public Component
{
public:
	Vector2D size;
	bool isTrigger;
	Vector2D offset;
	float density;
	static const std::string name;

	Collider2D(Object* _gameObject);

	std::string GetName() override
	{
		return name;
	}
};