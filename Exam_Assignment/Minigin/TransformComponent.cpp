#include "MiniginPCH.h"
#include "Components.h"
#include "GameObject.h"
#include <cmath>
#include "InputManager.h"

extern const float g_MoveSpeed;

void dae::TransformComponent::Update(float& deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	if(!m_IsStatic)
	{
		glm::vec3 velocity{ 0 };
		if (m_Velocity.x != 0 || m_Velocity.y != 0)
			velocity = MoveDirection();

		if(m_IsMoving)
		{
			//TODO: CHECK IF NEXT TILE IS LEGAL MOVE
			double newPositionX = m_Position.x + round(deltaTime * velocity.x);
			double newPositionY = m_Position.y + round(deltaTime * velocity.y);

			//BORDER CONTROL
			const int MIN_POSITION_X = 0;
			const int MAX_POSITION_X = 448 - 32;
			const int MIN_POSITION_Y = 32;
			const int MAX_POSITION_Y = 576 - (32 + 32);

			if (newPositionX < MIN_POSITION_X)
				newPositionX = MIN_POSITION_X;

			if (newPositionX > MAX_POSITION_X)
				newPositionX = MAX_POSITION_X;
			
			if (newPositionY < MIN_POSITION_Y)
				newPositionY = MIN_POSITION_Y;

			if (newPositionY > MAX_POSITION_Y)
				newPositionY = MAX_POSITION_Y;

			
			m_Position = { newPositionX, newPositionY, m_Position.z };
			m_IsMoving = false;
		}
	}
}

dae::TransformComponent::TransformComponent()
{
	m_Position = { 0,0,0 };
}

dae::TransformComponent::TransformComponent(float x, float y, float z)
{
	m_Position = { x, y, z };
}

void dae::TransformComponent::SetPosition(float x, float y, float z)
{
	m_Position = glm::vec3(x, y, z);
}


glm::vec3 dae::TransformComponent::MoveDirection()
{
	
	//TODO: Fix Minor freeze bug might be lag?
	glm::vec3 velocity{ 0 };
	m_IsMoving = true;
	if (m_Velocity.x != 0)
	{
		//Check if object is Aligned with center of tile on the Y-axis
		const auto modulo = fmod(round(m_Position.y), 32.0);
		isYonTileCenter = true;
		if (modulo > 1 && modulo < 31)
			isYonTileCenter = false;
		//IF not aligned first move object to aligned tile central Y-axis
		//ELSE move to input direction
		if (!isYonTileCenter)
		{
			if (modulo >= 16)
				velocity.y = g_MoveSpeed;
			else
				velocity.y = -g_MoveSpeed;
		}
		else
		{
			velocity.x = m_Velocity.x;
			velocity.y = m_Velocity.y;
		}
	}

	if (m_Velocity.y != 0)
	{
		//Check if object is Aligned with center of tile on the X-axis
		const auto modulo = fmod(round(m_Position.x), 32.0);
		//IF not aligned first move object to aligned tile central X-axis
		//ELSE move to input direction
		isXonTileCenter = true;
		if (modulo > 1 && modulo < 31)
			isXonTileCenter = false;
		if (!isXonTileCenter)
		{
			if (modulo >= 16)
				velocity.x = g_MoveSpeed;
			else
				velocity.x = -g_MoveSpeed;
		}
		else
		{
			velocity.x = m_Velocity.x;
			velocity.y = m_Velocity.y;
		}
	}
	return velocity;
}

dae::Direction dae::TransformComponent::GetDirectionFromVelocity() const
{
	if (m_Velocity.y < 0.0f)
		return Direction::UP;

	if (m_Velocity.y > 0.0f)
		return Direction::DOWN;

	if (m_Velocity.x < 0.0f)
		return Direction::LEFT;

	if (m_Velocity.x > 0.0f)
		return Direction::RIGHT;

	return Direction::NONE;
}

glm::vec3 dae::TransformComponent::MoveToTile(unsigned int x, unsigned int y, bool canDig)
{
	glm::vec3 velocity{ 0 };
	if(canDig)
	{
		m_IsMoving = true;

	
	glm::vec3 newPos;
	newPos.x = float(x) * 32;
	newPos.y = float(y) * 32;
	m_OffSet = glm::vec3(0, 0, 0);

	if (newPos.x > m_Position.y)
		velocity.x = g_MoveSpeed;
	if (newPos.x < m_Position.y)
		velocity.x = -g_MoveSpeed;
	if (newPos.y > m_Position.y)
		velocity.y = g_MoveSpeed;
	if (newPos.x < m_Position.y)
		velocity.y = -g_MoveSpeed;
	}
	return velocity;
}
