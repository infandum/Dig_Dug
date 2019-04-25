#pragma once
#include "Service.h"
#include <SDL.h>

struct SDL_Window;
struct SDL_Renderer;

namespace dae
{
	class Texture2D;
	class Renderer final : public Service
	{
		SDL_Renderer* mRenderer = nullptr;

	public:
		void Init(SDL_Window* window);
		void Render();
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y, SDL_RendererFlip flip = SDL_FLIP_NONE) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height, SDL_RendererFlip flip = SDL_FLIP_NONE) const;
		void RenderSprite(const Texture2D& texture, float x, float y, float U, float V, float width, float height, SDL_RendererFlip flip = SDL_FLIP_NONE) const;

		SDL_Renderer* GetSDLRenderer() const { return mRenderer; }
	};
}

