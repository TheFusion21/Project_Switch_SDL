#include "Scene.h"
#include <algorithm>
#include "SDL2/SDL.h"
#include "Renderer.h"
#include "Collider2D.h"
#include "Time.h"
void Scene::Update()
{
	std::vector<Object*> buffer = _objects;
	for (std::vector<Object*>::iterator  it = buffer.begin(); it != buffer.end(); ++it)
	{
		(*it)->Update();
	}
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


