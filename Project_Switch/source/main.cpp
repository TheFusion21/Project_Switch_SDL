
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
/*
class BaseBullet : public Object
{
public:
	BaseBullet() : Object(0, 0)
	{
		
	}
	void Awake()
	{

	}
	void Start()
	{ 
		
	}
	void Update()
	{

	}
};
class DefaultBullet : public BaseBullet
{
public:
	DefaultBullet() : BaseBullet()
	{
		SpriteRenderer * renderer = (SpriteRenderer*)GetComponent(SpriteRenderer::name);
		renderer->sprite = Sprite::SpriteFromFile("romfs:/DefaultBullet.png");
	}
};
class BaseGun : public Object
{
protected:
	int curBarrelIndex = 0;
public:
	enum FIREMODE
	{
		ALTERNATING,
		SIMULTANEOUSLY,
	};
	std::vector<Vector2D> BarrelPositions;
	float fireRate = 5;
	FIREMODE fireMode = ALTERNATING;
	float coolDown = 0;
	BaseBullet * bullet;
	BaseGun() : Object(0, 0)
	{

	}
	void Awake()
	{

	}
	void Start()
	{

	}
	void Update()
	{
		if (BarrelPositions.size() == 0 || coolDown == 0)
			return;
		if (coolDown > 0)
		{
			if (fireMode == ALTERNATING)
			{
				coolDown -= Time::deltaTime * fireRate;
			}
			else if (fireMode == SIMULTANEOUSLY)
			{
				coolDown -= Time::deltaTime / BarrelPositions.size() * fireRate;
			}
		}
		if (coolDown < 0)
		{
			coolDown = 0;
		}
	}
	virtual void Shoot(Vector2D direction)
	{
		
		if (BarrelPositions.size() < 1 || coolDown > 0)
			return;
		double PI = 3.141592653589793;
		float rotation = 90 - atan2(direction.GetX(), direction.GetY()) * 180 / PI;
		if (fireMode == ALTERNATING)
		{
			Object::Instantiate(bullet, BarrelPositions[curBarrelIndex], rotation);
			
			curBarrelIndex++;
			if (curBarrelIndex >= BarrelPositions.size())
				curBarrelIndex = 0;
		}
		else if (fireMode == SIMULTANEOUSLY)
		{

		}
		coolDown = 1;
	}
	
};


class DefaultGun : public BaseGun
{
public:
	DefaultGun() : BaseGun()
	{
		bullet = new DefaultBullet();
	}
};*/
class BaseBullet : public Component
{
public:
	float speed = 1;
	float damage = 1;
	static const std::string name;
	BaseBullet(Object * _gameObject) : Component(_gameObject)
	{

	}
	
	std::string GetName()
	{
		return name;
	}
	virtual BaseBullet * Clone(Object * _gameObject) = 0;
};
class DefaultBullet : public BaseBullet
{
public:
	DefaultBullet(Object * _gameObject) : BaseBullet(_gameObject)
	{
		SpriteRenderer * renderer = (SpriteRenderer*)gameObject->AddComponent(new SpriteRenderer(gameObject));
		renderer->sprite = Sprite::SpriteFromFile("romfs:/DefaultBullet.png");
		
	}
	void Start()
	{
		BoxCollider2D * collider = (BoxCollider2D*)gameObject->AddComponent(new BoxCollider2D(gameObject));
		collider->size = Vector2D(.1f, .025f);
		SDL_Log("rotation of bullet is: %f", gameObject->transform.localRotation);
		Destroy(gameObject, 2);
	}
	DefaultBullet * Clone(Object * _gameObject) override
	{
		DefaultBullet * clone = new DefaultBullet(_gameObject);

		return clone;
	}
};
const std::string BaseBullet::name = "BaseBullet";
class BaseGun : public Component
{
protected:
	int curBarrelIndex = 0;
	float coolDown = 0;
public:
	enum FIREMODE
	{
		ALTERNATING,
		SIMULTANEOUSLY,
	};
	std::vector<Vector2D*> BarrelPositions;
	float fireRate = 5;
	FIREMODE fireMode = ALTERNATING;
	BaseBullet * bullet;

