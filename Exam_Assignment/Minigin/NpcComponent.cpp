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
	m_IsReset = true;
}


void dae::NpcComponent::Reset()
{
	m_IsDead = false;
	m_IsHit = false;
	m_isGhosting = false;
	m_IsReset = true;
	m_player = nullptr;
	m_Hits = 0;

	auto a = GetGameObject();
	a->Enable(true);
	GetGameObject()->GetRenderer()->EnableRender(true);
	GetGameObject()->GetCollision()->EnableCollision(true);
	GetGameObject()->GetTransform()->Reset();
	GetGameObject()->GetComponent<MoveComponent>()->Reset();
	GetGameObject()->GetSprite()->onNotify(NotifyEvent::EVENT_SPAWN);
}

void dae::NpcComponent::onNotify(GameObject& , NotifyEvent& )
{
}

void dae::NpcComponent::Initialize()
{
	m_pLevelManager = ServiceLocator::GetLevelManager();
	m_pLevelManager->AddEntity(this);

	m_CrushedPoints[0] = 0;
	m_CrushedPoints[1] = 1000;
	m_CrushedPoints[2] = 2500;
	m_CrushedPoints[3] = 4000;
	m_CrushedPoints[4] = 6000;
	m_CrushedPoints[5] = 8000;
	m_CrushedPoints[6] = 10000;
	m_CrushedPoints[7] = 12000;
	m_CrushedPoints[8] = 15000;

	switch (m_Type)
	{
	case NPCType::POOKA:
			GetGameObject()->GetSprite()->onNotify(NotifyEvent::EVENT_IDLE);

		break;
	case NPCType::FYGAR:
			GetGameObject()->GetSprite()->onNotify(NotifyEvent::EVENT_IDLE);

		break;
	default:

		break;
	}
}

void dae::NpcComponent::Update(float )
{
	if (m_IsReset)
	{
		GetGameObject()->GetSprite()->onNotify(NotifyEvent::EVENT_SPAWN);
		m_IsReset = false;
		return;
	}	

	const auto index = GetGameObject()->GetTransform()->GetPositionIndex();
	const auto tile = m_pLevelManager->GetTile(index.x, index.y);
	if (tile->GetTileState() == TileState::FREE)
	{
		m_isGhosting = true;
	}

	switch (m_Type)
	{
	case NPCType::POOKA:

		if (!m_IsHit && !m_IsCrushed)
		{
			GetGameObject()->GetSprite()->onNotify(NotifyEvent::EVENT_MOVE);
			GetGameObject()->GetComponent<MoveComponent>()->SetMovementInput({ 1, 0, 0 });
			if (GetGameObject()->GetComponent<MoveComponent>()->CheckTileSwapping() && GetGameObject()->GetComponent<MoveComponent>()->IsCentered())
			{
				GetGameObject()->GetComponent<MoveComponent>()->SetMovementInput({ 0, 0, 0 });
				GetGameObject()->GetSprite()->onNotify(NotifyEvent::EVENT_IDLE);
			}
		}

		break;
	case NPCType::FYGAR:
		if (!m_IsHit && !m_IsCrushed)
		{
			GetGameObject()->GetSprite()->onNotify(NotifyEvent::EVENT_MOVE);
			GetGameObject()->GetComponent<MoveComponent>()->SetMovementInput({ 1, 0, 0 });
			if (GetGameObject()->GetComponent<MoveComponent>()->CheckTileSwapping() && GetGameObject()->GetComponent<MoveComponent>()->IsCentered())
			{
				GetGameObject()->GetComponent<MoveComponent>()->SetMovementInput({ 0, 0, 0 });
				GetGameObject()->GetSprite()->onNotify(NotifyEvent::EVENT_IDLE);
			}
		}
		
		break;
	case NPCType::ROCK:
		GetGameObject()->GetSprite()->onNotify(NotifyEvent::EVENT_IDLE);

		break;
	default:

		break;
	}
	
}

void dae::NpcComponent::EnableCrushing(const bool& enable)
{
	m_IsCrushed = enable;
	GetGameObject()->GetComponent<MoveComponent>()->SetMovementInput({ 0, 1, 0 });
}

void dae::NpcComponent::Hit(PlayerComponent* player)
{

	m_player = player;

	m_IsHit = true;
}

int dae::NpcComponent::PointCalculation() const
{
	int points;
	switch (m_Type)
	{
	case NPCType::POOKA:

		points = m_Points + (100 * (((GetGameObject()->GetTransform()->GetPositionIndex().y - 2) / 4)));

		break;
	case NPCType::FYGAR:

		points = m_Points + (200 * (((GetGameObject()->GetTransform()->GetPositionIndex().y - 2) / 4)));

		if (m_player->GetGameObject()->GetTransform()->GetPositionIndex().y == GetGameObject()->GetTransform()->GetPositionIndex().y)
			points *= 2;

		break;

	case NPCType::ROCK:

		points = m_CrushedPoints.at(m_Hits);

		break;
	default:
		
		points = 0;

		break;
	}

	return points;
}

void dae::NpcComponent::Dead()
{
	m_IsDead = true;

	if(m_player == nullptr)
	{
		std::cout << "NpcComponent>>Dead:: No Player to give points too?\n";
		return;
	}

	const auto points = PointCalculation();
	m_player->AddPoints(points);
	
}
