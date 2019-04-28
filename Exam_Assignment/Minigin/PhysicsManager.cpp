#include "MiniginPCH.h"
#include "PhysicsManager.h"
#include "GameObject.h"
#include "Components.h"

void dae::PhysicsManager::Update(float deltaTime)
{
	//TODO: ENTER COLLISION
	//TODO: LEAVE COLLISION
	UNREFERENCED_PARAMETER(deltaTime);
	for (auto& component : m_pCollisionComponents)
	{
		//Render Collision Debug Box 
		if(!component->ShowCollisionBox())
			component->ShowCollisionBox(ShowCollisionBox());

		for (auto& otherComponent : m_pCollisionComponents)
		{
			if(component == otherComponent)
				continue;

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
			const auto isOverlapping = CheckBoxesIntersect(compBox, otherCompBox);
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
	for (auto& component : m_pCollisionComponents)
	{
		if (component->GetGameObject() == collision->GetGameObject())
		{
			std::cout << "Collision Duplicate: " << collision->GetGameObject()->GetName() << " >> Already added!!\n";
			return;
		}
	}
	m_pCollisionComponents.push_back(collision);
}

dae::CollisionComponent* dae::PhysicsManager::GetCollision(GameObject* owner)
{
	for (auto& component : m_pCollisionComponents)
	{
		if (component->GetGameObject() == owner)
		{
			return component;
		}
	}
	return nullptr;
}