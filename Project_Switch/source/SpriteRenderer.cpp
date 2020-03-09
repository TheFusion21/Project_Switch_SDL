#include "SpriteRenderer.h"
#include "GameManager.h"
#include "Object.h"

#include "SDL2/SDL_opengl.h"
#include "SDL2/SDL_opengl_glext.h"
const std::string SpriteRenderer::name = "Sprite Renderer";
SpriteRenderer::SpriteRenderer(Object* _gameObject) : Renderer(_gameObject)
{
	
}

void SpriteRenderer::Render()
{
	SDL_Renderer * g_renderer = GameManager::instance().GetRenderer();
	
	//https://github.com/AugustoRuiz/sdl2glsl/blob/master/src/main.cpp
	if (sprite == nullptr)return;
	if (!enabled || sprite->src_Texture == nullptr)return;
	//SDL_RenderCopy(Globals::renderer, tex, &srcRect, &dstRect);
	Vector2D worldPos = GameManager::instance().camera.WorldToScreenPoint(gameObject->transform.GetGlobalPosition());
	SDL_Rect dst_rect =
	{
		worldPos.GetX() - sprite->src_rect.w * gameObject->transform.anchor.GetX() * gameObject->transform.scale.GetX(),
		worldPos.GetY() - sprite->src_rect.h * gameObject->transform.anchor.GetY() * gameObject->transform.scale.GetY(),
		sprite->src_rect.w * gameObject->transform.scale.GetX(),
		sprite->src_rect.h * gameObject->transform.scale.GetY()
	};
	SDL_Point center = {sprite->src_rect.w*gameObject->transform.anchor.GetX(), sprite->src_rect.h*gameObject->transform.anchor.GetY() };
	SDL_RendererFlip flip = (SDL_RendererFlip)((flipX ? SDL_RendererFlip::SDL_FLIP_VERTICAL : SDL_RendererFlip::SDL_FLIP_NONE) | (flipY ? SDL_RendererFlip::SDL_FLIP_HORIZONTAL : SDL_RendererFlip::SDL_FLIP_NONE));
	SDL_RenderCopyEx(g_renderer, sprite->src_Texture, &sprite->src_rect, &dst_rect, gameObject->transform.localRotation, &center, flip);
}
