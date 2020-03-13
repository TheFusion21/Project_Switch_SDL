#include "Rigidbody2D.h"
#include "Object.h"
#include "Time.h"
#include "Physics2D.h"
const std::string RigidBody2D::name = "Rigidbody2D";

RigidBody2D::RigidBody2D(Object* _gameObject) : Component(_gameObject)
{
	
}

bool RigidBody2D::IsSleeping()
{
	return _sleeping;
}

void RigidBody2D::Sleep()
{
	_sleeping = true;
}

void RigidBody2D::WakeUp()
{
	_sleeping = true;
}

void RigidBody2D::SetVelocity(Vector2D vel)
{
	_velocity = vel;
}

void RigidBody2D::AddVelocity(Vector2D vel)
{
	_velocity += vel;
}

Vector2D RigidBody2D::GetVelocity()
{
	return _velocity;
}

void RigidBody2D::MovePosition(Vector2D pos)
{
	_position = pos;
}

void RigidBody2D::AddPosition(Vector2D pos)
{
	_position += pos;
}

Vector2D RigidBody2D::GetPosition()
{
	return _position;
}

void RigidBody2D::SetRotation(float rot)
{
	_degRotation = rot;
	if (_degRotation > 360)
		_degRotation -= 360;
	if (_degRotation < 0)
		_degRotation += 360;
	double PI = 3.141592653589793;
	_radRotation = _degRotation * PI / 180.0f;
}

void RigidBody2D::AddRotation(float rot)
{
	SetRotation(_degRotation + rot);
}

float RigidBody2D::GetRotation()
{
	return _degRotation;
}

void RigidBody2D::Awake()
{
	_position = gameObject->transform.localPosition;
}

void RigidBody2D::FixedUpdate()
{
	if (_sleeping)return;
	_velocity += Physics2D::gravity * gravityScale;
	_position += _velocity * Time::fixedTimeStep;
	
	gameObject->transform.localPosition = _position;
}

