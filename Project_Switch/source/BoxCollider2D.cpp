#include "BoxCollider2D.h"
#include "GameManager.h"
#include "Object.h"
#include "Structs.h"
#include "SDL_Extension.h"
const std::string BoxCollider2D::name = "Box Collider2D";

BoxCollider2D::BoxCollider2D(Object * _gameObject) : Collider2D(_gameObject), edgeRadius(0)
{

}

void BoxCollider2D::Render()
{
	if (Debug::showCollider)
	{
		float rot = gameObject->transform.localRotation;
		SDL_Renderer * g_renderer = GameManager::instance().GetRenderer();
		Vector2D worldPos = GameManager::instance().camera.WorldToScreenPoint(gameObject->transform.localPosition + offset);
		SDL_Rect dst_rect =
		{
			worldPos.GetX() - size.GetX() * GameManager::instance().camera.pixelPerUnit * gameObject->transform.anchor.GetX() * gameObject->transform.scale.GetX(),
			worldPos.GetY() - size.GetY() * GameManager::instance().camera.pixelPerUnit * gameObject->transform.anchor.GetY() * gameObject->transform.scale.GetY(),
			size.GetX() * GameManager::instance().camera.pixelPerUnit * gameObject->transform.scale.GetX(),
			size.GetY() * GameManager::instance().camera.pixelPerUnit * gameObject->transform.scale.GetY()
		};
		int pixelRadius = edgeRadius * GameManager::instance().camera.pixelPerUnit;
		SDL_SetRenderDrawColor(g_renderer, Debug::colliderColor.r * 255, Debug::colliderColor.g * 255, Debug::colliderColor.b * 255, Debug::colliderColor.a * 255);
		//TOP LINE
		SDL_RenderDrawLine(g_renderer, dst_rect.x + pixelRadius, dst_rect.y, dst_rect.x + dst_rect.w - pixelRadius, dst_rect.y);
		//LEFT LINE
		SDL_RenderDrawLine(g_renderer, dst_rect.x, dst_rect.y + pixelRadius, dst_rect.x, dst_rect.y + dst_rect.h - pixelRadius);
		//BOTTOM LINE
		SDL_RenderDrawLine(g_renderer, dst_rect.x + pixelRadius, dst_rect.y + dst_rect.h, dst_rect.x + dst_rect.w - pixelRadius, dst_rect.y + dst_rect.h);
		//RIGHT LINE
		SDL_RenderDrawLine(g_renderer, dst_rect.x + dst_rect.w, dst_rect.y + pixelRadius, dst_rect.x + dst_rect.w, dst_rect.y + dst_rect.h - pixelRadius);

		if (pixelRadius > 1)
		{
			//TOP LEFT ARC
			SDL_Extension::SDL_RenderArc(g_renderer, dst_rect.x + pixelRadius, dst_rect.y + pixelRadius, pixelRadius, 180, 270);
			//TOP RIGHT ARC
			SDL_Extension::SDL_RenderArc(g_renderer, dst_rect.x + dst_rect.w - pixelRadius, dst_rect.y + pixelRadius, pixelRadius, 270, 0);
			//BOTTOM RIGHT ARC
			SDL_Extension::SDL_RenderArc(g_renderer, dst_rect.x + dst_rect.w - pixelRadius, dst_rect.y + dst_rect.h - pixelRadius, pixelRadius, 0, 90);
			//BOTTOM LEFT ARC
			SDL_Extension::SDL_RenderArc(g_renderer, dst_rect.x + pixelRadius, dst_rect.y + dst_rect.h - pixelRadius, pixelRadius, 90, 180);
		}
	}
}

Vector2D BoxCollider2D::GetCenterPoint()
{
	return GameManager::instance().camera.WorldToScreenPoint(gameObject->transform.localPosition + offset);
}

Vector2D BoxCollider2D::GetClosestPoint(Vector2D pos)
{
	return Vector2D();
}

Rect BoxCollider2D::GetBoundingBox()
{
	Rect rect;
	/*Vector2D center = GetCenterPoint();
	SDL_Rect dst_rect =
	{
		center.GetX() - size.GetX() * GameManager::instance().camera.pixelPerUnit * gameObject->transform.anchor.GetX() * gameObject->transform.scale.GetX(),
		center.GetY() - size.GetY() * GameManager::instance().camera.pixelPerUnit * gameObject->transform.anchor.GetY() * gameObject->transform.scale.GetY(),
		size.GetX() * GameManager::instance().camera.pixelPerUnit * gameObject->transform.scale.GetX(),
		size.GetY() * GameManager::instance().camera.pixelPerUnit * gameObject->transform.scale.GetY()
	};
	int pixelRadius = edgeRadius * GameManager::instance().camera.pixelPerUnit;
	rect.Set(dst_rect.x - pixelRadius, dst_rect.y - pixelRadius, dst_rect.w + pixelRadius * 2, dst_rect.h + pixelRadius * 2);*/
	return rect;
}
