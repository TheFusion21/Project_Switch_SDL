#ifndef SCENE_H
#define SCENE_H
#include <string>
#include <vector>
#include "Object.h"
class Scene
{
public:
	virtual bool Init() = 0;

	virtual void Update();

	virtual void Render();

	virtual void Exit();

	virtual ~Scene()
	{}
	std::string GetStateName()
	{
		return _stateName;
	}
	void Instantiate(Object* object);
	void Instantiate(Object* object, Vector2D position);
	void Instantiate(Object* object, Vector2D position, float rotation);
protected:
	std::string _stateName;
	std::vector<Object *> _objects;
};
#endif