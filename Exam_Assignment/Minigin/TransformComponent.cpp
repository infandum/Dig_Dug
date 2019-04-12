#include "MiniginPCH.h"
#include "Components.h"
#include <cmath>

extern const float g_MoveSpeed;

void dae::TransformComponent::Update(float& deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	if(!isStatic)
	{
		glm::vec3 velocity{ 0 };
		if (m_Direction.x != 0 || m_Direction.y != 0)
			velocity = MoveDirection();


		double newPositionX = m_Position.x + round(deltaTime * velocity.x);
		double newPositionY = m_Position.y + round(deltaTime * velocity.y);

		//BORDER CONTROL
		const int MIN_POSITION_X = 0;
		const int MAX_POSITION_X = 448 - 32;
		const int MIN_POSITION_Y = 32;
		const int MAX_POSITION_Y = 576 - (32 + 32);

		if (newPositionX < MIN_POSITION_X)
			newPositionX = MIN_POSITION_X;

		if (newPositionX >= MAX_POSITION_X)
			newPositionX = MAX_POSITION_X;
		
		if (newPositionY < MIN_POSITION_Y)
			newPositionY = MIN_POSITION_Y;

		if (newPositionY >= MAX_POSITION_Y)
			newPositionY = MAX_POSITION_Y;

		m_Position = { newPositionX, newPositionY, m_Position.z };
	}
}

void dae::TransformComponent::SetPosition(float x, float y, float z)
{
	m_Position = glm::vec3(x, y, z);
}


glm::vec3 dae::TransformComponent::MoveDirection()
{
	//TODO: Fix Minor freeze bug might be lag?
	glm::vec3 velocity{ 0 };
	if (m_Direction.x != 0)
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
			velocity.x = m_Direction.x;
			velocity.y = m_Direction.y;
		}
	}

	if (m_Direction.y != 0)
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
			velocity.x = m_Direction.x;
			velocity.y = m_Direction.y;
		}
	}
	return velocity;
}

bool dae::TransformComponent::MoveToTile(unsigned int x, unsigned int y)
{
	isStatic = true;

	glm::vec3 newPos;
	newPos.x = float(x) * 32;
	newPos.y = float(y) * 32;
	m_OffSet = glm::vec3(0, 0, 0);

	if (newPos.x > m_Position.y)
		m_OffSet.x = 1;
	if (newPos.x < m_Position.y)
		m_OffSet.x = -1;
	if (newPos.y > m_Position.y)
		m_OffSet.y = 1;
	if (newPos.x < m_Position.y)
		m_OffSet.y = -1;

	if ((int(newPos.x) == int(m_Position.x) && newPos.y == m_Position.y)
		/*||(m_Position.x <= 0 || m_Position.x >= 13*32 || m_Position.y <= 0 || m_Position.y >= 17 * 32)*/)
	{
		isStatic = false;  
		return true;
	}
	return false;
}
