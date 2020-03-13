#include "Physics2D.h"
#include "Collider2D.h"
#include "SceneManager.h"
#include <vector>
int Physics2D::velocityIterations = 4;
int Physics2D::positionIterations = 4;
Vector2D Physics2D::gravity = Vector2D(0, -9.81f);

Physics2D & Physics2D::instance()
{
	static Physics2D _instance;
	return _instance;
}

void Physics2D::Update()
{
	std::map<Collider2D*, Collider2D*> dones;
	std::vector<Collider2D*> allColliders;
	//GET ALL COLLIDERS IN CURRENT SCENE
	//THIS IS GARBAGE
	//TODO: REMAKE THIS BECAUSE DONT DO THIS EVERY FRAME?
	for (std::vector<Object*>::iterator it = SceneManager::instance()._currentScene->_objects.begin(); it != SceneManager::instance()._currentScene->_objects.end(); ++it)
	{
		std::vector<Component*> list = (*it)->GetComponentsWithName("Collider2D");
		for (std::vector<Component*>::iterator objIT = list.begin(); objIT != list.end(); ++objIT)
		{
			allColliders.push_back((Collider2D*)(*objIT));
		}
	}

	for (std::vector<Collider2D*>::iterator it1 = allColliders.begin(); it1 != allColliders.end(); ++it1)
	{
		for (std::vector<Collider2D*>::iterator it2 = allColliders.begin(); it2 != allColliders.end(); ++it2)
		{
			//IF ONE OF THEM IS DISABLED NO NEED TO CHECK
			if (!(*it1)->IsEnabled() || !(*it2)->IsEnabled()
			 || !(*it1)->gameObject->IsEnabled() || !(*it2)->gameObject->IsEnabled())
			{
				dones.insert(std::pair<Collider2D*, Collider2D*>( *it1, *it2 ));
				continue;
			}
			//IF ALREADY IN LIST NO NEED TO CHECK
			if (dones.find(*it1) != dones.end() || dones.find(*it2) != dones.end())
			{
				continue;
			}
			
		}
	}
}
