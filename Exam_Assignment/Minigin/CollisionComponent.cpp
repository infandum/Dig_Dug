#include "MiniginPCH.h"
#include "GameObject.h"
#include "Components.h"
#include "PhysicsManager.h"

extern const float g_MoveSpeed;

dae::CollisionComponent::CollisionComponent()
{
	auto& Collision = PhysicsManager::GetInstance();
	std::shared_ptr<CollisionComponent> coll;
	coll.reset(this);
	Collision.AddCollision(coll);
}

dae::CollisionComponent::CollisionComponent(int x, int y)
{
	m_Size = {x,y};
	auto& Collision = PhysicsManager::GetInstance();
	std::shared_ptr<CollisionComponent> coll;
	coll.reset(this);
	Collision.AddCollision(coll);
}

void dae::CollisionComponent::SetPosition(float x, float y, float z)
{
	m_Position = glm::vec3(x, y, z);
}

void dae::CollisionComponent::Update(float& deltaTime)
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
			m_Size = GetGameObject()->GetComponent<TextureComponent>()->GetSize();
	}
	else
	{
		if (m_offSet.IsNullVector())
		{
			if (GetGameObject() && !GetGameObject()->GetComponent<TextureComponent>()->GetSize().IsNullVector())
			{
				m_offSet.x = m_Size.x - GetGameObject()->GetComponent<TextureComponent>()->GetSize().x;
				m_offSet.y = m_Size.y - GetGameObject()->GetComponent<TextureComponent>()->GetSize().y;
			}
		}
		m_Position.x = m_pTransformComponent->GetPosition().x - m_offSet.x / 2;
		m_Position.y = m_pTransformComponent->GetPosition().y - m_offSet.y / 2;
	}

	//TODO:: CHANGE PUSH OUT EFFECT, MAYBE PREVENT OBJECT MOVING INTO A COLLISION?
	//Prevent Overlapping
	if(GetCollision() != nullptr)
	{
		if(GetCollision()->GetGameObject()->GetComponent<TransformComponent>()->GetIsStatic())
		{
			std::cout << "PUSHOUT" << std::endl;
			GetGameObject()->GetComponent<TransformComponent>()->SetPosition(float(GetGameObject()->GetComponent<TransformComponent>()->GetPositionIndex().x * 32), float(GetGameObject()->GetComponent<TransformComponent>()->GetPositionIndex().y * 32));

			//if (m_Position.x < GetCollision()->GetPosition().x)
			//{
			//	////if (GetGameObject()->GetComponent<TransformComponent>()->GetDirectionFromVelocity() == Direction::RIGHT)
			//	//	GetGameObject()->GetComponent<TransformComponent>()->SetVelocity(glm::vec3{ -g_MoveSpeed / 3, 0, 0 });
			//GetGameObject()->GetComponent<TransformComponent>()->SetPosition(float(GetGameObject()->GetComponent<TransformComponent>()->GetPositionIndex().x * 32), float(GetGameObject()->GetComponent<TransformComponent>()->GetPositionIndex().y * 32));
			//}
			//if (m_Position.x > GetCollision()->GetPosition().x)
			//{ 
			//	//if (GetGameObject()->GetComponent<TransformComponent>()->GetDirectionFromVelocity() == Direction::LEFT)
			//		//GetGameObject()->GetComponent<TransformComponent>()->SetVelocity(glm::vec3{ g_MoveSpeed / 3, 0, 0 });
			//	GetGameObject()->GetComponent<TransformComponent>()->SetPosition(float(GetGameObject()->GetComponent<TransformComponent>()->GetPositionIndex().x * 32), float(GetGameObject()->GetComponent<TransformComponent>()->GetPositionIndex().y * 32));

			//}
			//if (m_Position.y < GetCollision()->GetPosition().y)
			//{
			//	//if (GetGameObject()->GetComponent<TransformComponent>()->GetDirectionFromVelocity() == Direction::DOWN)
			//		//GetGameObject()->GetComponent<TransformComponent>()->SetVelocity(glm::vec3{ 0, -g_MoveSpeed / 3, 0 });
			//	GetGameObject()->GetComponent<TransformComponent>()->SetPosition(float(GetGameObject()->GetComponent<TransformComponent>()->GetPositionIndex().x * 32), float(GetGameObject()->GetComponent<TransformComponent>()->GetPositionIndex().y * 32));

			//}
			//if (m_Position.y > GetCollision()->GetPosition().y)
			//{
			//	//if (GetGameObject()->GetComponent<TransformComponent>()->GetDirectionFromVelocity() == Direction::UP)}
			//		//GetGameObject()->GetComponent<TransformComponent>()->SetVelocity(glm::vec3{ 0, g_MoveSpeed / 3, 0 });
			//	GetGameObject()->GetComponent<TransformComponent>()->SetPosition(float(GetGameObject()->GetComponent<TransformComponent>()->GetPositionIndex().x * 32), float(GetGameObject()->GetComponent<TransformComponent>()->GetPositionIndex().y * 32));

			//}
		}	
	}
}
