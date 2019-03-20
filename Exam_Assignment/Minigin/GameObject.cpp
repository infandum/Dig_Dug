#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Components.h"

void dae::GameObject::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	for (auto component : m_pComponents)
	{
		component->Update(deltaTime);
	}
}

void dae::GameObject::Render() const
{
	if (mTexture)
	{
		const auto& ti = typeid(TransformComponent);
		for (auto &component : m_pComponents)
		{
			if (component && typeid(*component) == ti)
				Renderer::GetInstance().RenderTexture(*mTexture, static_cast<TransformComponent*>(component)->GetPosition().x, static_cast<TransformComponent*>(component)->GetPosition().y);
		}
	}	
}

void dae::GameObject::SetTexture(const std::string& filename)
{
	mTexture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::GameObject::SetTexture(std::shared_ptr<Texture2D> texture)
{
	mTexture = texture;
}

void dae::GameObject::SetPosition(float x, float y)
{
	mTransform.SetPosition(x, y, 0.0f);
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