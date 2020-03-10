#include "Transform.h"
#include "Object.h"
const std::string Transform::name = "Transform";
Transform::Transform(Object* _gameObject) : Component(_gameObject), scale(1, 1), anchor(.5f, .5f), localPosition(0, 0), parent(nullptr)
{

}
Vector2D Transform::GetGlobalPosition()
{
	Vector2D pos;
	pos.Set(localPosition);
	Transform * curParent = parent;
	while (curParent != nullptr)
	{
		pos += curParent->localPosition;
		curParent = curParent->parent;
	}
	return pos;
}
