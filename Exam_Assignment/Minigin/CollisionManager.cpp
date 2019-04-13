#include "MiniginPCH.h"
#include "CollisionManager.h"
#include "GameObject.h"
#include "Components.h"

extern const float g_CollisionPadding;

void dae::CollisionManager::Update(float deltaTime)
{
	//TODO: ENTER COLLISION
	//TODO: LEAVE COLLISION
	UNREFERENCED_PARAMETER(deltaTime);
	for (auto& component : m_pCollisionComponents)
	{
		//Render Collision Debug Box 
		if(!component->ShowCollisionBox())
			component->ShowCollisionBox(ShowCollisionBox());

		auto isOverlapping = false;

		/*const glm::vec3 firstPos = component->GetPosition();*/

		for (auto& otherComponent : m_pCollisionComponents)
		{
			if(component == otherComponent)
				continue;

			
			/*glm::vec3 SecondPos = otherComponent->GetPosition();*/
			isOverlapping = IsOverlapping(component, otherComponent);
			
			/*std::cout << component->GetGameObject()->GetName() << "<>" <<otherComponent->GetGameObject()->GetName() << std::endl;
			if(isOverlapping)
				std::cout << "COLLISION!!" << std::endl;
			else
				std::cout << "NO COLLISION!!" << std::endl;*/

			if(isOverlapping)
			{
				component->SetHasCollision(isOverlapping);
				otherComponent->SetHasCollision(isOverlapping);
				component->SetCollision(otherComponent);
				otherComponent->SetCollision(component);
			}
			else
			{
				component->SetHasCollision(isOverlapping);
				otherComponent->SetHasCollision(isOverlapping);
				component->SetCollision(nullptr);
				otherComponent->SetCollision(nullptr);
			}
		}
	}
}

void dae::CollisionManager::AddCollision(CollisionComponent* collision)
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

dae::CollisionComponent* dae::CollisionManager::GetCollision(std::shared_ptr<GameObject> owner)
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

bool dae::CollisionManager::IsOverlapping(CollisionComponent* firstComp, CollisionComponent* secondComp)
{
	auto IsXOverlap = false;
	auto IsYOverlap = false;

	if (firstComp->GetPosition().x >= secondComp->GetPosition().x)
	{
		if (firstComp->GetPosition().x - (firstComp->GetSize().x / 2) + g_CollisionPadding < secondComp->GetPosition().x + (secondComp->GetSize().x / 2) - g_CollisionPadding)
		{
			IsXOverlap = true;
		}
	}
	else
	{
		if (firstComp->GetPosition().x + (firstComp->GetSize().x / 2) - g_CollisionPadding > secondComp->GetPosition().x - (secondComp->GetSize().x / 2) + g_CollisionPadding)
		{
			IsXOverlap = true;
		}
	}

	if (firstComp->GetPosition().y >= secondComp->GetPosition().y)
	{
		if (firstComp->GetPosition().y - (firstComp->GetSize().y / 2) + g_CollisionPadding < secondComp->GetPosition().y + (secondComp->GetSize().y / 2) - g_CollisionPadding)
		{
			IsYOverlap = true;
		}
	}
	else
	{
		if (firstComp->GetPosition().y + (firstComp->GetSize().y / 2) - g_CollisionPadding > secondComp->GetPosition().y - (secondComp->GetSize().y / 2) + g_CollisionPadding)
		{
			IsYOverlap = true;
		}
	}

	return IsXOverlap && IsYOverlap;
}