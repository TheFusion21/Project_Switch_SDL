#ifndef SCENE_H
#define SCENE_H
#include <string>
#include <vector>
#include "Object.h"
class Scene
{
private:
	float timePast = 0;
public:
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
	std::string _stateName;
	std::vector<Object *> _objects;
};
#endif