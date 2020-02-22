#include "Animator.h"
#include "SDL2/SDL.h"
//ANIMATION
Animation::Animation()
{

}
void Animation::Update()
{

}
void Animation::SetSamples(int samples)
{
	this->samples = samples;
}

int Animation::GetSamples()
{
	return samples;
}
//TRANSITION
Transition::Transition(unsigned int id1, unsigned int id2) : exitTime(1), hasExitTime(true), start(id1), end(id2)
{

}
//ANIMATOR
const std::string Animator::name = "Animator";
Animator::Animator(Object* _gameObject) : Component(_gameObject), updateMode(Animator::Update_Mode::Normal)
{

}

void Animator::Update()
{

}

void Animator::Render()
{
}

const unsigned int Animator::AddAnimation(Animation anim)
{
	for (std::map<unsigned int, Animation>::iterator it = animations.begin(); it != animations.end(); ++it)
	{
		if (&it->second == &anim)
			return it->first;
	}
	
	animations.insert(std::pair<unsigned int, Animation>(index, anim));
	index++;
	return index - 1;
}

Animation * Animator::GetAnimationAt(const unsigned int index)
{
	if (animations.find(index) != animations.end())
		return &animations.find(index)->second;
	return nullptr;
}

void Animator::AddTransition(Transition transition)
{
	for (std::vector<Transition>::iterator it = transitions.begin(); it != transitions.end(); ++it)
	{
		if ((*it).start == transition.start && (*it).end == transition.end)
			return;
		if (&(*it) == &transition)
			return;
	}
}


