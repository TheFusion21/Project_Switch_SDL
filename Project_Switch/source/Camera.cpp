#include "Camera.h"
#include "GameManager.h"
Camera::Camera() : viewportRect(0, 0, 1, 1), orthographicSize(2), pixelPerUnit(128)
{

}

Camera::Camera(Rect viewportRect) : viewportRect(viewportRect)
{

}

Vector2D Camera::WorldToScreenPoint(Vector2D inPos)
{
	float worldHeight = orthographicSize * 2.f;
	float worldWidth = worldHeight * GameManager::instance().GetRatio();
	Vector2D worldPos(((inPos.GetX() / worldWidth) + .5f)*GameManager::instance().GetSize().GetX(), ((-inPos.GetY() / worldHeight) + .5f)*GameManager::instance().GetSize().GetY());
	return worldPos;
}

