#include "MiniginPCH.h"
#include "Components.h"
#include "GameObject.h"

void dae::TransformComponent::Update(float )
{
	if (GetGameObject()->GetParent())
		if (GetGameObject()->GetIsFollowingParent())
			m_Position = GetGameObject()->GetParent()->GetTransform()->GetPosition() + GetGameObject()->GetTransform()->GetLocalPosition();
}

dae::TransformComponent::TransformComponent(float x, float y, float z)
{
	SetPosition(x, y,  z);
	SetPositionIndex({ static_cast<int>(x / 32), static_cast<int>(y / 32) });
}

void dae::TransformComponent::SetPosition(float x, float y, float z)
{
	m_Position = { 0,0,0 };
	m_Position = glm::vec3(x, y, z);
}

void dae::TransformComponent::Initialize()
{
	SetPositionIndex({ static_cast<int>(m_Position.x / 32), static_cast<int>(m_Position.y / 32) });
}