	static const std::string name;
	BaseGun(Object * _gameObject) : Component(_gameObject)
	{

	}
	void Update()
	{
		if (BarrelPositions.size() == 0 || coolDown == 0)
			return;
		if (coolDown > 0)
		{
			if (fireMode == ALTERNATING)
			{
				coolDown -= Time::deltaTime * fireRate;
			}
			else if (fireMode == SIMULTANEOUSLY)
			{
				coolDown -= Time::deltaTime / BarrelPositions.size() * fireRate;
			}
		}
		if (coolDown < 0)
		{
			coolDown = 0;
		}
	}
	virtual void Shoot(Vector2D direction)
	{
		if (BarrelPositions.size() < 1 || coolDown > 0)
			return;
		double PI = 3.141592653589793;
		float rotation = 90 - atan2(direction.GetX(), direction.GetY()) * 180 / PI;
		if (fireMode == ALTERNATING)
		{
			SDL_Log("Shooting 3");
			Object * instance = Object::Instantiate(new Object(), *BarrelPositions[curBarrelIndex], rotation);
			instance->AddComponent(bullet->Clone(instance));
			instance->name = "Bullet (clone)";

			curBarrelIndex++;
			if (curBarrelIndex >= BarrelPositions.size())
				curBarrelIndex = 0;
		}
		else if (fireMode == SIMULTANEOUSLY)
		{

		}
		coolDown = 1;
	}
	std::string GetName()
	{
		return name;
	}
};
const std::string BaseGun::name = "BaseGun";
class SingleFireGun : public BaseGun
{
public:

