#pragma once
#include "Collider2D.h"
class BoxCollider2D : public Collider2D
{
public:
	
	float edgeRadius;

	static const std::string name;

	BoxCollider2D(Object * _gameObject);

	void Render();

	std::string GetName() override
	{
		return name;
	}
};