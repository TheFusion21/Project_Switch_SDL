#ifndef COMPONENT_H
#define COMPONENT_H
#include "Vector2D.h"
#include <string>

class Object;
class Component
{
protected:
	Object* gameObject;
	//Indicates wether the object is enabled or not. Use Disable and Enable to change this state
	bool enabled = true;

	Component(Object * _gameObject);
public:
	
	
	//Render is called every frame, if the object is enabled.
	virtual void Render() = 0;
	//Update is called every frame, if the object is enabled.
	virtual void Update();
	//This function is called when the object becomes enabled and active.
	virtual void OnEnable();
	//This function is called when the object becomes disabled.
	virtual void OnDisable();
	//This function is called to enable the component
	virtual void Enable();
	//This function is called to disable the component
	virtual void Disable();

	virtual std::string GetName() = 0;

};

#endif