	SingleFireGun(Object * _gameObject) : BaseGun(_gameObject)
	{
		bullet = new DefaultBullet(gameObject);
	}
};
class PlayerController : public Component
{
private:
	int spriteSize = 74;
	Vector2D speed;
	SpriteSheet sheet;
	Animator * animator;
	unsigned int idleAnimIndex, rightAnimIndex, rightRevAnimIndex, leftAnimIndex, leftRevAnimIndex;
	unsigned int idle2AnimIndex, upAnimIndex, upRevAnimIndex, downAnimIndex, downRevAnimIndex;
	unsigned int vToHAnimIndex, hToVAnimIndex;
	bool verticalMode = false;
	bool inTransition = false;
	bool canMove = true;
	bool canShoot = true;
	BaseGun * gun;
	Vector2D barrel1Local;
	Vector2D barrel2Local;
	Vector2D barrel1Position;
	Vector2D barrel2Position;
public:
	static const std::string name;
	PlayerController(Object * _gameObject) : Component(_gameObject), barrel1Local(-0.1f, 0), barrel2Local(0.1f, 0)
	{
		
		speed.Set(4, 4);
		//COLLIDER SETUP
		BoxCollider2D * collider2D = (BoxCollider2D*)gameObject->AddComponent(new BoxCollider2D(gameObject));
		collider2D->size.Set(0.2734375f, 0.578125f);
		collider2D->edgeRadius = 0.09375f;

		//ANIMATION TREE
		SpriteRenderer * renderer = (SpriteRenderer*)gameObject->AddComponent(new SpriteRenderer(gameObject));
		animator = (Animator*)gameObject->AddComponent(new Animator(gameObject));
		sheet = SpriteSheet::FromTileSize("romfs:/Player.png", spriteSize, spriteSize);

		//VERTICAL 

		//IDLE ANIMATION
		Animation idleAnim;
		Key idleKey1;
		idleKey1.sprites.insert(std::pair<Sprite**, Sprite*>(&renderer->sprite, sheet.GetSpriteAt(0, 0)));
		idleKey1.vecs.insert(std::pair<Vector2D*, Vector2D>(&collider2D->size, Vector2D(0.2734375f, 0.578125f)));
		idleAnim.AddKey(0, idleKey1);
		Key idleKey2;
		idleKey2.sprites.insert(std::pair<Sprite**, Sprite*>(&renderer->sprite, sheet.GetSpriteAt(0, 0)));
		idleKey2.vecs.insert(std::pair<Vector2D*, Vector2D>(&collider2D->size, Vector2D(0.2734375f, 0.578125f)));
		idleAnim.AddKey(1, idleKey2);
		idleAnim.SetSamples(2);
		idleAnimIndex = animator->AddAnimation(idleAnim);

		//RIGHT IN ANIMATION
		Animation rightAnim;
		for (int i = 0; i < 6; i++)
		{
			Key rightKey;
			rightKey.sprites.insert(std::pair<Sprite**, Sprite*>(&renderer->sprite, sheet.GetSpriteAt(i, 1)));
			rightAnim.AddKey(i, rightKey);
		}
		rightAnim.SetSamples(60);
		rightAnim.loop = false;
		rightAnimIndex = animator->AddAnimation(rightAnim);

		//RIGHT OUT ANIMATION
		Animation rightRevAnim;
		for (int i = 0; i < 6; i++)
		{
			Key rightRevKey;
			rightRevKey.sprites.insert(std::pair<Sprite**, Sprite*>(&renderer->sprite, sheet.GetSpriteAt(5 - i, 1)));
			rightRevAnim.AddKey(i, rightRevKey);
		}
		rightRevAnim.SetSamples(60);
		rightRevAnim.loop = false;
		rightRevAnimIndex = animator->AddAnimation(rightRevAnim);

		//LEFT IN ANIMATION
		Animation leftAnim;
		for (int i = 0; i < 6; i++)
		{
			Key leftKey;
			leftKey.sprites.insert(std::pair<Sprite**, Sprite*>(&renderer->sprite, sheet.GetSpriteAt(i, 0)));
			leftAnim.AddKey(i, leftKey);
		}
		leftAnim.SetSamples(60);
		leftAnim.loop = false;
		leftAnimIndex = animator->AddAnimation(leftAnim);

		//LEFT OUT ANIMATION
		Animation leftRevAnim;
		for (int i = 0; i < 6; i++)
		{
			Key leftRevKey;
			leftRevKey.sprites.insert(std::pair<Sprite**, Sprite*>(&renderer->sprite, sheet.GetSpriteAt(5 - i, 0)));
			leftRevAnim.AddKey(i, leftRevKey);
		}
		leftRevAnim.SetSamples(60);
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

		//HORIZONTAL

		//IDLE ANIMATION
		Animation idle2Anim;
		Key idle2Key1;
		idle2Key1.sprites.insert(std::pair<Sprite**, Sprite*>(&renderer->sprite, sheet.GetSpriteAt(0, 3)));
		idle2Key1.vecs.insert(std::pair<Vector2D*, Vector2D>(&collider2D->size, Vector2D(0.578125f, 0.15625f)));
		idle2Anim.AddKey(0, idle2Key1);
		Key idle2Key2;
		idle2Key2.sprites.insert(std::pair<Sprite**, Sprite*>(&renderer->sprite, sheet.GetSpriteAt(0, 3)));
		idle2Key2.vecs.insert(std::pair<Vector2D*, Vector2D>(&collider2D->size, Vector2D(0.578125f, 0.15625f)));
		idle2Anim.AddKey(1, idle2Key2);
		idle2Anim.SetSamples(2);
		idle2AnimIndex = animator->AddAnimation(idle2Anim);

		//UP IN ANIMATION
		Animation upAnim;
		for (int i = 0; i < 7; i++)
		{
			Key upKey;
			upKey.sprites.insert(std::pair<Sprite**, Sprite*>(&renderer->sprite, sheet.GetSpriteAt(i, 3)));
			upAnim.AddKey(i, upKey);
		}
		upAnim.SetSamples(60);
		upAnim.loop = false;
		upAnimIndex = animator->AddAnimation(upAnim);

		//UP OUT ANIMATION
		Animation upRevAnim;
		for (int i = 0; i < 7; i++)
		{
			Key upRevKey;
			upRevKey.sprites.insert(std::pair<Sprite**, Sprite*>(&renderer->sprite, sheet.GetSpriteAt(6 - i, 3)));
			upRevAnim.AddKey(i, upRevKey);
		}
		upRevAnim.SetSamples(60);
		upRevAnim.loop = false;
		upRevAnimIndex = animator->AddAnimation(upRevAnim);

		//DOWN IN ANIMATION
		Animation downAnim;
		for (int i = 0; i < 7; i++)
		{
			Key downKey;
			downKey.sprites.insert(std::pair<Sprite**, Sprite*>(&renderer->sprite, sheet.GetSpriteAt(i, 4)));
			downAnim.AddKey(i, downKey);
		}
		downAnim.SetSamples(60);
		downAnim.loop = false;
		downAnimIndex = animator->AddAnimation(downAnim);

		//DOWN OUT ANIMATION
		Animation downRevAnim;
		for (int i = 0; i < 7; i++)
		{
			Key downRevKey;
			downRevKey.sprites.insert(std::pair<Sprite**, Sprite*>(&renderer->sprite, sheet.GetSpriteAt(6 - i, 4)));
			downRevAnim.AddKey(i, downRevKey);
		}
		downRevAnim.SetSamples(60);
		downRevAnim.loop = false;
		downRevAnimIndex = animator->AddAnimation(downRevAnim);

		//UP TRANSITIONS

		//FROM IDLE TO UP IN
		Transition idleToUp(idle2AnimIndex, upAnimIndex);
		idleToUp.hasExitTime = false;
		idleToUp.trigger = "iup";
		animator->AddTransition(idleToUp);

		//FROM UP IN TO UP OUT
		Transition upToUp(upAnimIndex, upRevAnimIndex);
		upToUp.hasExitTime = true;
		upToUp.trigger = "oup";
		animator->AddTransition(upToUp);

		//FROM UP OUT TO IDLE
		Transition upToIdle(upRevAnimIndex, idle2AnimIndex);
		upToIdle.hasExitTime = true;
		upToIdle.trigger = "";
		animator->AddTransition(upToIdle);

		//DOWN TRANSITIONS
		//FROM IDLE TO DOWN IN
		Transition idleToDown(idle2AnimIndex, downAnimIndex);
		idleToDown.hasExitTime = false;
		idleToDown.trigger = "idown";
		animator->AddTransition(idleToDown);

		//FROM DOWN IN TO DOWN OUT
		Transition downToDown(downAnimIndex, downRevAnimIndex);
		downToDown.hasExitTime = true;
		downToDown.trigger = "odown";
		animator->AddTransition(downToDown);

		//FROM DOWN OUT TO IDLE
		Transition downToIdle(downRevAnimIndex, idle2AnimIndex);
		downToIdle.hasExitTime = true;
		downToIdle.trigger = "";
		animator->AddTransition(downToIdle);

		//TRANSITION ANIMATION

		//V TO H ANIMATION
		Animation vToHAnim;
		for (int i = 0; i < 11; i++)
		{
			Key vToHKey;
			vToHKey.sprites.insert(std::pair<Sprite**, Sprite*>(&renderer->sprite, sheet.GetSpriteAt(i, 2)));
			if (i == 10)
			{
				vToHKey.vecs.insert(std::pair<Vector2D*, Vector2D>(&collider2D->size, Vector2D(0.578125f, 0.15625f)));
			}
			else if (i == 0)
			{
				vToHKey.vecs.insert(std::pair<Vector2D*, Vector2D>(&collider2D->size, Vector2D(0.2734375f, 0.578125f)));
			}
			vToHAnim.AddKey(i, vToHKey);
		}
		vToHAnim.SetSamples(30);
		vToHAnim.loop = false;
		vToHAnimIndex = animator->AddAnimation(vToHAnim);

		//H TO V ANIMATION

		Animation hToVAnim;
		for (int i = 0; i < 11; i++)
		{
			Key hToVKey;
			hToVKey.sprites.insert(std::pair<Sprite**, Sprite*>(&renderer->sprite, sheet.GetSpriteAt(10 - i, 2)));
			if (i == 0)
			{
				hToVKey.vecs.insert(std::pair<Vector2D*, Vector2D>(&collider2D->size, Vector2D(0.578125f, 0.15625f)));
			}
			else if (i == 10)
			{
				hToVKey.vecs.insert(std::pair<Vector2D*, Vector2D>(&collider2D->size, Vector2D(0.2734375f, 0.578125f)));
			}
			hToVAnim.AddKey(i, hToVKey);
		}
		hToVAnim.SetSamples(30);
		hToVAnim.loop = false;
		hToVAnimIndex = animator->AddAnimation(hToVAnim);

		//FROM IDLE TO VTOH
		Transition vToHIn(idleAnimIndex, vToHAnimIndex);
		vToHIn.hasExitTime = false;
		vToHIn.trigger = "vtoh";
		animator->AddTransition(vToHIn);

		//FROM VTOH TO IDLE2
		Transition vToHOut(vToHAnimIndex, idle2AnimIndex);
		vToHOut.hasExitTime = true;
		vToHOut.trigger = "";
		animator->AddTransition(vToHOut);

		//FROM HORIZONTAL TO VERTICAL
		Transition hToVIn(idle2AnimIndex, hToVAnimIndex);
		hToVIn.hasExitTime = false;
		hToVIn.trigger = "htov";
		animator->AddTransition(hToVIn);

		Transition hToVOut(hToVAnimIndex, idleAnimIndex);
		hToVOut.hasExitTime = true;
		hToVOut.trigger = "";
		animator->AddTransition(hToVOut);

		
		SDL_Log("Created Player Controller");
	}
	void Start()
	{
		if (!verticalMode)
			animator->OverrideCurrentAnimation(idle2AnimIndex);
		//GUN SETUP
		Object * playerGun = Object::Instantiate(new Object(), Vector2D(0, 0), 0);
		playerGun->transform.parent = &gameObject->transform;
		gun = (BaseGun*)playerGun->AddComponent(new SingleFireGun(playerGun));
		playerGun->name = "PlayerGun";
		gun->BarrelPositions.push_back(&barrel1Position);
		gun->BarrelPositions.push_back(&barrel2Position);
	}
	void UpdateMovement()
	{
		if (inTransition)
		{
			if ((verticalMode && animator->GetCurrentAnimationID() == idle2AnimIndex)
				|| (!verticalMode && animator->GetCurrentAnimationID() == idleAnimIndex))
			{
				verticalMode = !verticalMode;
				inTransition = false;
				EnableMovement();
				EnableShooting();
			}
			else
			{
				if (verticalMode)
					animator->SetTrigger("vtoh");
				else
					animator->SetTrigger("htov");
			}
		}
		//Vertical Stick assigned to Horizontal Movement
		if (abs(Input::GetAxisRaw(Input::AxisCode::AXIS_RSTICK_V)) > 0.02f && canMove)
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
			gameObject->transform.localPosition.SetX(gameObject->transform.localPosition.GetX() + Time::deltaTime * speed.GetX() * val);
		}
		else
		{
			animator->SetTrigger("oright");
			animator->SetTrigger("oleft");
		}
		//Horizontal Stick assigned to Vertical Movement
		if (abs(Input::GetAxisRaw(Input::AxisCode::AXIS_RSTICK_H)) > 0.02f && canMove)
		{
			float val = Input::GetAxisRaw(Input::AxisCode::AXIS_RSTICK_H);
			if (val > 0)
			{
				animator->SetTrigger("odown");
				animator->SetTrigger("iup");
			}
			else if (val < 0)
			{
				animator->SetTrigger("oup");
				animator->SetTrigger("idown");
			}
			gameObject->transform.localPosition.SetY(gameObject->transform.localPosition.GetY() + Time::deltaTime * speed.GetY() * val);
		}
		else
		{
			animator->SetTrigger("oup");
			animator->SetTrigger("odown");
		}
		if (Input::GetKeyDown(Input::KeyCode::NX_Y))
		{
			ToggleMode();
		}
	}
	void UpdateGun()
	{
		if (!canShoot)return;
		if (Input::GetKey(Input::KeyCode::NX_X))
		{
			Vector2D direction(1, 0);
			if (verticalMode)
			{
				direction = Vector2D(0, 1);
			}
			barrel1Position = gameObject->transform.GetGlobalPosition() + barrel1Local;
			barrel2Position = gameObject->transform.GetGlobalPosition() + barrel2Local;
			gun->Shoot(direction);
		}
	}
	void Update()
	{
		UpdateMovement();
		UpdateGun();
	}
	void ToggleMode()
	{
		inTransition = true;
		DisableMovement();
		DisableShooting();
	}
	void DisableMovement()
	{
		canMove = false;
	}
	void EnableMovement()
	{
		if (!inTransition)
			canMove = true;
	}
	void DisableShooting()
	{
		canShoot = false;
	}
	void EnableShooting()
	{
		canShoot = true;
	}
	std::string GetName()
	{
		return name;
	}
};
const std::string PlayerController::name = "PlayerController";

class TestScene : public Scene
{
public:
	bool Init()
	{
		_stateName = "TestScene";
		Object * player = Object::Instantiate(new Object(), Vector2D(0, 0), 0);
		player->AddComponent(new PlayerController(player));
		player->name = "Player";
		player->layer = 999;
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