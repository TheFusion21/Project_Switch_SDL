#ifndef CAMERA_H
#define CAMERA_H
#include "Rect.h"
class Camera
{
public:
	float orthographicSize;
	float pixelPerUnit;
	Rect viewportRect;
	Camera();
	Camera(Rect viewportRect);
	Vector2D WorldToScreenPoint(Vector2D pos);
};
#endif