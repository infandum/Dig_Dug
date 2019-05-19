#include "MiniginPCH.h"
#include "GameObject.h"
#include "Components.h"
#include "PhysicsManager.h"
#include "ServiceLocator.h"

dae::CollisionComponent::CollisionComponent(int x, int y, const bool& isTrigger)
{
	m_Size = {x,y};
	m_Trigger = isTrigger;
}

void dae::CollisionComponent::SetPosition(float x, float y, float z)
{
	m_Position = glm::vec3(x, y, z);
}

void dae::CollisionComponent::Initialize()
{
	auto physics_manager = ServiceLocator::GetPhysicsManager();
	physics_manager->AddCollision(this);
}

void dae::CollisionComponent::Update(float deltaTime)
{
	
	UNREFERENCED_PARAMETER(deltaTime);
	if (!m_pTransformComponent && m_pTransformComponent == nullptr && GetGameObject()->GetTransform() != nullptr)
	{
		m_pTransformComponent = GetGameObject()->GetTransform();
		m_Position = m_pTransformComponent->GetPosition();	
	}

	//Set Collision box around the center of the object
	if (m_Size.IsNullVector())
	{
		if (GetGameObject())
			if(GetGameObject()->GetSprite())
				m_Size = { GetGameObject()->GetComponent<SpriteComponent>()->GetCurrentUV().w, GetGameObject()->GetComponent<SpriteComponent>()->GetCurrentUV().h };
			else if(GetGameObject()->GetTexture())
				m_Size = GetGameObject()->GetComponent<TextureComponent>()->GetSize();
	}
	else
	{
		if (m_offSet.IsNullVector())
		{
			if (GetGameObject() && !GetGameObject()->GetComponent<TextureComponent>()->GetSize().IsNullVector())
			{
				if (!GetGameObject()->GetSprite())
				{
					m_offSet.x = m_Size.x - GetGameObject()->GetComponent<TextureComponent>()->GetSize().x;
					m_offSet.y = m_Size.y - GetGameObject()->GetComponent<TextureComponent>()->GetSize().y;
				}		
			}
		}
		m_Position.x = m_pTransformComponent->GetPosition().x - (m_offSet.x / 2);
		m_Position.y = m_pTransformComponent->GetPosition().y - (m_offSet.x / 2);
	}


	if (!m_Collide)
		return;

	ShowCollisionBox(m_Collide);
	//Prevent Overlapping
	if(m_HasCollision && m_Collide)
	{	
		if(m_pOtherCollider != this && GetCollision()->m_Collide)
		{
			//Don't trigger collision with child/parents 
			if (GetGameObject()->IsChild(GetCollision()->GetGameObject()) || GetGameObject()->GetParent() == GetCollision()->GetGameObject())
			{
				m_HasCollision = false;
				return;
			}

			//TODO:: CHANGE PUSH OUT EFFECT, MAYBE PREVENT OBJECT MOVING INTO A COLLISION?
			if(!m_Trigger && !GetCollision()->IsTrigger() && m_PushOut)
				GetGameObject()->GetComponent<TransformComponent>()->SetPosition(float(GetGameObject()->GetComponent<TransformComponent>()->GetPositionIndex().x * 32), float(GetGameObject()->GetComponent<TransformComponent>()->GetPositionIndex().y * 32));
				
		}
	}
}