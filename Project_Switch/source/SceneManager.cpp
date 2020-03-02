#include "SceneManager.h"
#include "Time.h"
#include "Input.h"
#include "GameManager.h"
SceneManager &SceneManager::instance()
{
	static SceneManager _instance;
	return _instance;
}

SceneManager::SceneManager()
{}

SceneManager::~SceneManager()
{
}


void SceneManager::Run(Scene *initialScene)
{
	_fsm_status = true;
	instance().push(initialScene);
	if (_fsm_status)
	{
		for (;;)
		{
			if (!_fsm_status)
				break;
			Time::Update();
			Input::Update();
			if (Input::GetKeyDown(Input::KeyCode::NX_PLUS))
				_fsm_status = false;
			_scenes.back()->Update();
			SDL_SetRenderDrawColor(GameManager::instance().GetRenderer(), 111, 111, 111, 255);
			//SDL_GetWindowSize(Globals::window, &w, &h);
			Vector2D vec = GameManager::instance().GetSize();
			SDL_Rect f = { 0, 0, vec.GetX() , vec.GetY() };
			SDL_RenderFillRect(GameManager::instance().GetRenderer(), &f);
			_scenes.back()->Render();
			SDL_RenderPresent(GameManager::instance().GetRenderer());

		}
	}
	GameManager::instance().deInitSDL();
}

void SceneManager::push(Scene *scene)
{
	_scenes.push_back(scene);
	_currentScene = scene;
	_scenes.back()->Init();
}

void SceneManager::change(Scene *scene)
{
	if (_scenes.empty())
	{
		if (_scenes.back()->GetStateName() == scene->GetStateName())
		{
			return;
		}
		else
		{
			_scenes.back()->Exit();
			delete _scenes.back();
			_scenes.pop_back();
		}
	}
	_scenes.push_back(scene);
	_scenes.back()->Init();
}

void SceneManager::Pop()
{
	if (!_scenes.empty())
	{
		_scenes.back()->Exit();
		delete _scenes.back();
		_scenes.pop_back();
	}
}

void SceneManager::Exit()
{
	_fsm_status = false;
	if (_scenes.empty())
	{
		for (std::vector<Scene *>::iterator it = _scenes.begin(); it != _scenes.end(); ++it)
		{
			(*it)->Exit();
			delete (*it);
		}
	}
}