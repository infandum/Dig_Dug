#include "MiniginPCH.h"
#include "Components.h"
#include "ServiceLocator.h"
#include <cmath>
#include "LevelManager.h"
#include "GameObject.h"

void dae::MoveComponent::Reset(Direction dir)
{
	SetVelocity({ 0,0,0 });

	m_CurrentDirection = dir;
	m_PreviousDirection = dir;
}

void dae::MoveComponent::onNotify(GameObject& , NotifyEvent& )
{

}

void dae::MoveComponent::Initialize()
{
	m_pTransform = GetGameObject()->GetTransform();
	m_pLevelManager = ServiceLocator::GetLevelManager();

}

void dae::MoveComponent::Update(float deltaTime)
{
	m_pTransform = GetGameObject()->GetTransform();
	
	if (m_IsStatic)
	{
		const auto tile = m_pLevelManager->GetTile(m_pTransform->GetPositionIndex().x, m_pTransform->GetPositionIndex().y);
		if (tile->GetTileState() != TileState::OCCUPIED && !GetGameObject()->GetParent())
			tile->SetTileState(TileState::OCCUPIED);
	}
	else
	{
		glm::vec3 velocity{ 0 };
		if (m_Velocity.x != 0 || m_Velocity.y != 0)
			if (m_IsOmniDirectional || GetGameObject()->GetParent())
				velocity = MoveOmniDirectional();
			else
				velocity = MoveDirectional();


		if (m_IsMoving)
		{
			if (!CheckOccupiedTileMove())
				return;

			CheckTileSwapping();

			double newPositionX;
			double newPositionY;

			if (GetGameObject()->GetParent())
			{
				if (GetGameObject()->GetIsFollowingParent())
				{
					newPositionX = m_pTransform->GetLocalPosition().x + round(deltaTime * velocity.x);
					newPositionY = m_pTransform->GetLocalPosition().y + round(deltaTime * velocity.y);
				}
				else
				{
					newPositionX = m_pTransform->GetPosition().x + round(deltaTime * velocity.x);
					newPositionY = m_pTransform->GetPosition().y + round(deltaTime * velocity.y);
				}
			}
			else
			{
				newPositionX = m_pTransform->GetPosition().x + round(deltaTime * velocity.x);
				newPositionY = m_pTransform->GetPosition().y + round(deltaTime * velocity.y);
			}
				

			

			BorderControl(newPositionX, newPositionY);

			if (GetGameObject()->GetParent())
				if (GetGameObject()->GetIsFollowingParent())
					m_pTransform->SetLocalPosition(static_cast<float>(newPositionX), static_cast<float>(newPositionY), m_pTransform->GetLocalPosition().z);
				else
					m_pTransform->SetPosition(static_cast<float>(newPositionX), static_cast<float>(newPositionY), m_pTransform->GetPosition().z);
			else
				m_pTransform->SetPosition( static_cast<float>(newPositionX), static_cast<float>(newPositionY), m_pTransform->GetPosition().z );
			m_IsMoving = false;
		}
	}
}


