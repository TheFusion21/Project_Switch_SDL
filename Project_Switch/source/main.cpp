
#if __INTELLISENSE__
typedef unsigned int __SIZE_TYPE__;
typedef unsigned long __PTRDIFF_TYPE__;
#define __attribute__(q)
#define __builtin_strcmp(a,b) 0
#define __builtin_strlen(a) 0
#define __builtin_memcpy(a,b) 0
#define __builtin_va_list void*
#define __builtin_va_start(a,b)
#define __extension__
#endif

#if defined(_MSC_VER)
#include <BaseTsd.h>
typedef SSIZE_T ssize_t;
#endif

#include "SDL_Switch.h"

class Player : public Object
{
private:
	int spriteSize = 74;
	Vector2D speed;
	SpriteSheet sheet;
	Animator * animator;
	unsigned int idleAnimIndex, rightAnimIndex, rightRevAnimIndex, leftAnimIndex, leftRevAnimIndex;
	unsigned int idle2AnimIndex, upAnimIndex, upRevIndex, downAnimIndex, downRevAnimIndex;
	unsigned int vToHAnimIndex, hToVAnimIndex;
public:
	bool verticalMode = true;
	bool canShoot = true;
	bool canMove = true;
	Player() : Object(0, 0), speed(4, 4)
	{
		
		//COLLIDER SETUP
		BoxCollider2D * collider2D = (BoxCollider2D*)AddComponent(new BoxCollider2D(this));
		collider2D->size.Set(0.2734375f, 0.578125f);
		collider2D->edgeRadius = 0.09375f;

		//ANIMATION TREE
		
		animator = (Animator*)AddComponent(new Animator(this));
		sheet = SpriteSheet::FromTileSize("romfs:/Player.png", spriteSize, spriteSize);
		
		//IDLE ANIMATION
		Animation idleAnim;
		Key idleKey1;
		idleKey1.sprite = sheet.GetSpriteAt(0, 0);
		idleAnim.AddKey(0, idleKey1);
		Key idleKey2;
		idleKey2.sprite = sheet.GetSpriteAt(0, 0);
		idleAnim.AddKey(1, idleKey2);
		idleAnim.SetSamples(2);
		idleAnimIndex = animator->AddAnimation(idleAnim);

		//RIGHT IN ANIMATION
		Animation rightAnim;
		for (int i = 0; i < 6; i++)
		{
			Key rightKey;
			rightKey.sprite = sheet.GetSpriteAt(i, 1);
			rightAnim.AddKey(i, rightKey);
		}
		rightAnim.SetSamples(30);
		rightAnim.loop = false;
		rightAnimIndex = animator->AddAnimation(rightAnim);

		//RIGHT OUT ANIMATION
		Animation rightRevAnim;
		for (int i = 0; i < 6; i++)
		{
			Key rightRevKey;
			rightRevKey.sprite = sheet.GetSpriteAt(5-i, 1);
			rightRevAnim.AddKey(i, rightRevKey);
		}
		rightRevAnim.SetSamples(30);
		rightRevAnim.loop = false;
		rightRevAnimIndex = animator->AddAnimation(rightRevAnim);

		//LEFT IN ANIMATION
		Animation leftAnim;
		for (int i = 0; i < 6; i++)
		{
			Key leftKey;
			leftKey.sprite = sheet.GetSpriteAt(i, 0);
			leftAnim.AddKey(i, leftKey);
		}
		leftAnim.SetSamples(30);
		leftAnim.loop = false;
		leftAnimIndex = animator->AddAnimation(leftAnim);

		//LEFT OUT ANIMATION
		Animation leftRevAnim;
		for (int i = 0; i < 6; i++)
		{
			Key leftRevKey;
			leftRevKey.sprite = sheet.GetSpriteAt(5-i, 0);
			leftRevAnim.AddKey(i, leftRevKey);
		}
		leftRevAnim.SetSamples(30);
		leftRevAnim.loop = false;
		leftRevAnimIndex = animator->AddAnimation(leftRevAnim);

		//RIGHT TRANSITIONS

		//FROM IDLE TO RIGHT IN
		Transition idleToRight(idleAnimIndex, rightAnimIndex);
		idleToRight.hasExitTime = false;
		idleToRight.trigger = "iright";
		animator->AddTransition(idleToRight);

		//FROM RIGHT IN TO RIGHT OUT
		Transition rightToRight(rightAnimIndex, rightRevAnimIndex);
		rightToRight.hasExitTime = true;
		rightToRight.trigger = "oright";
		animator->AddTransition(rightToRight);

		//FROM RIGHT OUT TO IDLE
		Transition rightToIdle(rightRevAnimIndex, idleAnimIndex);
		rightToIdle.hasExitTime = true;
		rightToIdle.trigger = "";
		animator->AddTransition(rightToIdle);

		//LEFT TRANSITIONS

		//FROM IDLE TO LEFT IN
		Transition idleToLeft(idleAnimIndex, leftAnimIndex);
		idleToLeft.hasExitTime = false;
		idleToLeft.trigger = "ileft";
		animator->AddTransition(idleToLeft);

		//FROM LEFT IN TO LEFT OUT
		Transition leftToLeft(leftAnimIndex, leftRevAnimIndex);
		leftToLeft.hasExitTime = true;
		leftToLeft.trigger = "oleft";
		animator->AddTransition(leftToLeft);

		//FROM LEFT OUT TO IDLE
		Transition leftToIdle(leftRevAnimIndex, idleAnimIndex);
		leftToIdle.hasExitTime = true;
		leftToIdle.trigger = "";
		animator->AddTransition(leftToIdle);

		SDL_Log("Created Player");
	}
	void Awake()
	{

	}
	void Start()
	{
		if (!verticalMode)
			animator->OverrideCurrentAnimation(idle2AnimIndex);
	}
	void Update()
	{
		//Vertical Stick assigned to Horizontal Movement
		if (abs(Input::GetAxisRaw(Input::AxisCode::AXIS_RSTICK_V)) > 0.02f)
		{
			if (canMove)
			{
				float val = Input::GetAxisRaw(Input::AxisCode::AXIS_RSTICK_V);
				if (val > 0)
				{
					animator->SetTrigger("oleft");
					animator->SetTrigger("iright");
				}
				else if (val < 0)
				{
					animator->SetTrigger("oright");
					animator->SetTrigger("ileft");
				}
				transform.position.SetX(transform.position.GetX() + Time::deltaTime * speed.GetX() * val);
			}
		}
		else
		{
			animator->SetTrigger("oright");
			animator->SetTrigger("oleft");
		}
		//Horizontal Stick assigned to Vertical Movement
		if (abs(Input::GetAxisRaw(Input::AxisCode::AXIS_RSTICK_H)) > 0.02f)
		{
			if (canMove)
			{
				transform.position.SetY(transform.position.GetY() + Time::deltaTime * speed.GetY() * Input::GetAxisRaw(Input::AxisCode::AXIS_RSTICK_H));
			}
		}
	}
};
class TestScene : public Scene
{
public:
	bool Init()
	{
		_stateName = "TestScene";
		Instantiate(new Player(), Vector2D(0, 0), 0);
		return true;
	}
};
int main(int argc, char* argv[])
{
	Debug::showCollider = true;
	Debug::enableSocket = true;
	if (!GameManager::instance().Init())
		return EXIT_FAILURE;
	if (!GameManager::instance().CreateWindow("Angry Skeletal", 960, 540))
		return EXIT_FAILURE;
	if (!GameManager::instance().CreateRenderer())
		return EXIT_FAILURE;
	SceneManager::instance().Run(new TestScene());
	return EXIT_SUCCESS;
}