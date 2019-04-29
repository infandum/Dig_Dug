#include "MiniginPCH.h"
#include "Components.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include "Font.h"
#include "GameObject.h"
#include "Texture2D.h"
#include "Renderer.h"
#include "ServiceLocator.h"

dae::TextComponent::TextComponent(const std::string& text, std::shared_ptr<Font> font)
	: m_NeedsUpdate(true), m_Text(text), mFont(font)
{
	
}

void dae::TextComponent::Update(float& deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	if (m_NeedsUpdate)
	{
		const auto surf = TTF_RenderText_Blended(mFont->GetFont(), m_Text.c_str(), m_Color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(ServiceLocator::GetRenderer()->GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		if (GetGameObject()->GetComponent<TextureComponent>())
			GetGameObject()->GetComponent<TextureComponent>()->SetTexture(std::make_shared<Texture2D>(texture));
	}
}

void dae::TextComponent::Render()
{
}

void dae::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void dae::TextComponent::SetColor(const SDL_Color& color)
{
	m_Color = color;
	m_NeedsUpdate = true;
}