glm::vec3 dae::MoveComponent::MoveDirectional()
{
	//TODO: Fix Minor freeze bug might be lag?
	glm::vec3 velocity{ 0 };
	m_IsMoving = true;
	if (m_Velocity.x != 0)
	{
		//Check if object is Aligned with center of tile on the Y-axis
		const auto modulo = fmod(round(m_pTransform->GetPosition().y), 32.0);
		isYonTileCenter = true;
		if (modulo > 1 && modulo < 31)
			isYonTileCenter = false;
		//IF not aligned first move object to aligned tile central Y-axis
		//ELSE move to input direction
		if (!isYonTileCenter)
		{
			if (modulo >= 16)
				velocity.y = m_MoveSpeed;
			else
				velocity.y = -m_MoveSpeed;
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
		const auto modulo = fmod(round(m_pTransform->GetPosition().x), 32.0);
		//IF not aligned first move object to aligned tile central X-axis
		//ELSE move to input direction
		isXonTileCenter = true;
		if (modulo > 1 && modulo < 31)
			isXonTileCenter = false;
		if (!isXonTileCenter)
		{
			if (modulo >= 16)
				velocity.x = m_MoveSpeed;
			else
				velocity.x = -m_MoveSpeed;
		}
		else
		{
			velocity.x = m_Velocity.x;
			velocity.y = m_Velocity.y;
		}
	}
	return velocity;
}

glm::vec3 dae::MoveComponent::MoveOmniDirectional()
{
	glm::vec3 velocity{ 0 };
	m_IsMoving = true;
	velocity.x = m_Velocity.x;
	velocity.y = m_Velocity.y;
	return velocity;
}

bool dae::MoveComponent::IsCentered() const
{
	bool XisCenter = false;
	bool YisCenter = false;

	if (m_pTransform->GetPosition().x >= m_pTransform->GetPositionIndex().x * 32 - m_MovePadding && m_pTransform->GetPosition().x <= m_pTransform->GetPositionIndex().x * 32 + m_MovePadding)
		XisCenter = true;

	if (m_pTransform->GetPosition().y >= m_pTransform->GetPositionIndex().y * 32 - m_MovePadding && m_pTransform->GetPosition().y <= m_pTransform->GetPositionIndex().y * 32 + m_MovePadding)
		YisCenter = true;

	return XisCenter && YisCenter;
}

void dae::MoveComponent::SetVelocity(glm::vec3 direction)
{
	m_Velocity = direction;
	if (GetDirectionFromVelocity() != Direction::NONE)
	{
		m_PreviousDirection = m_CurrentDirection;
		m_CurrentDirection = GetDirectionFromVelocity();
	}
}

dae::Direction dae::MoveComponent::GetDirectionFromVelocity() const
{
	Direction dir;
	if (m_Velocity.x < 0.0f)
		dir = Direction::LEFT;
	else if (m_Velocity.x > 0.0f)
		dir = Direction::RIGHT;
	else if (m_Velocity.y < 0.0f)
		dir = Direction::UP;
	else if (m_Velocity.y > 0.0f)
		dir = Direction::DOWN;
	else
		dir = Direction::NONE;

	return dir;
}

void dae::MoveComponent::MoveToTile(unsigned int xIndex, unsigned int yIndex)
{
	glm::vec3 velocity{ 0 };
	if (m_pTransform->GetPositionIndex().x == static_cast<int>(xIndex) && m_pTransform->GetPositionIndex().y == static_cast<int>(yIndex))
		if (IsCentered())
		{
			m_Velocity = velocity;
			return;
		}


	m_IsMoving = true;
	iVector2 vec = { static_cast<int>((xIndex * 32) - m_pTransform->GetPosition().x) ,  static_cast<int>((yIndex * 32) - m_pTransform->GetPosition().y) };
	const float distance = vec.Magnitude();
	velocity.x = (m_MoveSpeed / distance) * vec.x;
	velocity.y = (m_MoveSpeed / distance) * vec.y;

	SetVelocity({ velocity.x, velocity.y, 0 });
}


bool dae::MoveComponent::CheckTileSwapping()
{
	const iVector2 nextTileIndex = { m_pTransform->GetPositionIndex().x + static_cast<int>(DirectionAxis(m_CurrentDirection).x), m_pTransform->GetPositionIndex().y + static_cast<int>(DirectionAxis(m_CurrentDirection).y) };

	m_pLevelManager = ServiceLocator::GetLevelManager();
	const auto currTile = m_pLevelManager->GetTile(m_pTransform->GetPositionIndex().x, m_pTransform->GetPositionIndex().y);
	const auto nextTile = m_pLevelManager->GetTile(nextTileIndex.x, nextTileIndex.y);
	/*if(GetGameObject()->GetInput())
	{
		std::cout << "CURRENT TILE: X =" << m_pTransform->GetPositionIndex().x << " , Y = " << m_pTransform->GetPositionIndex().y << "\n";
		std::cout << "NEXT TILE: X = " << m_pTransform->GetPositionIndex().x + GetNextTileDirectionFromVelocity().x << " , Y = " << m_pTransform->GetPositionIndex().y + GetNextTileDirectionFromVelocity().y << "\n";
	}*/
	
	if (nextTile != nullptr)
	{
		if (nextTile->GetTileState() == TileState::FREE)
		{
			isSwappingTile = true;
		}
		if (nextTile->GetTileState() == TileState::USED)
		{
			isSwappingTile = false;
			if (!currTile->GetIsConnectedBorder(GetCurrentDirection()))
				isSwappingTile = true;
		}

		if (nextTile->GetTileState() == TileState::EMPITY)
		{
			isSwappingTile = false;
		}
	}
	return isSwappingTile;
}


bool dae::MoveComponent::CheckOccupiedTileMove() const
{
	const iVector2 nextTileIndex = { m_pTransform->GetPositionIndex().x + static_cast<int>(DirectionAxis(m_CurrentDirection).x), m_pTransform->GetPositionIndex().y + static_cast<int>(DirectionAxis(m_CurrentDirection).y) };
	const auto nextTile = m_pLevelManager->GetTile(nextTileIndex.x, nextTileIndex.y);
	if (nextTile != nullptr)
		if (nextTile->GetTileState() == TileState::OCCUPIED && IsCentered())
			return false;

	return true;
}

void dae::MoveComponent::BorderControl(double& posX, double& posY) const
{
	if(GetGameObject()->GetComponent<CollisionComponent>() && GetGameObject()->GetComponent<CollisionComponent>()->IsTrigger())
		return;

	const int MIN_POSITION_X = 0;
	const int MAX_POSITION_X = 448 - 32;
	const int MIN_POSITION_Y = 32;
	const int MAX_POSITION_Y = 576 - (32 + 32);

	if (posX < MIN_POSITION_X)
		posX = MIN_POSITION_X;

	if (posX > MAX_POSITION_X)
		posX = MAX_POSITION_X;

	if (posY < MIN_POSITION_Y)
		posY = MIN_POSITION_Y;

	if (posY > MAX_POSITION_Y)
		posY = MAX_POSITION_Y;
}
