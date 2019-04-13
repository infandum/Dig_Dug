#include "MiniginPCH.h"
#include "GameObject.h"
#include "Components.h"
#include "CollisionManager.h"

extern const float g_MoveSpeed;

dae::CollisionComponent::CollisionComponent()
{
	auto& Collision = CollisionManager::GetInstance();
	Collision.AddCollision(this);
}

dae::CollisionComponent::CollisionComponent(int x, int y)
{
	m_Size = {x,y};
	auto& Collision = CollisionManager::GetInstance();
	Collision.AddCollision(this);
}

void dae::CollisionComponent::SetPosition(float x, float y, float z)
{
	m_Position = glm::vec3(x, y, z);
}

void dae::CollisionComponent::Update(float& deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	if (!m_pTransformComponent && m_pTransformComponent == nullptr)
	{
		m_pTransformComponent = GetGameObject()->GetComponent<TransformComponent>();
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

	//Prevent Overlapping
	if(GetCollision() != nullptr)
	{
		if(GetCollision()->GetGameObject()->GetComponent<TransformComponent>()->GetIsStatic())
		{
			if (m_Position.x < GetCollision()->GetPosition().x)
				if (GetGameObject()->GetComponent<TransformComponent>()->DirectionFromVelocity() == Direction::RIGHT)
					GetGameObject()->GetComponent<TransformComponent>()->SetVelocity(glm::vec3{ -g_MoveSpeed / 2, 0, 0 });

			if (m_Position.x > GetCollision()->GetPosition().x)
				if (GetGameObject()->GetComponent<TransformComponent>()->DirectionFromVelocity() == Direction::LEFT)
					GetGameObject()->GetComponent<TransformComponent>()->SetVelocity(glm::vec3{ g_MoveSpeed / 2, 0, 0 });

			if (m_Position.y < GetCollision()->GetPosition().y)
				if (GetGameObject()->GetComponent<TransformComponent>()->DirectionFromVelocity() == Direction::DOWN)
					GetGameObject()->GetComponent<TransformComponent>()->SetVelocity(glm::vec3{ 0, -g_MoveSpeed / 2, 0 });

			if (m_Position.y > GetCollision()->GetPosition().y)
				if (GetGameObject()->GetComponent<TransformComponent>()->DirectionFromVelocity() == Direction::UP)
					GetGameObject()->GetComponent<TransformComponent>()->SetVelocity(glm::vec3{ 0, g_MoveSpeed / 2, 0 });
		}
		
	}
}
