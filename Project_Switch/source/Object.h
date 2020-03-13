#ifndef OBJECT_H
#define OBJECT_H
#include "Transform.h"
#include <string>
#include <vector>
class Object
{
private:
	//Indicates wether the object is enabled or not. Use Disable and Enable to change this state
	bool enabled = true;
	std::vector<Component*> components;
public:
	//Define in which order to draw the objects
	int layer = 0;
	std::string name;
	Transform transform;
	Object();
	Object(float x, float y);
	~Object();

	//Awake is called when the script instance is being loaded.
	void Awake();
	//Start is called on the frame when a script is enabled just before any of the Update methods are called the first time.
	void Start();
	//Update is called every frame, if the object is enabled.
	void Update();

	void FixedUpdate();
	//Render is called every frame, if the object is enabled.
	void Render();
	bool IsEnabled() { return enabled; }

	Component* GetComponent(std::string name);
	Component* GetComponent(int index);
	inline int GetComponentCount() { return components.size(); }
	Component* AddComponent(Component * component);
	std::vector<Component*> GetComponentsWithName(std::string name);
	void RemoveCompontent(std::string name);

	static Object * Instantiate(Object* object);
	static Object * Instantiate(Object* object, Vector2D position);
	static Object * Instantiate(Object* object, Vector2D position, float rotation);

	static Object * FindByName(std::string name);
};
#endif