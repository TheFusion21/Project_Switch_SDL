#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H
#include "Scene.h"

class SceneManager
{
public:
	Scene *_currentScene = nullptr;
	static SceneManager &instance();


	void Run(Scene *initialScene);

	void push(Scene *scene);

	void change(Scene *scene);

	void Pop();

	void Exit();
private:
	std::vector<Scene*> _scenes;

	SceneManager();

	~SceneManager();

	
	bool _fsm_status = false;
};
#endif