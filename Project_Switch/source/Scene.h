#ifndef SCENE_H
#define SCENE_H
#include <string>
#include <vector>
#include "Object.h"

#include <map>
class Scene
{
private:
	float timePast = 0;
	
public:
	std::map<Component*, float> cmpntsDestroy;
	std::map<Object*, float> objDestroy;
	virtual bool Init() = 0;

	void Update();

	void Render();

	void Exit();

	~Scene(){}
	std::string GetStateName()
	{
		return _stateName;
	}
	inline int GetObjectCount() { return _objects.size(); }

protected:
	friend class Object;
	friend class Physics2D;
	std::string _stateName;
	std::vector<Object *> _objects;
};
#endif