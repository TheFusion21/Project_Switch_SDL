
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
public:
	Player() : Object(0, 0), speed(4, 4)
	{
		BoxCollider2D * collider2D = (BoxCollider2D*)AddComponent(new BoxCollider2D(this));
		collider2D->size.Set(0.25f, 0.578125f);
		collider2D->edgeRadius = 0.09375f;
		Animator* animator = (Animator*)AddComponent(new Animator(this));
		sheet = SpriteSheet::FromTileSize("romfs:/Player.png", spriteSize, spriteSize);
		
	}
	void Awake()
	{

	}
	void Start()
	{
		SpriteRenderer* renderer = (SpriteRenderer*)GetComponent(SpriteRenderer::name);
		if(renderer != nullptr)
			renderer->sprite = sheet.GetSpriteAt(0, 0);
	}
	void Update()
	{
		//Vertical Stick assigned to Horizontal Movement
		if (Input::GetAxisRaw(Input::AxisCode::AXIS_RSTICK_V) != 0)
		{
			transform.position.SetX(transform.position.GetX() + Time::deltaTime * speed.GetX() * Input::GetAxisRaw(Input::AxisCode::AXIS_RSTICK_V));
		}
		//Horizontal Stick assigned to Vertical Movement
		if (Input::GetAxisRaw(Input::AxisCode::AXIS_RSTICK_H) != 0)
		{
			transform.position.SetY(transform.position.GetY() + Time::deltaTime * speed.GetY() * Input::GetAxisRaw(Input::AxisCode::AXIS_RSTICK_H));
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