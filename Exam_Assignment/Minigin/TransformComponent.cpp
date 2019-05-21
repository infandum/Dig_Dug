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
	m_InitPosition = { x, y, z };
}

void dae::TransformComponent::SetPosition(float x, float y, float z)
{
	m_Position = { 0,0,0 };
	m_Position = glm::vec3(x, y, z);
}

void dae::TransformComponent::Reset()
{
	m_Position = m_InitPosition;
	int x = static_cast<int>(round(m_Position.x / 32.0f));
	int y = static_cast<int>(round(m_Position.y / 32.0f));
	SetPositionIndex({ x, y });
}

void dae::TransformComponent::onNotify(GameObject& , NotifyEvent& )
{

}

void dae::TransformComponent::Initialize()
{
	if (GetGameObject()->GetParent())
	{
		if (GetGameObject()->GetIsFollowingParent())
		{
			SetLocalPosition(m_InitPosition.x, m_InitPosition.y, m_InitPosition.y);
			SetPositionIndex({ static_cast<int>(GetGameObject()->GetParent()->GetTransform()->GetPosition().x + static_cast<int>(m_InitPosition.x / 32)),  static_cast<int>(GetGameObject()->GetParent()->GetTransform()->GetPosition().y + static_cast<int>(m_InitPosition.y / 32)) });
		}
		else
		{
			SetPosition(m_InitPosition.x, m_InitPosition.y, m_InitPosition.z);
			SetPositionIndex({ static_cast<int>(m_InitPosition.x / 32), static_cast<int>(m_InitPosition.y / 32) });
		}
	}
	else
	{
		SetPosition(m_InitPosition.x, m_InitPosition.y, m_InitPosition.z);
		SetPositionIndex({ static_cast<int>(m_InitPosition.x / 32), static_cast<int>(m_InitPosition.y / 32) });
	}
}
