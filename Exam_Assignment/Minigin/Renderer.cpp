#include "MiniginPCH.h"
#include "Renderer.h"
#include <SDL.h>
#include "Texture2D.h"
#include "ServiceLocator.h"

void dae::Renderer::Init(SDL_Window * window)
{
	mRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (mRenderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}
}

void dae::Renderer::Render()
{
	SDL_RenderClear(mRenderer);

	ServiceLocator::GetSceneManager()->Render();
	
	SDL_RenderPresent(mRenderer);
}

void dae::Renderer::Destroy()
{
	if (mRenderer != nullptr)
	{
		SDL_DestroyRenderer(mRenderer);
		mRenderer = nullptr;
	}
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, SDL_RendererFlip flip) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst, 0, nullptr, flip);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height, SDL_RendererFlip flip) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst, 0, nullptr, flip);
}

void dae::Renderer::RenderSprite(const Texture2D& texture, float x, float y, float U, float V, float width, float height, SDL_RendererFlip flip) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x - U);// + 16;
	dst.y = static_cast<int>(y - V);// + 16;
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_Rect clip;
	clip.x = dst.x + static_cast<int>(U);// - 32;
	clip.y = dst.y + static_cast<int>(V);// - 32;
	clip.w = static_cast<int>(width);
	clip.h = static_cast<int>(height);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderSetClipRect(GetSDLRenderer(), &clip);
	SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst, 0, nullptr, flip);
	SDL_RenderSetClipRect(GetSDLRenderer(), nullptr);
}
