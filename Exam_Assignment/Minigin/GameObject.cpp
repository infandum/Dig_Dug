#include "MiniginPCH.h"
#include "GameObject.h"
#include "Components.h"
#include <complex>
#include "ServiceLocator.h"

UINT dae::GameObject::m_NumberOfGameObjects = 0;

dae::GameObject::GameObject()
{
	++m_NumberOfGameObjects;
}

void dae::GameObject::Initialize()
{
	m_SceneIndex = ServiceLocator::GetSceneManager()->GetActiveSceneIndex();
	for (auto& component : m_pComponents)
	{
		component->Initialize();
	}

	for (size_t i = 0; i < m_pChilds.size(); i++)
	{
		m_pChilds[i]->Initialize();
	}
}

void dae::GameObject::Update(float deltaTime)
{
	//if(/*m_IsActive &&*/ m_SceneIndex == ServiceLocator::GetSceneManager()->GetActiveSceneIndex())
	if (m_Name == "Pooka")
	{
		std::cout << m_Name << std::endl;
	}
	if(m_IsActive)
	{
		for (size_t i = 0; i < m_pChilds.size(); i++)
		{
				m_pChilds[i]->Update(deltaTime);
		}

		for (auto& component : m_pComponents)
		{
			component->Update(deltaTime);
		}
		m_IsActiveLastFrame = m_IsActive;
	}
	else
	{
			m_IsActiveLastFrame = m_IsActive;
	}

	auto trans = GetComponent<TransformComponent>();
}

void dae::GameObject::Render() const
{
	if(m_Name == "Pooka")
	{
		std::cout << m_Name << std::endl;
	}
	if (m_IsActive && m_IsActiveLastFrame)
	{
		for (size_t i = 0; i < m_pChilds.size(); i++)
		{
			m_pChilds[i]->Render();
		}
		//TODO: REFRACTOR
		if(m_pRenderComponent)
			m_pRenderComponent->Render();	
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
			std::cout << "Component Duplicate: " << typeid(*comp).name() << " >> Already added!! " << GetName() << std::endl;
			return;
		}
	}
	m_pComponents.push_back(comp);
	comp->m_pGameObject = this;

	if (comp && typeid(*comp) == typeid(RenderComponent) && m_pRenderComponent == nullptr)
		m_pRenderComponent = std::static_pointer_cast<RenderComponent>(comp);
}

void dae::GameObject::RemoveComponent(std::shared_ptr<BaseComponent> pComp)
{
	const auto comp = std::find(m_pComponents.begin(), m_pComponents.end(), pComp);
	if (comp == m_pComponents.end())
	{
		std::cout << "GameObject::RemoveComponent > Component is not attached to this GameObject! " << GetName() << std::endl;
		return;
	}
	m_pComponents.erase(comp);
	pComp->m_pGameObject = nullptr;
}

void dae::GameObject::AddChild(std::shared_ptr<GameObject> pChild, bool isActive, bool isAttached)
{
	for (auto& child : m_pChilds)
	{
		if (child == pChild)
		{
			std::cout << "Child Duplicate: " << typeid(*child).name() << " >> Already added!! " << GetName() << std::endl;
			return;
		}
	}

	pChild->SetParent(this);
	pChild->GetComponent<TransformComponent>()->SetLocalPosition(pChild->GetComponent<TransformComponent>()->GetPosition().x - GetComponent<TransformComponent>()->GetPosition().x
																, pChild->GetComponent<TransformComponent>()->GetPosition().y - GetComponent<TransformComponent>()->GetPosition().y
																, pChild->GetComponent<TransformComponent>()->GetPosition().z - GetComponent<TransformComponent>()->GetPosition().z);
	pChild->SetIsActive(isActive);
	pChild->SetIsFollowParent(isAttached);
	m_pChilds.push_back(pChild);
	//m_pChilds[m_pChilds.size() - 1]->SetParent(this);
	////m_pChilds[m_pChilds.size() - 1]->GetComponent<TransformComponent>->SetLocalPosition(pChild->GetComponent<TransformComponent>()->GetPosition().x - GetComponent<TransformComponent>()->GetPosition().x
	////																					, pChild->GetComponent<TransformComponent>()->GetPosition().y - GetComponent<TransformComponent>()->GetPosition().y
	////																					, pChild->GetComponent<TransformComponent>()->GetPosition().z - GetComponent<TransformComponent>()->GetPosition().z);


	//m_pChilds[m_pChilds.size() - 1]->SetIsActive(isActive);
	//m_pChilds[m_pChilds.size() - 1]->SetIsFollowParent(isAttached);

}

void dae::GameObject::RemoveChild(std::shared_ptr<GameObject> pChild)
{
	const auto child = std::find(m_pChilds.begin(), m_pChilds.end(), pChild);
	if (child == m_pChilds.end())
	{
		std::cout << "GameObject::RemoveComponent > Component is not attached to this GameObject! " << GetName() << std::endl;
		return;
	}
	m_pChilds.erase(child);
	pChild->SetParent(nullptr);
}

bool dae::GameObject::IsChild(GameObject* pChild)
{
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
	for (UINT i = 0; i < m_pChilds.size(); i++)
	{
		if (i == index)
		{
			return m_pChilds[i];
		}
	}
	return nullptr;
}

void dae::GameObject::SetIsFollowParent(bool isFollow)
{
	if (!m_IsFollowing && isFollow)
	{
		GetComponent<TransformComponent>()->SetLocalPosition(GetComponent<TransformComponent>()->GetPosition().x - GetParent()->GetComponent<TransformComponent>()->GetPosition().x
															,GetComponent<TransformComponent>()->GetPosition().y - GetParent()->GetComponent<TransformComponent>()->GetPosition().y
															,GetComponent<TransformComponent>()->GetPosition().z - GetParent()->GetComponent<TransformComponent>()->GetPosition().z);
	}
	m_IsFollowing = isFollow;
}