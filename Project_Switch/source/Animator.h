#ifndef ANIMATOR_H
#define ANIMATOR_H
#include "Component.h"
#include "Structs.h"
#include <map>
#include <vector>
struct Key
{
	Sprite * sprite = nullptr;
	Vector2D * colliderSize = nullptr;
	Vector2D * colliderOffset = nullptr;
};
class Animation
{
private:
	friend class Animator;
	int samples;
	std::map<unsigned int, Key> keys;
public:
	bool loop = true;
	Animation();
	void SetSamples(int samples);
	int GetSamples();
	void AddKey(unsigned int pos, Key &key);
	void RemoveKeyAt(unsigned int pos);
};
class Transition
{
private:
	friend class Animator;
	const unsigned int start;
	const unsigned int end;
public:
	
	bool hasExitTime;
	float exitTime;
	std::string trigger;
	Transition(const unsigned int id1, const unsigned int id2);
};
class Animator : public Component
{
private:
	unsigned int index = 0;
	unsigned int curAnimIndex = 0;
	float time;
	float progress;
	std::map<const unsigned int, Animation> animations;
	std::vector<Transition> transitions;
	std::map<std::string, bool> triggers;
	void UpdateTransitions();
	void UpdateAnimations();
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
	const unsigned int AddAnimation(Animation &anim);
	Animation * GetAnimationAt(const unsigned int index);
	void OverrideCurrentAnimation(const unsigned int index);
	int AddTransition(Transition &transition);

	void SetTrigger(std::string name);
};
#endif