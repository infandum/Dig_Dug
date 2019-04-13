#include "MiniginPCH.h"
#include "Components.h"

dae::TextureComponent::TextureComponent(std::shared_ptr<Texture2D> texture)
	: m_spTexture(nullptr)
{
	m_spTexture = texture;
	SDL_QueryTexture(m_spTexture->GetSDLTexture(), nullptr, nullptr, &m_size.x, &m_size.y);
}

void dae::TextureComponent::SetTexture(std::shared_ptr<Texture2D> texture, int width, int heigth)
{
	m_spTexture = texture;
	SDL_QueryTexture(m_spTexture->GetSDLTexture(), nullptr, nullptr, &m_size.x, &m_size.y);
	if (width || heigth != 0)
	{
		m_size.x = width;
		m_size.y = heigth;
	}
}

void dae::TextureComponent::Update(float& deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}
