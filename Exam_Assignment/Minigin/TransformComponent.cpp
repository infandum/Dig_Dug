#include "MiniginPCH.h"
#include "Components.h"
#include "GameObject.h"
#include <cmath>
#include "InputManager.h"
#include "LevelManager.h"
#include "ServiceLocator.h"

extern  const float g_MoveSpeed;
extern const float g_TileCenterPadding;

void dae::TransformComponent::Update(float& deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	if(m_IsStatic)
	{
		const auto tile = ServiceLocator::GetLevelManager()->GetTile(m_CurrentTileIndex.x, m_CurrentTileIndex.y);
		if (tile->GetTileState() != TileState::OCCUPIED)
			tile->SetTileState(TileState::OCCUPIED);
	}

	if(!m_IsStatic)
	{
		glm::vec3 velocity{ 0 };
		if (m_Velocity.x != 0 || m_Velocity.y != 0)
			velocity = MoveDirection();
		

		if (m_IsMoving)
		{
			isSwappingTile = false;
			//CHECK IF NEXT TILE IS LEGAL MOVE
			const iVector2 nextTileIndex = { m_CurrentTileIndex.x + GetNextTileDirectionFromVelocity().x, m_CurrentTileIndex.y + GetNextTileDirectionFromVelocity().y };
			//const auto currTile = ServiceLocator::GetLevelManager()->GetTile(m_CurrentTileIndex.x, m_CurrentTileIndex.y);
			const auto nextTile = ServiceLocator::GetLevelManager()->GetTile(nextTileIndex.x, nextTileIndex.y);
			if (nextTile != nullptr)
			{
				if(nextTile->GetTileState() == TileState::OCCUPIED && IsCentered())
				{
					//std::cout << "NEXT TILE IS OCCUPIED\n";
					isSwappingTile = false;
					return;
				}
				if (nextTile->GetTileState() == TileState::DIRT/* && currTile->GetBorder(GetCurrentDirection()) == false*/)
				{
					isSwappingTile = true;
				}
			}

				
				
			

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

dae::TransformComponent::TransformComponent(float x, float y, float z)
{
	m_Position = { x, y, z };
}

void dae::TransformComponent::SetPosition(float x, float y, float z)
{
	m_Position = glm::vec3(x, y, z);
	SetPositionIndex({int( x / 32), int(y / 32) });
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

bool dae::TransformComponent::IsCentered() const
{
	//from top
	bool XisCenter = false;
	bool YisCenter = false;

	if (m_Position.x >= m_CurrentTileIndex.x * 32 - g_TileCenterPadding && m_Position.x <= m_CurrentTileIndex.x * 32 + g_TileCenterPadding)
		XisCenter = true;							  
													  
	if (m_Position.y >= m_CurrentTileIndex.y * 32 - g_TileCenterPadding && m_Position.y <= m_CurrentTileIndex.y * 32 + g_TileCenterPadding)
		YisCenter = true;

	return XisCenter && YisCenter;
}

void dae::TransformComponent::SetVelocity(glm::vec3 direction)
{
	m_Velocity = direction; 
	if (GetDirectionFromVelocity() != Direction::NONE) 
	{
		/*if (m_PreviousDirection != m_CurrentDirection)*/
			m_PreviousDirection = m_CurrentDirection;

		m_CurrentDirection = GetDirectionFromVelocity();
	}
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

dae::iVector2 dae::TransformComponent::GetNextTileDirectionFromVelocity() const
{
	iVector2 dir{ 0,0 };

	if (m_Velocity.x != 0)
		dir.x = static_cast<int>(m_Velocity.x) / abs(static_cast<int>(m_Velocity.x));
	if (m_Velocity.y != 0)
		dir.y = static_cast<int>(m_Velocity.y) / abs(static_cast<int>(m_Velocity.y));

	return dir;
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