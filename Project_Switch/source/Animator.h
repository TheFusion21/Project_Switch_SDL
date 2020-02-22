#ifndef ANIMATOR_H
#define ANIMATOR_H
#include "Component.h"
#include <map>
#include <vector>
class Animation
{
private:
	friend class Animator;
	int samples;
	void Update();
public:
	Animation();
	void SetSamples(int samples);
	int GetSamples();
};
class Transition
{
public:
	const unsigned int start;
	const unsigned int end;
	bool hasExitTime;
	float exitTime;
	Transition(const unsigned int id1, const unsigned int id2);
};
class Animator : public Component
{
private:
	unsigned int index = 0;
	std::map<const unsigned int, Animation> animations;
	std::vector<Transition> transitions;
public:
	
	static const std::string name;
	enum Update_Mode
	{
		Normal,
		Unscaled_Time
	};

	Update_Mode updateMode;
	Animator(Object* _gameObject);
	void Update();
	void Render();
	std::string GetName()
	{
		return name;
	}
	const unsigned int AddAnimation(Animation anim);
	Animation * GetAnimationAt(const unsigned int index);

	void AddTransition(Transition transition);
};
#endif