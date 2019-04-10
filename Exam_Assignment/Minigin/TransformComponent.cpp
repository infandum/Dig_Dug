#include "MiniginPCH.h"
#include "Components.h"

void dae::TransformComponent::Update(float& deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	/*if (m_Position.x == 13 * 32)
		isMoving = false;
	if (m_Position.x == 0 * 32)
		isMoving = false;
	if (m_Position.x == 13 * 32)
		isMoving = false;
	if (m_Position.x == 13 * 32)
		isMoving = false;*/
	/*if (isMoving)
	{ 
		m_Position.x += ( m_OffSet.x * m_Speed ) * deltaTime;
		m_Position.y += ( m_OffSet.y * m_Speed ) * deltaTime;
	}*/

	/*if (m_Direction.x != 0)
	{
		m_Position.x += (deltaTime * m_Direction.x);
	}
	if (m_Direction.y != 0)
	{
		m_Position.y += (deltaTime * m_Direction.y);
	}*/

	
	glm::vec3 AdjustedVelocity = m_Direction;
	//bool xAlligned = true;
	//bool yAlligned = true;
	//bool AdjustingY = false;
	//bool AdjustingX = false;
	//	// check allignment 
	//	auto modulo = fmod(m_Position.y, 32);
	//	if (modulo > 16)
	//		modulo = 32 - modulo;
	//	if (modulo > 2.f) {
	//		yAlligned = false;
	//		double intpart;
	//		auto fracpart = modf(m_Position.y / 32, &intpart);
	//		if (fracpart < 0.5) {
	//			AdjustingY = true;
	//			AdjustedVelocity.y = -1;
	//			AdjustedVelocity.x = 0;
	//		}
	//		else {
	//			AdjustedVelocity.y = 1;
	//			AdjustedVelocity.x = 0;
	//		}

	//	}

	//

	////Check if able to turn
	//	// check allignment 
	//	modulo = fmod(m_Position.x, 32);
	//	if (modulo > 16)
	//		modulo = 32 - modulo;
	//	if (modulo > 2.0f) {
	//		xAlligned = false;
	//		double intpart;
	//		auto fracpart = modf(m_Position.x / 32, &intpart);
	//		if (fracpart < 0.5) {
	//			AdjustingX = true;
	//			AdjustedVelocity.x = -1;
	//			AdjustedVelocity.y = 0;
	//		}
	//		else {
	//			AdjustedVelocity.x = 1;
	//			AdjustedVelocity.y = 0;
	//		}
	//	}
	//

	//Boundary control
	if(isMoving)
	{
		auto newPositionX = m_Position.x + (deltaTime * AdjustedVelocity.x);
		auto newPositionY = m_Position.y + (deltaTime * AdjustedVelocity.y);
		float MIN_POSITION_X = 0;
		float MAX_POSITION_X = 448 - 32;
		float MIN_POSITION_Y = (32 * (2));
		float MAX_POSITION_Y = 576 - (32 + 32);

		if (newPositionX < MIN_POSITION_X)
			newPositionX = MIN_POSITION_X;
		if (newPositionX > MAX_POSITION_X)
			newPositionX = MAX_POSITION_X;
		
		if (newPositionY < MIN_POSITION_Y)
			newPositionY = MIN_POSITION_Y;
		if (newPositionY > MAX_POSITION_Y)
			newPositionY = MAX_POSITION_Y;

		m_Position = { newPositionX, newPositionY, m_Position.z };
	}
}

void dae::TransformComponent::SetPosition(float x, float y, float z)
{
	m_Position = glm::vec3(x, y, z);
}


bool dae::TransformComponent::MoveToTile(unsigned int x, unsigned int y)
{
	isMoving = true;

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
		isMoving = false;  
		return true;
	}
	return false;
}
