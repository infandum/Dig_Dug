#include "MiniginPCH.h"
#include "NpcComponent.h"
#include "GameObject.h"
#include "ServiceLocator.h"

dae::NpcComponent::NpcComponent(NPCType type) :m_Type(type)
{
	switch (type)
	{
	case NPCType::POOKA:
		m_Points = NPCBasePoints::POINTS_POOKA;
		break;
	case NPCType::FYGAR:
		m_Points = NPCBasePoints::POINTS_FYGAR;
		break;
	default:
		m_Points = 0;
		break;
	}
}

void dae::NpcComponent::Hit(PlayerComponent* player)
{
	if(m_IsHit)
		if (GetGameObject()->GetSprite()->IsAnimationEnded() && typeid(*GetGameObject()->GetSprite()->GetCurrentState()) == typeid(DeadEnemyState))
		{
			Dead();
			int points = 0;
			switch (m_Type)
			{
			case NPCType::POOKA:

				points = m_Points + (100 * (((GetGameObject()->GetTransform()->GetPositionIndex().y - 2) / 4)));

				break;
			case NPCType::FYGAR:

				points = m_Points + (200 * (((GetGameObject()->GetTransform()->GetPositionIndex().y - 2) / 4)));

				if (player->GetGameObject()->GetTransform()->GetPositionIndex().y == GetGameObject()->GetTransform()->GetPositionIndex().y)
					points *= 2;

				break;
			default:

				points = 0;

				break;
			}
			
			player->AddPoints(points);
		}

	m_IsHit = true;
}

void dae::NpcComponent::Reset()
{
	m_IsDead = false;
	m_IsHit = false;
	m_isGhosting = false;

	GetGameObject()->Enable(true);
	GetGameObject()->GetTransform()->Reset();
	GetGameObject()->GetComponent<MoveComponent>()->Reset();

	switch (m_Type)
	{
	case NPCType::POOKA:
		GetGameObject()->GetSprite()->onNotify(NotifyEvent::EVENT_SPAWN);

		break;
	case NPCType::FYGAR:
		GetGameObject()->GetSprite()->onNotify(NotifyEvent::EVENT_SPAWN);

		break;
	default:

		break;
	}
}

void dae::NpcComponent::onNotify(GameObject & , NotifyEvent & )
{
}

void dae::NpcComponent::Initialize()
{
	auto tiles = ServiceLocator::GetLevelManager();
	tiles->AddEntity(this);

	switch (m_Type)
	{
	case NPCType::POOKA:
		if (!m_IsHit)
			GetGameObject()->GetSprite()->onNotify(NotifyEvent::EVENT_IDLE);

		break;
	case NPCType::FYGAR:
		if (!m_IsHit)
			GetGameObject()->GetSprite()->onNotify(NotifyEvent::EVENT_IDLE);

		break;
	default:

		break;
	}
}

void dae::NpcComponent::Update(float )
{
	if(m_IsDead)
	{
		GetGameObject()->Enable(false);
	}

	

	switch (m_Type)
	{
	case NPCType::POOKA:
		if (!m_IsHit)
			GetGameObject()->GetSprite()->onNotify(NotifyEvent::EVENT_IDLE);
		
		break;
	case NPCType::FYGAR:
		if (!m_IsHit)
			GetGameObject()->GetSprite()->onNotify(NotifyEvent::EVENT_IDLE);
		
		break;
	default:

		break;
	}
	
}

void dae::NpcComponent::Dead()
{
	m_IsDead = true;
	
}
