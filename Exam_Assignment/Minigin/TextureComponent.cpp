#include "MiniginPCH.h"
#include "Components.h"

dae::TextureComponent::TextureComponent(std::shared_ptr<Texture2D> texture)
	: m_spTexture(nullptr)
{
	m_spTexture = texture;
	SDL_QueryTexture(m_spTexture->GetSDLTexture(), nullptr, nullptr, &m_Size.x, &m_Size.y);
}

void dae::TextureComponent::SetTexture(std::shared_ptr<Texture2D> texture, int width, int height)
{
	m_spTexture = texture;
	SDL_QueryTexture(m_spTexture->GetSDLTexture(), nullptr, nullptr, &m_Size.x, &m_Size.y);
	UNREFERENCED_PARAMETER(width);
	UNREFERENCED_PARAMETER(height);
	//if (width || height != 32)
	//{
	//m_Size.x = width;
	//m_Size.y = height;
	//}
}

void dae::TextureComponent::Update(float& deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}
