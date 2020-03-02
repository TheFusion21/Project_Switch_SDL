#include "Scene.h"
#include <algorithm>
#include "SDL2/SDL.h"
#include "Renderer.h"
#include "Collider2D.h"
void Scene::Update()
{
	for (std::vector<Object*>::iterator it = _objects.begin(); it != _objects.end(); ++it)
	{
		(*it)->Update();
		int CompCount = (*it)->GetComponentCount();
		for (int i = 0; i < CompCount; i++)
		{
			(*it)->GetComponent(i)->Update();
		}
	}
}
void Scene::Render()
{
	//Sort by layer
	std::sort(_objects.begin(), _objects.end(),
	[](const Object* a, const Object* b) -> bool
	{
			return a->layer > b->layer;
	});

	for (std::vector<Object*>::iterator it = _objects.begin(); it != _objects.end(); ++it)
	{
		int CompCount = (*it)->GetComponentCount();
		for (int i = 0; i < CompCount; i++)
		{
			(*it)->GetComponent(i)->Render();
		}
	}
}
void Scene::Exit()
{
	for (std::vector<Object*>::iterator it = _objects.begin(); it != _objects.end(); ++it)
	{
		delete (*it);
	}
}


