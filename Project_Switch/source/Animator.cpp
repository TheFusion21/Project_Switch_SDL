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
float QuadEaseInOut(float t)
{
	return t < 0.5f ? 2.0f * t * t : -1.0f + (4.0f - 2.0f * t) * t;
	//return t<.5 ? 2*t*t : -1+(4-2*t)*t
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
void Animator::UpdateAnimation()
{
	Animation curAnim = animations[curAnimIndex];
	frame = (int)std::round(time * curAnim.samples);
	
	lastKey = 0;
	firstKey = UINT_MAX;
	for (std::map<unsigned int, Key>::iterator it = curAnim.keys.begin(); it != curAnim.keys.end(); ++it)
	{
		if (lastKey < (*it).first)
		{
			lastKey = (*it).first;
		}
		if (firstKey > (*it).first)
		{
			firstKey = (*it).first;
		}
	}
	if (curAnim.loop && frame > lastKey)
	{
		frame = frame % lastKey;
		time = 0;
	}
	else
	{
		frame = frame > lastKey ? lastKey : frame;
	}
	progress = frame / (float)lastKey;
}
void Animator::UpdateInterpolations()
{
	Animation curAnim = animations[curAnimIndex];
	if (frame < firstKey)
	{
		return;
	}

	struct KeyPair
	{
		unsigned int prevKey = 0;
		unsigned int nextKey = UINT_MAX;
		bool prevKeySet = false;
		bool nextKeySet = false;
	};
	std::map<Vector2D*, KeyPair> vecMarks;
	std::map<float*, KeyPair> floatMarks;
	std::map<int*, KeyPair> intMarks;
	std::map<bool*, KeyPair> boolMarks;

	for (std::map<unsigned int, Key>::iterator it = curAnim.keys.begin(); it != curAnim.keys.end(); ++it)
	{
		if (it->second.vecs.size() > 0)
		{
			//DO MARKS FOR THIS KEY ON VECTORS
			for (std::map<Vector2D*, Vector2D>::iterator v_it = it->second.vecs.begin(); v_it != it->second.vecs.end(); ++v_it)
			{
				
				if (it->first == frame)
				{
					//SET VALUE AND BREAK
					*v_it->first = v_it->second;
					continue;
				}
				if (vecMarks.find(v_it->first) == vecMarks.end())
				{
					vecMarks.insert(std::pair<Vector2D*, KeyPair>(v_it->first, KeyPair()));
				}
				KeyPair& mark = vecMarks.at(v_it->first);
				
				if (it->first >= mark.prevKey && it->first < frame)
				{
					mark.prevKey = it->first;
					mark.prevKeySet = true;
				}
				if (it->first <= mark.nextKey && it->first > frame)
				{
					mark.nextKey = it->first;
					mark.nextKeySet = true;
				}
			}
		}
		//NO NEED FOR MARKS WITH SPRITES AS THERE ARE NOT INTERPOLATED
		if (it->second.sprites.size() > 0)
		{
			for (std::map<Sprite**, Sprite*>::iterator s_it = it->second.sprites.begin(); s_it != it->second.sprites.end(); ++s_it)
			{
				if (it->first == frame)
				{
					*s_it->first = s_it->second;
				}
			}
		}
	}
	for (std::map<Vector2D*, KeyPair>::iterator it = vecMarks.begin(); it != vecMarks.end(); ++it)
	{
		if (it->second.prevKeySet && it->second.nextKeySet)
		{
			Key left = curAnim.keys[it->second.prevKey];
			Key right = curAnim.keys[it->second.nextKey];
			float t = remap(frame, it->second.prevKey, it->second.nextKey, 0, 1);
			Vector2D lerpVec;
			if (t < 0.5f)
			{
				if (left.rightInterpolation == Key::INTERPOLATION_TYPE::LINEAR)
				{
					lerpVec = Vector2D::Lerp(left.vecs.at(it->first), right.vecs.at(it->first), t);
				}
				else if (left.rightInterpolation == Key::INTERPOLATION_TYPE::SMOOTH)
				{
					float st = QuadEaseInOut(t);
					lerpVec = Vector2D::Lerp(left.vecs.at(it->first), right.vecs.at(it->first), st);
				}
			}
			else
			{
				if (right.leftInterpolation == Key::INTERPOLATION_TYPE::LINEAR)
				{
					lerpVec = Vector2D::Lerp(left.vecs.at(it->first), right.vecs.at(it->first), t);
				}
				else if (right.leftInterpolation == Key::INTERPOLATION_TYPE::SMOOTH)
				{
					float st = QuadEaseInOut(t);
					lerpVec = Vector2D::Lerp(left.vecs.at(it->first), right.vecs.at(it->first), st);
				}
			}
			*it->first = lerpVec;
		}
	}
}
void Animator::Update()
{
	if (animations.size() < 1)
		return;
	UpdateTransitions();
	Animation curAnim = animations[curAnimIndex];
	if (curAnim.keys.size() < 1)
	{
		return;
	}
	UpdateAnimation();
	UpdateInterpolations();
	time += Time::deltaTime;
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

const unsigned int Animator::GetCurrentAnimationID()
{
	return curAnimIndex;
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


