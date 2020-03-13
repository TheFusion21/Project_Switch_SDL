#include "Object.h"
#include "Transform.h"
#include "SpriteRenderer.h"
#include "Rigidbody2D.h"
#include "SceneManager.h"
Object::Object() : Object(0, 0)
{
	name = "GameObject";
}
Object::Object(float x, float y) : enabled(true), layer(0), transform(this)
{
	transform.localPosition.SetX(x);
	transform.localPosition.SetY(y);
	components.push_back(&transform);
	//components.push_back(new SpriteRenderer(this));
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
	for (std::vector<Component*>::iterator it = components.begin(); it != components.end(); ++it)
	{
		(*it)->Awake();
	}
}
void Object::Start()
{
	for (std::vector<Component*>::iterator it = components.begin(); it != components.end(); ++it)
	{
		(*it)->Start();
	}
}
void Object::Update()
{
	for (std::vector<Component*>::iterator it = components.begin(); it != components.end(); ++it)
	{
		(*it)->Update();
	}
}

void Object::FixedUpdate()
{
	for (std::vector<Component*>::iterator it = components.begin(); it != components.end(); ++it)
	{
		(*it)->FixedUpdate();
	}
}

void Object::Render()
{
	for (std::vector<Component*>::iterator it = components.begin(); it != components.end(); ++it)
	{
		(*it)->Render();
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
	/*if (component->GetName().find("Collider") != std::string::npos)
		AddComponent(new RigidBody2D(this));*/
	for (std::vector<Component*>::iterator it = components.begin(); it != components.end(); ++it)
	{
		if ((*it)->GetName() == component->GetName() || (*it)->GetName().find(component->GetName()) != std::string::npos)
			return (*it);
	}
	components.push_back(component);
	if (components.back()->enabled)
	{
		components.back()->Awake();
		components.back()->Start();
	}
	return components.back();
}

std::vector<Component*> Object::GetComponentsWithName(std::string name)
{
	std::vector<Component*> list;
	for (std::vector<Component*>::iterator it = components.begin(); it != components.end(); ++it)
	{
		if ((*it)->GetName() == name || (*it)->GetName().find(name) != std::string::npos)
			list.push_back((*it));
	}
	return list;
}

void Object::RemoveCompontent(std::string name)
{
	for (std::vector<Component*>::iterator it = components.begin(); it != components.end(); ++it)
	{
		if ((*it)->GetName() == name)
		{
			it = components.erase(it);
			return;
		}
	}
}


Object * Object::Instantiate(Object* object)
{
	return Instantiate(object, object->transform.localPosition, object->transform.localRotation);
}

Object * Object::Instantiate(Object* object, Vector2D position)
{
	return Instantiate(object, position, object->transform.localRotation);
}

Object * Object::Instantiate(Object* object, Vector2D position, float rotation)
{
	object->transform.localRotation = rotation;
	object->transform.localPosition.Set(position);
	SceneManager::instance()._currentScene->_objects.push_back(object);
	if (SceneManager::instance()._currentScene->_objects.back()->IsEnabled())
	{
		SceneManager::instance()._currentScene->_objects.back()->Awake();
		SceneManager::instance()._currentScene->_objects.back()->Start();
	}
	return SceneManager::instance()._currentScene->_objects.back();
}

Object * Object::FindByName(std::string name)
{
	for (std::vector<Object*>::iterator it = SceneManager::instance()._currentScene->_objects.begin(); it != SceneManager::instance()._currentScene->_objects.end(); ++it)
	{
		if ((*it)->name == name)
			return (*it);
	}
	return nullptr;
}
