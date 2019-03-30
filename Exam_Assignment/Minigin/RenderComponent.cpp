#include "MiniginPCH.h"
#include "Components.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "GameObject.h"
#include "Texture2D.h"
void dae::RenderComponent::Draw(float& deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	if (GetGameObject()->GetComponent<TextureComponent>())
		if (GetGameObject()->GetComponent<TransformComponent>())
	Renderer::GetInstance().RenderTexture(*GetGameObject()->GetComponent<TextureComponent>()->GetTexture(), GetGameObject()->GetComponent<TransformComponent>()->GetPosition().x, GetGameObject()->GetComponent<TransformComponent>()->GetPosition().y);
}

//void dae::RenderComponent::RenderTexture(const Texture2D& texture, const float x, const float y) const
//{
//	/*SDL_Rect dst;
//	dst.x = static_cast<int>(x);
//	dst.y = static_cast<int>(y);
//	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
//	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);*/
//}

//void dae::RenderComponent::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
//{
//	/*SDL_Rect dst;
//	dst.x = static_cast<int>(x);
//	dst.y = static_cast<int>(y);
//	dst.w = static_cast<int>(width);
//	dst.h = static_cast<int>(height);
//	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);*/
//}