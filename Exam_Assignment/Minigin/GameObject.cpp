#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Components.h"
#include <complex>
unsigned int dae::GameObject::m_NumberOfGameObjects = 0;

dae::GameObject::GameObject(): m_pTransformComponent(nullptr), m_pTextureComponent(nullptr)
{
	++m_NumberOfGameObjects;
}

void dae::GameObject::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	for (auto& component : m_pComponents)
	{
		component->Update(deltaTime);
		if (component && typeid(*component) == typeid(TransformComponent) && !m_pTransformComponent)
			m_pTransformComponent = static_cast<TransformComponent*>(component);

		if (component && typeid(*component) == typeid(TextureComponent) && !m_pTextureComponent)
			m_pTextureComponent = static_cast<TextureComponent*>(component);

	}
}

void dae::GameObject::Render() const
{
	if (m_pTextureComponent != nullptr && m_pTransformComponent != nullptr)
		if(m_pTextureComponent->GetTexture())
			Renderer::GetInstance().RenderTexture(*m_pTextureComponent->GetTexture(), m_pTransformComponent->GetPosition().x, m_pTransformComponent->GetPosition().y, float(m_pTextureComponent->GetSize().x), float(m_pTextureComponent->GetSize().y));

}

void dae::GameObject::SetName(std::string name)
{
	m_Name = name;
}

void dae::GameObject::AddComponent(BaseComponent* comp)
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
	std::shared_ptr<GameObject> owner;
	owner.reset(this);
	comp->m_pGameObject = owner;
}

void dae::GameObject::RemoveComponent(BaseComponent* pComp)
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