#include "MiniginPCH.h"
#include "Components.h"
#include "ServiceLocator.h"
#include "GameObject.h"

void dae::RenderComponent::onNotify(GameObject& , NotifyEvent& )
{
}

void dae::RenderComponent::Initialize()
{
	m_pTextureComponent = GetGameObject()->GetComponent<TextureComponent>().get();
	m_pTransformComponent = GetGameObject()->GetComponent<TransformComponent>().get();
	m_pSpriteComponent = GetGameObject()->GetComponent<SpriteComponent>().get();
}

void dae::RenderComponent::Update(float)
{
}

void dae::RenderComponent::Render() const
{
	if(m_Render)
	{
		if (m_pTextureComponent != nullptr && m_pTransformComponent != nullptr)
			if (m_pTextureComponent->GetTexture())
			{
				auto flip = SDL_FLIP_NONE;
				if (m_pSpriteComponent)
				{
					flip = m_pSpriteComponent->GetFlipSprite();
					auto x = m_pSpriteComponent->GetCurrentUV().x;
					ServiceLocator::GetRenderer()->RenderSprite(*m_pTextureComponent->GetTexture(), m_pTransformComponent->GetPosition().x, m_pTransformComponent->GetPosition().y, static_cast<float>(x), static_cast<float>(m_pSpriteComponent->GetCurrentUV().y), static_cast<float>(m_pSpriteComponent->GetCurrentUV().w), static_cast<float>(m_pSpriteComponent->GetCurrentUV().h), flip);
				}
				else
				{
					ServiceLocator::GetRenderer()->RenderTexture(*m_pTextureComponent->GetTexture(), m_pTransformComponent->GetPosition().x, m_pTransformComponent->GetPosition().y, static_cast<float>(m_pTextureComponent->GetSize().x), static_cast<float>(m_pTextureComponent->GetSize().y), flip);
				}
			}

		////TODO: UPDATE TILE DEBUG TEXTURES WITH TILE TEXTURE FUNCTIONS
		//if (m_pTileComponent != nullptr && m_pTransformComponent != nullptr)
		//{
		//	if (m_pTileComponent->GetTileState() == TileState::USED)
		//	{
		//		const auto Hwall = ServiceLocator::GetResourceManager()->GetTexture(10002);

		//		const auto Vwall = ServiceLocator::GetResourceManager()->GetTexture(10004);

		//		if (!m_pTileComponent->GetIsConnectedBorder(Direction::UP))
		//			ServiceLocator::GetRenderer()->RenderTexture(*Hwall, m_pTransformComponent->GetPosition().x, m_pTransformComponent->GetPosition().y, 32.0f, 5.0f);


		//		if (!m_pTileComponent->GetIsConnectedBorder(Direction::DOWN))
		//			ServiceLocator::GetRenderer()->RenderTexture(*Hwall, m_pTransformComponent->GetPosition().x, m_pTransformComponent->GetPosition().y + 32 - 5, 32.0f, 5.0f);


		//		if (!m_pTileComponent->GetIsConnectedBorder(Direction::LEFT))
		//			ServiceLocator::GetRenderer()->RenderTexture(*Vwall, m_pTransformComponent->GetPosition().x, m_pTransformComponent->GetPosition().y, 5.0f, 32.0f);


		//		if (!m_pTileComponent->GetIsConnectedBorder(Direction::RIGHT))
		//			ServiceLocator::GetRenderer()->RenderTexture(*Vwall, m_pTransformComponent->GetPosition().x + 32 - 5, m_pTransformComponent->GetPosition().y, 5.0f, 32.0f);
		//	}
		//}

		/*if (m_pCollisionComponent != nullptr && m_pTransformComponent != nullptr)
		{
			if (m_pCollisionComponent->ShowCollisionBox())
			{
				const auto Collision = ServiceLocator::GetResourceManager()->GetTexture(10000);
				ServiceLocator::GetRenderer()->RenderSprite(*Collision, m_pCollisionComponent->GetPosition().x, m_pCollisionComponent->GetPosition().y, 0, 0, static_cast<float>(m_pCollisionComponent->GetSize().x), static_cast<float>(m_pCollisionComponent->GetSize().y));
			}
		}*/
	}
}
