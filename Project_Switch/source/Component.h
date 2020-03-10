#ifndef COMPONENT_H
#define COMPONENT_H
#include "Vector2D.h"
#include <string>

class Object;
class Component
{
private:
	friend class Object;
	friend class Scene;
	Component(){}
protected:
	Object* gameObject;
	//Indicates wether the object is enabled or not. Use Disable and Enable to change this state
	bool enabled = true;

	Component(Object * _gameObject);
	//Awake is called when the script instance is being loaded.
	virtual void Awake();
	//Start is called on the frame when a script is enabled just before any of the Update methods are called the first time.
	virtual void Start();
	//Render is called every frame, if the object is enabled.
	virtual void Render();
	//Update is called every frame, if the object is enabled.
	virtual void Update();

	virtual void FixedUpdate();
	//This function is called when the object becomes enabled and active.
	virtual void OnEnable();
	//This function is called when the object becomes disabled.
	virtual void OnDisable();
	//This function is called to enable the component
	void Enable();
	//This function is called to disable the component
	void Disable();

	virtual std::string GetName() = 0;

	static void Destroy(Component * cmpnt);
	static void Destroy(Component * cmpnt, float time);

	static void Destroy(Object * obj);
	static void Destroy(Object * obj, float time);
	
};

#endif