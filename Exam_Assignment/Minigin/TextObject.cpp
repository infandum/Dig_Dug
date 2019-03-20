#include "MiniginPCH.h"
#include <SDL.h>
#include <SDL_ttf.h>

#include "TextObject.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "Components.h"

dae::TextObject::TextObject(const std::string& text, std::shared_ptr<Font> font) 
	: mNeedsUpdate(true), mText(text), mFont(font), mTexture(nullptr)
{ }

void dae::TextObject::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	if (mNeedsUpdate)
	{
		const SDL_Color color = { 255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(mFont->GetFont(), mText.c_str(), color);
		if (surf == nullptr) 
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr) 
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		mTexture = std::make_shared<Texture2D>(texture);
	}
}

void dae::TextObject::Render() const
{
	if (mTexture != nullptr)
	{
		const auto pos = mTransform.GetPosition();
		Renderer::GetInstance().RenderTexture(*mTexture, pos.x, pos.y);
	}
}

void dae::TextObject::SetText(const std::string& text)
{
	mText = text;
	mNeedsUpdate = true;
}

void dae::TextObject::SetPosition(const float x, const float y)
{
	mTransform.SetPosition(x, y, 0.0f);
}

//void dae::TextObject::AddComponent(BaseComponent* pComp)
//{
//	m_pComponents.push_back(pComp);
//	pComp->m_pTextObject = this;
//}
//
//void dae::TextObject::RemoveComponent(BaseComponent* pComp)
//{
//	auto comp = std::find(m_pComponents.begin(), m_pComponents.end(), pComp);
//	if (comp == m_pComponents.end())
//	{
//		std::wcout << L"GameObject::RemoveComponent > Component is not attached to this GameObject!" << std::endl;
//		return;
//	}
//	m_pComponents.erase(comp);
//	pComp->m_pTextObject = nullptr;
//}