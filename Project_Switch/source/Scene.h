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
	
protected:
	friend class Object;
	std::string _stateName;
	std::vector<Object *> _objects;
};
#endif