#include "Component.h"

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
