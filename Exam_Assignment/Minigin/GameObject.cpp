#include "MiniginPCH.h"
#include "GameObject.h"
#include "Renderer.h"
#include "Components.h"
#include <complex>
#include "ServiceLocator.h"

UINT dae::GameObject::m_NumberOfGameObjects = 0;

dae::GameObject::GameObject(): m_pTransformComponent(nullptr), m_pTextureComponent(nullptr),
                               m_pCollisionComponent(nullptr), m_pTileComponent(nullptr)
{
	++m_NumberOfGameObjects;
}

void dae::GameObject::Update(float deltaTime)
{
	for (size_t i = 0; i < m_pChilds.size(); i++)
	{
		if (m_IsChildActive[i])
			m_pChilds[i]->Update(deltaTime);
	}

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
				ServiceLocator::GetRenderer()->RenderTexture(*m_pTextureComponent->GetTexture(), m_pTransformComponent->GetPosition().x, m_pTransformComponent->GetPosition().y, static_cast<float>(m_pTextureComponent->GetSize().x), static_cast<float>(m_pTextureComponent->GetSize().y), flip);
			}
		}
	
	if (m_pTileComponent != nullptr && m_pTransformComponent != nullptr)
	{
		if (m_pTileComponent->GetTileState() == TileState::USED)
		{
			const auto Hwall = ServiceLocator::GetResourceManager()->GetTexture(10002);

			const auto Vwall = ServiceLocator::GetResourceManager()->GetTexture(10004);

			if(!m_pTileComponent->GetIsConnectedBorder(Direction::UP))
				ServiceLocator::GetRenderer()->RenderTexture(*Hwall, m_pTransformComponent->GetPosition().x, m_pTransformComponent->GetPosition().y, 32.0f, 5.0f);
			

			if (!m_pTileComponent->GetIsConnectedBorder(Direction::DOWN))
				ServiceLocator::GetRenderer()->RenderTexture(*Hwall, m_pTransformComponent->GetPosition().x, m_pTransformComponent->GetPosition().y + 32 - 5, 32.0f, 5.0f);
			

			if (!m_pTileComponent->GetIsConnectedBorder(Direction::LEFT))
				ServiceLocator::GetRenderer()->RenderTexture(*Vwall, m_pTransformComponent->GetPosition().x, m_pTransformComponent->GetPosition().y, 5.0f, 32.0f);
			

			if (!m_pTileComponent->GetIsConnectedBorder(Direction::RIGHT))
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

	for(size_t i = 0; i < m_pChilds.size(); i++)
	{
		if (m_IsChildActive[i])
			m_pChilds[i]->Render();
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

		if (component && typeid(*component) == typeid(NpcComponent) && m_pNpcComponent == nullptr)
			m_pNpcComponent = std::static_pointer_cast<NpcComponent>(component);
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

void dae::GameObject::AddChild(std::shared_ptr<GameObject> pChild, bool isActive, bool isAttached)
{
	for (auto& child : m_pChilds)
	{
		if (typeid(*child) == typeid(*pChild))
		{
			std::cout << "Component Duplicate: " << typeid(*child).name() << " >> Already added!!";
			return;
		}
	}
	pChild->SetParent(this);
	pChild->GetTransform()->SetLocalPosition(pChild->GetTransform()->GetPosition().x - GetTransform()->GetPosition().x, pChild->GetTransform()->GetPosition().y - GetTransform()->GetPosition().y, pChild->GetTransform()->GetPosition().z - GetTransform()->GetPosition().z);
	m_IsChildAttached.push_back(isAttached);
	m_IsChildActive.push_back(isActive);
	m_pChilds.push_back(pChild);
}

void dae::GameObject::RemoveChild(std::shared_ptr<GameObject> pChild)
{
	const auto child = std::find(m_pChilds.begin(), m_pChilds.end(), pChild);
	if (child == m_pChilds.end())
	{
		std::wcout << L"GameObject::RemoveComponent > Component is not attached to this GameObject!" << std::endl;
		return;
	}
	const auto it = m_IsChildAttached.begin() + (child - m_pChilds.begin());
	m_pChilds.erase(child);
	m_IsChildAttached.erase(it);
	pChild->SetParent(nullptr);
}

bool dae::GameObject::IsChild(GameObject* pChild)
{
	if (m_pChilds.size() == 0)
		return false;

	for (UINT i = 0; i < m_pChilds.size(); i++)
	{
		if (m_pChilds[i].get() == pChild)
		{
			return true;
		}
	}
	return false;
}

std::shared_ptr<dae::GameObject> dae::GameObject::GetChild(UINT index)
{
	if(m_pChilds.size() == 0)
		return nullptr;

	for (UINT i = 0; i < m_pChilds.size(); i++)
	{
		if (i == index)
		{
			return m_pChilds[i];
		}
	}
	return nullptr;
}

void dae::GameObject::DetachChild(GameObject* pChild)
{
	if (m_pChilds.size() == 0)
		return;

	for (size_t i = 0; i < m_pChilds.size(); i++)
	{
		if (m_pChilds[i].get() == pChild)
		{
			m_IsChildAttached[i] = false;
			return;
		}
	}
}

void dae::GameObject::AttachChild(GameObject* pChild)
{
	if (m_pChilds.size() == 0)
		return;

	for (size_t i = 0; i < m_pChilds.size(); i++)
	{
		if (m_pChilds[i].get() == pChild)
		{
			m_IsChildAttached[i] = true;
			pChild->GetTransform()->SetLocalPosition(pChild->GetTransform()->GetPosition().x - GetTransform()->GetPosition().x, pChild->GetTransform()->GetPosition().y - GetTransform()->GetPosition().y, pChild->GetTransform()->GetPosition().z - GetTransform()->GetPosition().z);
			return;
		}
	}
}

bool dae::GameObject::IsChildAttached(GameObject* pChild)
{
	if (m_pChilds.size() == 0)
		return false;

	for (size_t i = 0; i < m_pChilds.size(); i++)
	{
		if (m_pChilds[i].get() == pChild)
		{
			return m_IsChildAttached[i];
		}
	}
	return false;
}

void dae::GameObject::ActivateChild(GameObject* pChild)
{
	if (m_pChilds.size() == 0)
		return;

	for (size_t i = 0; i < m_pChilds.size(); i++)
	{
		if (m_pChilds[i].get() == pChild)
		{
			m_IsChildActive[i] = true;
			return;
		}
	}
}

void dae::GameObject::DeactivateChild(GameObject* pChild)
{
	if (m_pChilds.size() == 0)
		return;

	for (size_t i = 0; i < m_pChilds.size(); i++)
	{
		if (m_pChilds[i].get() == pChild)
		{
			m_IsChildActive[i] = false;
			return;
		}
	}
}


bool dae::GameObject::IsChildActive(GameObject* pChild)
{
	if (m_pChilds.size() == 0)
		return false;

	for(size_t i = 0; i < m_pChilds.size(); i++)
	{
		if(m_pChilds[i].get() == pChild)
		{
			return m_IsChildActive[i];
		}
	}
	return false;
}
