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

void dae::CollisionComponent::Reset()
{
	m_Position = m_pTransformComponent->GetPosition();
	CollisionPosition();
	m_HasCollision = false;
	m_pOtherCollider = nullptr;
}

void dae::CollisionComponent::onNotify(GameObject& , NotifyEvent& )
{
}

void dae::CollisionComponent::Initialize()
{
	auto physics_manager = ServiceLocator::GetPhysicsManager();
	physics_manager->AddCollision(this);

	m_pTransformComponent = GetGameObject()->GetTransform();
	m_Position = m_pTransformComponent->GetPosition();

	m_pSpriteComponent = GetGameObject()->GetSprite();
	m_pTextureComponent = GetGameObject()->GetTexture();

	CollisionPosition();
}

void dae::CollisionComponent::Collision()
{
	if(m_HasCollision && m_Collide)
	{	
		if(m_pOtherCollider != this && GetCollision()->m_Collide)
		{
			//Don't trigger collision with child/parents 
			if (GetGameObject()->IsChild(GetCollision()->GetGameObject()) || GetGameObject()->GetParent() == GetCollision()->GetGameObject() || (m_Trigger && GetCollision()->IsTrigger()))
			{
				m_HasCollision = false;
			}
			//TODO:: CHANGE PUSH OUT EFFECT, MAYBE PREVENT OBJECT MOVING INTO A COLLISION?
			if(!m_Trigger && !GetCollision()->IsTrigger() && m_PushOut)
				GetGameObject()->GetComponent<TransformComponent>()->SetPosition(float(GetGameObject()->GetComponent<TransformComponent>()->GetPositionIndex().x * 32), float(GetGameObject()->GetComponent<TransformComponent>()->GetPositionIndex().y * 32));
				
		}
	}
}

void dae::CollisionComponent::CollisionPosition()
{
	if (m_pSpriteComponent)
	{
		if (m_CustomSize)
		{

		}
		else
		{
			m_Size = { m_pSpriteComponent->GetCurrentUV().w, m_pSpriteComponent->GetCurrentUV().h };

			m_offSet.x = m_Size.x - m_pSpriteComponent->GetCurrentUV().w;
			m_offSet.y = m_Size.y - m_pSpriteComponent->GetCurrentUV().h;
		}
			
	}		
	else if (m_pTextureComponent)
	{
		if (m_CustomSize)
		{
			
		}
		else
		{
			m_Size = m_pTextureComponent->GetSize();

			m_offSet.x = m_Size.x - m_pTextureComponent->GetSize().x;
			m_offSet.y = m_Size.y - m_pTextureComponent->GetSize().y;
		}
		
	}
	else
	{
		if (!m_CustomSize)
			m_Size = { 32, 32 };

		m_offSet.x = 0;
		m_offSet.y = 0;
	}

	m_Position.x = m_pTransformComponent->GetPosition().x - (m_offSet.x / 2);
	m_Position.y = m_pTransformComponent->GetPosition().y - (m_offSet.x / 2);
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
	CollisionPosition();

	if (!m_Collide)
		return;

	ShowCollisionBox(m_Collide);
	//Prevent Overlapping
	Collision();
}
