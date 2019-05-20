#include "MiniginPCH.h"
#include "PhysicsManager.h"
#include "GameObject.h"
#include "Components.h"
#include "ServiceLocator.h"

void dae::PhysicsManager::Initialize()
{
}

void dae::PhysicsManager::Update(float deltaTime)
{
	//TODO: CLEAN THIS UP SO IT DOENS GET DONE EVERY UPDATE;
	SetActiveScene(ServiceLocator::GetSceneManager()->GetActiveSceneIndex());

	//TODO: ENTER COLLISION
	//TODO: LEAVE COLLISION
	UNREFERENCED_PARAMETER(deltaTime);
	auto isOverlapping = false;
	for (auto& component : m_pCollisionComponents[m_ActiveSceneIndex])
	{
		//Render Collision Debug Box 
		if(!component->ShowCollisionBox())
			component->ShowCollisionBox(ShowCollisionBox());

		if (!component->GetGameObject()->GetIsActive()
			||!component->CanCollide()
			)
		{
			isOverlapping = false;
			continue;
		}

		for (auto& otherComponent : m_pCollisionComponents[m_ActiveSceneIndex])
		{
			if(component == otherComponent
				|| !otherComponent->GetGameObject()->GetIsActive()
				|| !otherComponent->CanCollide()
				|| component->GetGameObject()->IsChild(otherComponent->GetGameObject()) 
				|| component->GetGameObject()->GetParent() == otherComponent->GetGameObject() 
				|| otherComponent->GetGameObject()->IsChild(component->GetGameObject())
				|| otherComponent->GetGameObject()->GetParent() == component->GetGameObject())
			{
				isOverlapping = false; 
				continue;
			}
				
			if(component->IsTrigger() && otherComponent->IsTrigger())
			{
				isOverlapping = false;
				continue;
			}
			CollisionBox compBox;
			compBox.x = static_cast<int>(component->GetPosition().x);
			compBox.y = static_cast<int>(component->GetPosition().y);
			compBox.RadiusX = static_cast<int>(component->GetSize().x - m_CollisionPadding);
			compBox.RadiusY = static_cast<int>(component->GetSize().y - m_CollisionPadding);

			CollisionBox otherCompBox;
			otherCompBox.x = static_cast<int>(otherComponent->GetPosition().x);
			otherCompBox.y = static_cast<int>(otherComponent->GetPosition().y);
			otherCompBox.RadiusX = static_cast<int>(otherComponent->GetSize().x - m_CollisionPadding);
			otherCompBox.RadiusY = static_cast<int>(otherComponent->GetSize().y - m_CollisionPadding);
			isOverlapping = CheckBoxesIntersect(compBox, otherCompBox);
			if(isOverlapping)
			{
				component->SetHasCollision(isOverlapping);
				otherComponent->SetHasCollision(isOverlapping);
				component->SetCollision(otherComponent);
				otherComponent->SetCollision(component);
			}
		}
	}
}

void dae::PhysicsManager::AddCollision(CollisionComponent* collision)
{
	m_ActiveSceneIndex = ServiceLocator::GetSceneManager()->GetActiveSceneIndex();
	if (m_pCollisionComponents.empty() || m_pCollisionComponents.size() <= m_ActiveSceneIndex)
		for (auto i = m_pCollisionComponents.size(); i <= m_ActiveSceneIndex; ++i)
		{
			m_pCollisionComponents.push_back(std::vector<CollisionComponent*>());
		}

	for (auto& component : m_pCollisionComponents[m_ActiveSceneIndex])
	{
		if (component->GetGameObject() == collision->GetGameObject())
		{
			std::cout << "Collision Duplicate: " << collision->GetGameObject()->GetName() << " >> Already added!!\n";
			return;
		}
	}
	m_pCollisionComponents[m_ActiveSceneIndex].push_back(collision);
}

dae::CollisionComponent* dae::PhysicsManager::GetCollision(GameObject* owner)
{
	for (auto& component : m_pCollisionComponents[m_ActiveSceneIndex])
	{
		if (component->GetGameObject() == owner)
		{
			return component;
		}
	}
	return nullptr;
}