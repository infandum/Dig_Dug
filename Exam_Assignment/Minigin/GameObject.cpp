#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Components.h"
#include <complex>

dae::GameObject::GameObject(): m_pTransformComponent(nullptr), m_pTextureComponent(nullptr)
{
	++m_NumberOfGameObjects;
}

//dae::GameObject::~GameObject()
//{
//	for (auto& component : m_pComponents)
//		component = nullptr;
//
//	m_pComponents.clear();
//}

void dae::GameObject::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	for (auto component : m_pComponents)
	{
		component->Update(deltaTime);
		if (component && typeid(*component) == typeid(TransformComponent))
			m_pTransformComponent = static_cast<TransformComponent*>(component);

		if (component && typeid(*component) == typeid(TextureComponent))
			m_pTextureComponent = static_cast<TextureComponent*>(component);

	}
}

void dae::GameObject::Render() const
{
	if (m_pTextureComponent != nullptr && m_pTransformComponent != nullptr)
		if(m_pTextureComponent->GetTexture())
			Renderer::GetInstance().RenderTexture(*m_pTextureComponent->GetTexture(), m_pTransformComponent->GetPosition().x, m_pTransformComponent->GetPosition().y);

}

void dae::GameObject::SetName(std::string& name)
{
	m_Name = name;
}

void dae::GameObject::SetTexture(const std::string& filename)
{
	mTexture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::GameObject::SetTexture(std::shared_ptr<Texture2D> texture)
{
	mTexture = texture;
}

void dae::GameObject::AddComponent(BaseComponent* comp)
{
	//TODO: check duplicates
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