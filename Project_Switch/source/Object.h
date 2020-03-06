#ifndef OBJECT_H
#define OBJECT_H
#include "Transform.h"
#include <string>
#include <vector>
class Scene;
class Object
{
private:
	//Indicates wether the object is enabled or not. Use Disable and Enable to change this state
	bool enabled = true;
	std::vector<Component*> components;
public:
	//Define in which order to draw the objects
	int layer = 0;
	Transform transform;
	Object(float x, float y);
	~Object();

	//Awake is called when the script instance is being loaded.
	virtual void Awake() = 0;
	//Start is called on the frame when a script is enabled just before any of the Update methods are called the first time.
	virtual void Start() = 0;
	//Update is called every frame, if the object is enabled.
	virtual void Update() = 0;
	//Reset to default values.
	virtual void Reset();
	//This function is called to enable the object
	void Enable();
	//This function is called to disable the object
	void Disable();

	bool IsEnabled() { return enabled; }

	Component* GetComponent(std::string name);

	Component* GetComponent(int index);

	inline int GetComponentCount() { return components.size(); }

	Component* AddComponent(Component * component);

	static Object * Instantiate(Object* object);
	static Object * Instantiate(Object* object, Vector2D position);
	static Object * Instantiate(Object* object, Vector2D position, float rotation);
protected:
	//This function is called when the object becomes enabled and active.
	virtual void OnEnable();
	//This function is called when the object becomes disabled.
	virtual void OnDisable();
};
#endif