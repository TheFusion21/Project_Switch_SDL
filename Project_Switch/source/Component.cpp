#include "Component.h"
#include "SceneManager.h"
#include "Time.h"
Component::Component(Object* _gameObject) : gameObject(_gameObject)
{
}

void Component::Awake()
{
}

void Component::Start()
{
}

void Component::Render()
{
}

void Component::Update()
{
}

void Component::FixedUpdate()
{
}

void Component::OnEnable()
{
}

void Component::OnDisable()
{
}

void Component::Enable()
{
	if (!enabled)
	{
		enabled = true;
		OnEnable();
	}
}

void Component::Disable()
{
	if (enabled)
	{
		enabled = false;
		OnDisable();
	}
}

bool Component::IsEnabled()
{
	return enabled;
}

void Component::Destroy(Component * cmpnt)
{
	Destroy(cmpnt, 0);
}

void Component::Destroy(Component * cmpnt, float time)
{
	SceneManager::instance()._currentScene->cmpntsDestroy.insert(std::pair<Component*, float>(cmpnt, Time::time + time));
}

void Component::Destroy(Object * obj)
{
	Destroy(obj, 0);
}

void Component::Destroy(Object * obj, float time)
{
	SceneManager::instance()._currentScene->objDestroy.insert(std::pair<Object*, float>(obj, Time::time + time));
}
