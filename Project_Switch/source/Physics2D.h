#ifndef PHYSICS2D_H
#define PHYSICS2D_H
#include "Vector2D.h"
class Physics2D
{
private:
	Physics2D();
protected:
	friend class Scene;
	static Physics2D &instance();
	void Update();

public:
	static int velocityIterations;
	static int positionIterations;
	static Vector2D gravity;

};
#endif