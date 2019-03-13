#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"


dae::GameObject::~GameObject() = default;

void dae::GameObject::Update(){}

void dae::GameObject::Render() const
{
	const auto pos = mTransform.GetPosition();
	Renderer::GetInstance().RenderTexture(*mTexture, pos.x, pos.y);
}

void dae::GameObject::SetTexture(const std::string& filename)
{
	mTexture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::GameObject::SetPosition(float x, float y)
{
	mTransform.SetPosition(x, y, 0.0f);
}

void dae::GameObject::AddComponent(BaseComponent* pComp)
{
	/*for (auto *component : m_pComponents)
	{
		if (component == pComp)
		{
			std::wcout << L"GameObject::AddComponent > GameObject already contains this component!" << std::endl;
			return;
		}
	}*/
	m_pComponents.push_back(pComp);
	pComp->m_pGameObject = this;
}

void dae::GameObject::RemoveComponent(BaseComponent* pComp)
{
	auto comp = std::find(m_pComponents.begin(), m_pComponents.end(), pComp);
	if (comp == m_pComponents.end())
	{
		std::wcout << L"GameObject::RemoveComponent > Component is not attached to this GameObject!" << std::endl;
		return;
	}
	m_pComponents.erase(comp);
	pComp->m_pGameObject = nullptr;
}
