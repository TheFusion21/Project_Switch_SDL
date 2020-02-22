#include "Transform.h"

const std::string Transform::name = "Transform";
Transform::Transform(Object* _gameObject) : Component(_gameObject), scale(1, 1), anchor(.5f, .5f), position(0, 0)
{

}

void Transform::Update()
{
}

void Transform::Render()
{
}
