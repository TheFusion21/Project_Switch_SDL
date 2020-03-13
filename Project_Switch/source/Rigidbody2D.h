#ifndef RIGIBODY2D_H
#define RIGIBODY2D_H
#include "Component.h"
#include "Collider2D.h"
#include <vector>
class RigidBody2D : public Component
{
private:
	Vector2D _lastPosition;
	Vector2D _velocity;
	Vector2D _position;
	float _degRotation;
	float _radRotation;
	bool _sleeping = false;
	//std::vector<Collider2D*> objColliders;
public:
	float mass = 1.0f;
	float drag = 0.1f;
	float gravityScale = 1.0f;

	static const std::string name;
	RigidBody2D(Object * _gameObject);

	bool IsSleeping();
	void Sleep();
	void WakeUp();

	void SetVelocity(Vector2D vel);
	void AddVelocity(Vector2D vel);
	Vector2D GetVelocity();

	void MovePosition(Vector2D pos);
	void AddPosition(Vector2D pos);
	Vector2D GetPosition();

	void SetRotation(float rot);
	void AddRotation(float rot);
	float GetRotation();


	void Awake();

	void FixedUpdate();


	std::string GetName() override
	{
		return name;
	}
};
#endif