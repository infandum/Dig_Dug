#include "MiniginPCH.h"
#include "GameObject.h"
#include "Renderer.h"
#include "Components.h"
#include <complex>
#include "ServiceLocator.h"

unsigned int dae::GameObject::m_NumberOfGameObjects = 0;

dae::GameObject::GameObject(): m_pTransformComponent(nullptr), m_pTextureComponent(nullptr),
                               m_pCollisionComponent(nullptr), m_pTileComponent(nullptr)
{
	++m_NumberOfGameObjects;
}

void dae::GameObject::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	for (auto& component : m_pComponents)
	{
		component->Update(deltaTime);
	}
}

void dae::GameObject::Render() const
{
	if (m_pTextureComponent != nullptr && m_pTransformComponent != nullptr)
		if(m_pTextureComponent->GetTexture())
		{
			auto flip = SDL_FLIP_NONE;
			if (GetSprite())
			{ 
				flip = GetSprite()->GetFlipSprite();
				auto x = GetSprite()->GetCurrentUV().x;
				ServiceLocator::GetRenderer()->RenderSprite(*m_pTextureComponent->GetTexture(), m_pTransformComponent->GetPosition().x, m_pTransformComponent->GetPosition().y, static_cast<float>(x), static_cast<float>(GetSprite()->GetCurrentUV().y), static_cast<float>(GetSprite()->GetCurrentUV().w), static_cast<float>(GetSprite()->GetCurrentUV().h), flip);
			}
			else
			{
				ServiceLocator::GetRenderer()->RenderTexture(*m_pTextureComponent->GetTexture(), m_pTransformComponent->GetPosition().x, m_pTransformComponent->GetPosition().y, (float)(m_pTextureComponent->GetSize().x), (float)(m_pTextureComponent->GetSize().y), flip);
			}
		}
	
	if (m_pTileComponent != nullptr && m_pTransformComponent != nullptr)
	{
		if (m_pTileComponent->GetTileState() == TileState::DUG)
		{
			const auto Hwall = ServiceLocator::GetResourceManager()->GetTexture(10002);

			const auto Vwall = ServiceLocator::GetResourceManager()->GetTexture(10004);

			if(!m_pTileComponent->GetBorder(Direction::UP))
				ServiceLocator::GetRenderer()->RenderTexture(*Hwall, m_pTransformComponent->GetPosition().x, m_pTransformComponent->GetPosition().y, 32.0f, 5.0f);
			

			if (!m_pTileComponent->GetBorder(Direction::DOWN))
				ServiceLocator::GetRenderer()->RenderTexture(*Hwall, m_pTransformComponent->GetPosition().x, m_pTransformComponent->GetPosition().y + 32 - 5, 32.0f, 5.0f);
			

			if (!m_pTileComponent->GetBorder(Direction::LEFT))
				ServiceLocator::GetRenderer()->RenderTexture(*Vwall, m_pTransformComponent->GetPosition().x, m_pTransformComponent->GetPosition().y, 5.0f, 32.0f);
			

			if (!m_pTileComponent->GetBorder(Direction::RIGHT))
				ServiceLocator::GetRenderer()->RenderTexture(*Vwall, m_pTransformComponent->GetPosition().x + 32 - 5, m_pTransformComponent->GetPosition().y, 5.0f, 32.0f);
		}
	}

	if (m_pCollisionComponent != nullptr && m_pTransformComponent != nullptr)
	{
		if(m_pCollisionComponent->ShowCollisionBox())
		{
			const auto Collision = ServiceLocator::GetResourceManager()->GetTexture(10000);
			ServiceLocator::GetRenderer()->RenderTexture(*Collision, m_pCollisionComponent->GetPosition().x, m_pCollisionComponent->GetPosition().y, static_cast<float>(m_pCollisionComponent->GetSize().x), static_cast<float>(m_pCollisionComponent->GetSize().y));
		}
	}
}

void dae::GameObject::SetName(std::string name)
{
	m_Name = name;
}

void dae::GameObject::AddComponent(std::shared_ptr<BaseComponent> comp)
{
	for (auto& component : m_pComponents)
	{ 
		if (typeid(*component) == typeid(*comp))
		{
			std::cout << "Component Duplicate: " << typeid(*comp).name() << " >> Already added!!"; 
			return;
		}
	}
	m_pComponents.push_back(comp);
	/*std::shared_ptr<GameObject> owner;
	owner.reset(this);*/
	comp->m_pGameObject = this;

	for (auto& component : m_pComponents)
	{
		if (component && typeid(*component) == typeid(TransformComponent) && m_pTransformComponent == nullptr)
			m_pTransformComponent = std::static_pointer_cast<TransformComponent>(component);

		if (component && typeid(*component) == typeid(TextureComponent) && m_pTextureComponent == nullptr)
			m_pTextureComponent = std::static_pointer_cast<TextureComponent>(component);

		if (component && typeid(*component) == typeid(TileComponent) && m_pTileComponent == nullptr)
			m_pTileComponent = std::static_pointer_cast<TileComponent>(component);

		if (component && typeid(*component) == typeid(CollisionComponent) && m_pCollisionComponent == nullptr)
			m_pCollisionComponent = std::static_pointer_cast<CollisionComponent>(component);

		if (component && typeid(*component) == typeid(SpriteComponent) && m_pSpriteComponent == nullptr)
			m_pSpriteComponent = std::static_pointer_cast<SpriteComponent>(component);

		if (component && typeid(*component) == typeid(InputComponent) && m_pInputComponent == nullptr)
			m_pInputComponent = std::static_pointer_cast<InputComponent>(component);
	}
}

void dae::GameObject::RemoveComponent(std::shared_ptr<BaseComponent> pComp)
{
	const auto comp = std::find(m_pComponents.begin(), m_pComponents.end(), pComp);
	if (comp == m_pComponents.end())
	{
		std::wcout << L"GameObject::RemoveComponent > Component is not attached to this GameObject!" << std::endl;
		return;
	}
	m_pComponents.erase(comp);
	pComp->m_pGameObject = nullptr;
}