#include "Scene.h"
#include <algorithm>
#include "SDL2/SDL.h"
#include "Renderer.h"
#include "Collider2D.h"
#include "Time.h"

void Scene::Update()
{
	for (std::map<Component*, float>::iterator it = cmpntsDestroy.begin(); it != cmpntsDestroy.end(); ++it)
	{
		if (Time::time >= (*it).second)
		{
			(*it).first->gameObject->RemoveCompontent((*it).first->GetName());
			it = cmpntsDestroy.erase(it);
		}
	}
	for (std::map<Object*, float>::iterator it = objDestroy.begin(); it != objDestroy.end();)
	{
		if (Time::time >= (*it).second)
		{
			
			_objects.erase(std::remove(_objects.begin(), _objects.end(), (*it).first), _objects.end());
			it = objDestroy.erase(it);
		}
		else
		{
			++it;
		}
	}
	std::vector<Object*> buffer = _objects;
	for (std::vector<Object*>::iterator  it = buffer.begin(); it != buffer.end(); ++it)
	{
		(*it)->Update();
	}
	timePast += Time::deltaTime;
	if (timePast > Time::fixedTimeStep)
	{
		for (std::vector<Object*>::iterator it = buffer.begin(); it != buffer.end(); ++it)
		{
			(*it)->FixedUpdate();
		}
		timePast -= Time::fixedTimeStep;
	}
}
void Scene::Render()
{
	//Sort by layer
	std::sort(_objects.begin(), _objects.end(),
	[](const Object* a, const Object* b) -> bool
	{
			return a->layer < b->layer;
	});

	for (std::vector<Object*>::iterator it = _objects.begin(); it != _objects.end(); ++it)
	{
		(*it)->Render();
	}
}
void Scene::Exit()
{
	for (std::vector<Object*>::iterator it = _objects.begin(); it != _objects.end(); ++it)
	{
		delete (*it);
	}
}


