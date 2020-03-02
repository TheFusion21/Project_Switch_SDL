#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H
#include "Scene.h"

class SceneManager
{
public:
	static SceneManager &instance();


	void Run(Scene *initialScene);

	void push(Scene *scene);

	void change(Scene *scene);

	void Pop();

	void Exit();
private:
	friend class Object;
	std::vector<Scene*> _scenes;

	SceneManager();

	~SceneManager();

	Scene *_currentScene = nullptr;
	bool _fsm_status = false;
};
#endif