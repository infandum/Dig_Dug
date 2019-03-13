#pragma once
#include "BaseComponent.h"
struct SDL_Texture;

class Texture2DComponent :
	public BaseComponent
{
public:
	Texture2DComponent(const Texture2DComponent& other) = delete;
	Texture2DComponent(Texture2DComponent&& other) noexcept = delete;
	Texture2DComponent& operator=(const Texture2DComponent& other) = delete;
	Texture2DComponent& operator=(Texture2DComponent&& other) noexcept = delete;

	SDL_Texture* GetSDLTexture() const;
	explicit Texture2DComponent(SDL_Texture* texture);
	~Texture2DComponent();

private:
	SDL_Texture* mTexture;
};

