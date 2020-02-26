#include "Animator.h"
#include "SDL2/SDL.h"
#include "Object.h"
#include "SpriteRenderer.h"
#include "Collider2D.h"
#include "Time.h"
#include <climits>
//FUNCTIONS
float remap(float value, float oldMin, float oldMax, float newMin, float newMax)
{
	return newMin + (value - oldMin) * (newMax - newMin) / (oldMax - oldMin);
}

//ANIMATION
Animation::Animation()
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
void Animation::AddKey(unsigned int pos, Key &key)
{
	if (keys.find(pos) != keys.end())
		return;
	keys.insert(std::pair<unsigned int, Key>(pos, key));
}
void Animation::RemoveKeyAt(unsigned int pos)
{
	if (keys.find(pos) == keys.end())
		return;
	keys.erase(pos);
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
void Animator::UpdateTransitions()
{
	if (transitions.size() < 1)
		return;
	std::vector<Transition> curAnimTransitions;
	for (std::vector<Transition>::iterator it = transitions.begin(); it != transitions.end(); ++it)
	{
		if (curAnimIndex == (*it).start)
			curAnimTransitions.push_back((*it));
	}
	for (std::vector<Transition>::iterator it = curAnimTransitions.begin(); it != curAnimTransitions.end(); ++it)
	{
		if ((*it).trigger.empty())
		{
			if ((*it).hasExitTime)
			{
				if (progress == 1)
				{
					curAnimIndex = (*it).end;
					time = 0;
					break;
				}
			}
			else
			{
				curAnimIndex = (*it).end;
				time = 0;
				break;
			}
		}
		else
		{
			if (triggers.find((*it).trigger) != triggers.end())
			{
				if (triggers.at((*it).trigger))
				{
					if ((*it).hasExitTime)
					{
						if (progress == 1)
						{
							curAnimIndex = (*it).end;
							time = 0;
							break;
						}
						
					}
					else
					{
						curAnimIndex = (*it).end;
						time = 0;
						break;
					}
						
				}
				
			}
		}
	}
	triggers.clear();
}
void Animator::UpdateAnimations()
{
	
	Animation curAnim = animations[curAnimIndex];

	if (curAnim.keys.size() < 1)
		return;
	int frame = (int)std::round(time * curAnim.samples);
	

	unsigned int lastKey = 0;
	int prevKey = INT_MIN;
	int nextKey = INT_MAX;
	for (std::map<unsigned int, Key>::iterator it = curAnim.keys.begin(); it != curAnim.keys.end(); ++it)
	{
		if (lastKey < (*it).first)
			lastKey = (*it).first;
		if ((*it).first == frame)
			prevKey = nextKey = (*it).first;
		else
		{
			if ((*it).first > frame && nextKey > (*it).first)
			{
				nextKey = (*it).first;
			}
			if ((*it).first < frame && prevKey < (*it).first)
			{
				prevKey = (*it).first;
			}
		}

	}
	if (curAnim.loop)
	{
		frame = frame % lastKey;
		time = 0;
	}
	else
	{
		frame = frame > lastKey ? lastKey : frame;
	}
	progress = frame / (float)lastKey;
	if (prevKey == nextKey)
	{
		Key key = curAnim.keys[prevKey];
		if (key.sprite != nullptr)
		{
			SpriteRenderer * renderer = (SpriteRenderer*)gameObject->GetComponent(SpriteRenderer::name);
			if(renderer != nullptr)
				renderer->sprite = key.sprite;
		}
		if (key.colliderSize != nullptr)
		{
			Collider2D * collider = (Collider2D*)gameObject->GetComponent(Collider2D::name);
			if (collider != nullptr)
				collider->size = *key.colliderSize;
		}
		if (key.colliderOffset != nullptr)
		{
			Collider2D * collider = (Collider2D*)gameObject->GetComponent(Collider2D::name);
			if (collider != nullptr)
				collider->offset = *key.colliderOffset;
		}
	}
	time += Time::deltaTime;
}
void Animator::Update()
{
	if (animations.size() < 1)
		return;
	UpdateTransitions();
	UpdateAnimations();
}

void Animator::Render()
{
}


const unsigned int Animator::AddAnimation(Animation &anim)
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

void Animator::OverrideCurrentAnimation(const unsigned int index)
{
	curAnimIndex = index;
	time = 0;
}

int Animator::AddTransition(Transition &transition)
{
	for (std::vector<Transition>::iterator it = transitions.begin(); it != transitions.end(); ++it)
	{
		if ((*it).start == transition.start && (*it).end == transition.end)
			return -1;
		if (&(*it) == &transition)
			return -1;
	}
	transitions.push_back(transition);
	return 0;
}

void Animator::SetTrigger(std::string name)
{
	//SDL_Log("Setting Trigger: %s", name.c_str());
	if (triggers.find(name) == triggers.end())
	{
		triggers.insert(std::pair<std::string, bool>(name, true));
	}
	else
	{
		triggers.at(name) = true;
	}
}


