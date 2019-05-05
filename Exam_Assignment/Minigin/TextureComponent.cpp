#include "MiniginPCH.h"
#include "Components.h"

dae::TextureComponent::TextureComponent(std::shared_ptr<Texture2D> texture)
	: m_spTexture(nullptr)
{
	SetTexture(texture);
}

void dae::TextureComponent::SetTexture(std::shared_ptr<Texture2D> texture)
{
	m_spTexture = texture;
	SDL_QueryTexture(m_spTexture->GetSDLTexture(), nullptr, nullptr, &m_Size.x, &m_Size.y);
}

void dae::TextureComponent::Initialize()
{
}

void dae::TextureComponent::Update(float )
{

}