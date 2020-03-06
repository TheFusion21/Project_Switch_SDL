#include "Object.h"
#include "Transform.h"
#include "SpriteRenderer.h"
#include "Rigidbody2D.h"
#include "SceneManager.h"
Object::Object(float x, float y) : enabled(true), layer(0), transform(this)
{
	transform.position.SetX(x);
	transform.position.SetY(y);
	components.push_back(&transform);
	components.push_back(new SpriteRenderer(this));
}

Object::~Object()
{
	for (std::vector<Component*>::iterator it = components.begin(); it != components.end(); ++it)
	{
		delete (*it);
		components.erase(it);
	}
}

void Object::Awake()
{

}
void Object::Start()
{
	
}
void Object::Update()
{

}
void Object::Reset()
{

}
void Object::OnEnable()
{

}
void Object::OnDisable()
{

}

void Object::Enable()
{
	if (!enabled)
	{
		enabled = true;
		OnEnable();
		Start();
	}
}

void Object::Disable()
{
	if (enabled)
	{
		enabled = false;
		OnDisable();
	}
}

Component* Object::GetComponent(std::string name)
{
	for (std::vector<Component*>::iterator it = components.begin(); it != components.end(); ++it)
	{
		if ((*it)->GetName() == name || (*it)->GetName().find(name) != std::string::npos)
			return (*it);
	}
	return nullptr;
}

Component* Object::GetComponent(int index)
{
	if (components.size() > index)
	{
		return components[index];
	}
	return nullptr;
}
Component* Object::AddComponent(Component* component)
{
	if (component->GetName().find("Collider") != std::string::npos)
		AddComponent(new RigidBody2D(this));
	for (std::vector<Component*>::iterator it = components.begin(); it != components.end(); ++it)
	{
		if ((*it)->GetName() == component->GetName() || (*it)->GetName().find(component->GetName()) != std::string::npos)
			return (*it);
	}
	components.push_back(component);
	return components.back();
}


Object * Object::Instantiate(Object* object)
{
	return Instantiate(object, object->transform.position);
}

Object * Object::Instantiate(Object* object, Vector2D position)
{
	return Instantiate(object, position, object->transform.rotation);
}

Object * Object::Instantiate(Object* object, Vector2D position, float rotation)
{
	SDL_Log("Instantiating Object");
	object->transform.rotation = rotation;
	SDL_Log("Rotation now is %f", object->transform.rotation);
	object->transform.position.Set(position);
	SDL_Log("Position now is %f, %f", object->transform.position.GetX(), object->transform.position.GetY());
	SceneManager::instance()._currentScene->_objects.push_back(object);
	if (SceneManager::instance()._currentScene->_objects.back()->IsEnabled())
	{
		SceneManager::instance()._currentScene->_objects.back()->Awake();
		SceneManager::instance()._currentScene->_objects.back()->Start();
	}
	return SceneManager::instance()._currentScene->_objects.back();
}