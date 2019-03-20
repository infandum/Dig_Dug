#include "MiniginPCH.h"
#include "TextureComponent.h"
#include <SDL.h>
#include "ResourceManager.h"

dae::TextureComponent::TextureComponent(const std::string& filename) : m_spTexture(nullptr)
{
	m_spTexture = ResourceManager::GetInstance().LoadTexture(filename);
}

dae::TextureComponent::TextureComponent(std::shared_ptr<Texture2D> texture): m_spTexture(nullptr)
{
	m_spTexture = texture;
}

void dae::TextureComponent::SetTexture(const std::string& filename)
{
	m_spTexture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::TextureComponent::SetTexture(std::shared_ptr<Texture2D> texture)
{
	m_spTexture = texture;
}