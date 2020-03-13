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

	virtual Vector2D GetCenterPoint() = 0;
	virtual Vector2D GetClosestPoint(Vector2D pos) = 0;
	virtual Rect GetBoundingBox() = 0;
};