#ifndef RIGIBODY2D_H
#define RIGIBODY2D_H
#include "Component.h"
class RigidBody2D : public Component
{
private:
	Vector2D _velocity;
	Vector2D _position;
	float _mass = 1.0f;
	float _drag = 0.1f;
	float _gravityScale = 1.0f;
public:
	static const std::string name;

	RigidBody2D(Object * _gameObject);

	void Render();

	std::string GetName() override
	{
		return name;
	}
};
#endif