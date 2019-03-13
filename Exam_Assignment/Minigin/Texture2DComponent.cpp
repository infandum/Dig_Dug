#include "MiniginPCH.h"
#include "Texture2DComponent.h"
#include <SDL.h>

SDL_Texture* Texture2DComponent::GetSDLTexture() const
{
	return mTexture;
}

Texture2DComponent::Texture2DComponent(SDL_Texture* texture)
{
	mTexture = texture;
}

Texture2DComponent::~Texture2DComponent()
{
	SDL_DestroyTexture(mTexture);
}
