#include "MiniginPCH.h"
#include "Components.h"
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
	m_IsCrushed = false;
	m_IsDead = false;
	m_IsHit = false;
	m_IsInflate = false;
	m_IsFalling = false;
	m_player = nullptr;
	m_Hits = 0;

	
	
	m_isGhosting = false;
	m_IsIdle = true;
	m_IsMoving = false;
	m_IsChasing = false;
	m_IsChangeTunnel = false;
	m_ActionTimer = 0.f;

	m_NewDir = Direction::NONE;
	m_pTarget = nullptr;
	m_TargetLocation = { 0,0 };

	const auto go = GetGameObject();
	go->Enable(true);
	go->GetRenderer()->EnableRender(true);
	go->GetCollision()->EnableCollision(true);
	go->GetTransform()->Reset();
	go->GetComponent<MoveComponent>()->Reset();
	go->GetSprite()->onNotify(NotifyEvent::EVENT_SPAWN);

	m_IsReset = true;
}

void dae::NpcComponent::onNotify(GameObject& , NotifyEvent& )
{
}

void dae::NpcComponent::Initialize()
{
	m_pLevelManager = ServiceLocator::GetLevelManager();
	m_pLevelManager->AddEntity(this);

	m_pSprite = GetGameObject()->GetSprite();
	m_pMove = GetGameObject()->GetComponent<MoveComponent>().get();

	m_CrushedPoints[0] = 0;
	m_CrushedPoints[1] = 1000;
	m_CrushedPoints[2] = 2500;
	m_CrushedPoints[3] = 4000;
	m_CrushedPoints[4] = 6000;
	m_CrushedPoints[5] = 8000;
	m_CrushedPoints[6] = 10000;
	m_CrushedPoints[7] = 12000;
	m_CrushedPoints[8] = 15000;

	GetGameObject()->GetSprite()->onNotify(NotifyEvent::EVENT_IDLE);
}


void dae::NpcComponent::Update(float deltaTime)
{
	if (m_IsReset)
	{
		GetGameObject()->GetSprite()->onNotify(NotifyEvent::EVENT_SPAWN);
		m_IsReset = false;
		m_ActionMaxTime = RandomFloatBetween(1.0f, m_IdleMaxTime);
		return;
	}	

	

	
	//TODO: FIX VERTICAL STATE BUG

	if(m_Type != NPCType::ROCK)
		if (!m_IsHit && !m_IsCrushed)
		{
			if (m_IsIdle)
			{
				GetGameObject()->GetSprite()->onNotify(NotifyEvent::EVENT_IDLE);

				if (m_ActionTimer >= m_ActionMaxTime)
				{
					auto rnd = RandomIntBetween(0, 100);
					if (rnd <= 50.f)
					{
						if (!m_IsMoving)
						{
							std::cout << GetGameObject()->GetName() << " IDLE MOVING\n";
							m_NewDir = static_cast<Direction>(rand() % static_cast<int>(Direction::NONE));
							m_ActionMaxTime = RandomFloatBetween(0.25f, m_MovingMaxTime);

							GetGameObject()->GetSprite()->onNotify(NotifyEvent::EVENT_MOVE);
							m_IsMoving = true;
							m_IsIdle = false;
							m_ActionTimer = 0.f;						
						}
					}
					else if(rnd <= 75.f)
					{
						if (!m_IsChasing)
						{
							std::cout << GetGameObject()->GetName() << " CHASE MOVING\n";
							if (m_pLevelManager->GetPlayerCount() > 1)
							{
								rnd = RandomIntBetween(0, 100 * static_cast<int>(m_pLevelManager->GetPlayerCount()));
								if (rnd <= 50)
								{

									SetChaseTarget(0);
								}
								else
								{
									SetChaseTarget(1);
								}

							}
							else
							{
								SetChaseTarget(0);
							}
						}
					}
					else
					{
						if (!m_IsChangeTunnel)
						{
							std::cout << GetGameObject()->GetName() << " GHOSTING MOVING\n";
							auto tiles = m_pLevelManager->GetTilesByState(TileState::USED);
							rnd = RandomIntBetween(0, 100 * static_cast<int>(tiles.size()) / 100) % tiles.size();
							float distance = static_cast<float>(sqrt(
																pow(tiles[rnd]->GetPositionIndex().x - GetGameObject()->GetTransform()->GetPositionIndex().x, 2) +
																pow(tiles[rnd]->GetPositionIndex().y - GetGameObject()->GetTransform()->GetPositionIndex().y, 2)));
							
							while (distance < 6.f)
							{
								rnd = RandomIntBetween(0, 100 * static_cast<int>(tiles.size()) / 100) % tiles.size();
								distance = static_cast<float>(sqrt(
																pow(tiles[rnd]->GetPositionIndex().x - GetGameObject()->GetTransform()->GetPositionIndex().x, 2) + 
																pow(tiles[rnd]->GetPositionIndex().y - GetGameObject()->GetTransform()->GetPositionIndex().y, 2)));
							}

							m_TargetLocation = tiles[rnd]->GetPositionIndex();

							m_ActionMaxTime = RandomFloatBetween(0.25f, m_MovingMaxTime);
							GetGameObject()->GetSprite()->onNotify(NotifyEvent::EVENT_MOVE);
							m_IsChangeTunnel = true;
							m_IsIdle = false;
							
						}
					}
					//FLIP DIRECTION


					
				}

				m_ActionTimer += deltaTime;
			}
			else if(m_IsMoving)
			{
				m_ActionTimer += deltaTime;
			}
			else if (m_IsChasing)
			{
				m_ActionTimer += deltaTime;
			}

			ChangeTunnel();
			if(!m_IsChangeTunnel)
			{
				Moving();
				Chasing();
			}
			
		}
		else
		{
			m_pMove->SetMovementInput(0, 0, 0);
			m_IsIdle = true;
			m_IsMoving = false;
			m_IsChasing = false;
			m_IsChangeTunnel = false;
		}


		const auto index = GetGameObject()->GetTransform()->GetPositionIndex();
		const auto tile = m_pLevelManager->GetTile(index.x, index.y);

		if (tile->GetTileState() == TileState::FREE)
		{
			m_isGhosting = true;
		}
	
}


void dae::NpcComponent::StopMovement()
{
	m_pMove->SetMovementInput(0, 0, 0);
	m_IsIdle = true;
	m_IsMoving = false;
	GetGameObject()->GetSprite()->onNotify(NotifyEvent::EVENT_IDLE);
}

void dae::NpcComponent::Moving()
{

	const auto index = GetGameObject()->GetTransform()->GetPositionIndex();
	const auto nextTile = m_pLevelManager->GetTile(index.x + static_cast<int>(DirectionAxis(m_NewDir).x), index.y + static_cast<int>(DirectionAxis(m_NewDir).y));
	if (m_IsMoving)
	{
		if (nextTile)
		{
			if (nextTile->GetTileState() != TileState::USED && GetGameObject()->GetComponent<MoveComponent>()->IsCentered())
			{
				m_ActionTimer = 0.f;
				StopMovement();
				return;
			}

			if (m_ActionTimer >= m_ActionMaxTime)
			{
				m_ActionTimer = 0.f;
				StopMovement();
				return;
			}

			if (nextTile->GetTileState() == TileState::USED)
			{
				m_pMove->SetMovementInput(DirectionAxis(m_NewDir));
				m_pMove->SetCurrentDirection(m_NewDir);
			}
			else if (nextTile->GetTileState() != TileState::USED && GetGameObject()->GetComponent<MoveComponent>()->IsCentered())
			{
				m_ActionTimer = 0.f;
				StopMovement();
			}
		}
		else
		{
			m_ActionTimer = 0.f;
			m_pMove->FlipDirection();
			StopMovement();
		}

	}
	else
	{
		StopMovement();
	}
}

void dae::NpcComponent::SetChaseTarget(const int& index)
{
	m_pTarget = m_pLevelManager->GetPlayer(index);
	m_ActionMaxTime = RandomFloatBetween(0.25f, m_MovingMaxTime);
	GetGameObject()->GetSprite()->onNotify(NotifyEvent::EVENT_MOVE);
	m_IsChasing = true;
	m_IsIdle = false;
	m_ActionTimer = 0.f;
}

void dae::NpcComponent::StopChasing()
{
	m_pMove->SetMovementInput(0, 0, 0);
	m_IsIdle = true;
	m_IsChasing = false;
	//GetGameObject()->GetSprite()->onNotify(NotifyEvent::EVENT_IDLE);
}

void dae::NpcComponent::Chasing()
{

	if (m_IsChasing)
	{
		m_TargetLocation = m_pTarget->GetGameObject()->GetTransform()->GetPositionIndex();

		const auto index = GetGameObject()->GetTransform()->GetPositionIndex();

		const auto DistanceX = m_TargetLocation.x - index.x;
		const auto DistanceY = m_TargetLocation.y - index.y;

		float DirX = 0;
		float DirY = 0;

		if (DistanceX > 0)
			DirX = static_cast<float>(DistanceX / abs(DistanceX));

		if (DistanceY > 0)
			DirY = static_cast<float>(DistanceY / abs(DistanceY));

		const auto XTile = m_pLevelManager->GetTile(index.x + static_cast<int>(DirX), index.y);
		const auto YTile = m_pLevelManager->GetTile(index.x, index.y + static_cast<int>(DirY));

		if (XTile && YTile)
		{
			GetGameObject()->GetSprite()->onNotify(NotifyEvent::EVENT_MOVE);

			if (XTile->GetTileState() != TileState::USED && YTile->GetTileState() != TileState::USED && GetGameObject()->GetComponent<MoveComponent>()->IsCentered())
			{
				m_ActionTimer = 0.f;
				StopMovement();
				return;
			}

			if (m_ActionTimer >= m_ActionMaxTime)
			{
				m_ActionTimer = 0.f;
				StopChasing();
				return;
			}

			if (XTile->GetTileState() == TileState::USED)
			{
				m_pMove->SetMovementInput(DirX, 0);
				m_pMove->SetCurrentDirection(AxisDirection({ DirX, 0, 0 }));
			}
			else if (YTile->GetTileState() == TileState::USED)
			{
				m_pMove->SetMovementInput(0, DirY);
				m_pMove->SetCurrentDirection(AxisDirection({ 0, DirY, 0 }));
			}
			else if (XTile->GetTileState() != TileState::USED && YTile->GetTileState() != TileState::USED && GetGameObject()->GetComponent<MoveComponent>()->IsCentered())
			{
				m_ActionTimer = 0.f;
				StopChasing();
			}
		}
		else
		{
			m_ActionTimer = 0.f;
			m_pMove->FlipDirection();
			StopChasing();
		}

	}
	else
	{
		StopChasing();
	}
}

void dae::NpcComponent::ChangeTunnel()
{
	if (m_IsChangeTunnel)
	{
		const auto index = GetGameObject()->GetTransform()->GetPositionIndex();

		const auto DistanceX = m_TargetLocation.x - index.x;
		const auto DistanceY = m_TargetLocation.y - index.y;
		float DirX = 0;
		float DirY = 0;

		if(DistanceX > 0 )
			DirX = static_cast<float>(DistanceX / abs(DistanceX));
		
		if(DistanceY > 0)
			DirY = static_cast<float>(DistanceY / abs(DistanceY));

		const auto XTile = m_pLevelManager->GetTile(index.x + static_cast<int>(DirX), index.y);
		const auto YTile = m_pLevelManager->GetTile(index.x, index.y + static_cast<int>(DirY));

		if (XTile && YTile)
		{
			int rnd = RandomIntBetween(0, 100);
			bool m_FirstHor = false;
			if(GetGameObject()->GetComponent<MoveComponent>()->IsCentered())
			{
				if(rnd <= 50)
				{
					m_FirstHor = true;
				}
			}

			if ((XTile->GetTileState() != TileState::OCCUPIED || XTile->GetTileState() != TileState::BLOCKED) && DirX > 0 && m_FirstHor && GetGameObject()->GetComponent<MoveComponent>()->IsCentered())
			{
				m_pMove->SetMovementInput(DirX, 0);
				m_pMove->SetCurrentDirection(AxisDirection({ DirX, 0, 0 }));
			}
			else if ((YTile->GetTileState() == TileState::OCCUPIED || YTile->GetTileState() != TileState::BLOCKED) && DirY > 0 && GetGameObject()->GetComponent<MoveComponent>()->IsCentered())
			{
				m_pMove->SetMovementInput(0, DirY);
				m_pMove->SetCurrentDirection(AxisDirection({ 0, DirY, 0 }));
			}
			else if (DirX <= 0 && DirY <= 0 && GetGameObject()->GetComponent<MoveComponent>()->IsCentered())
			{
				m_ActionTimer = 0.f;
				m_IsChangeTunnel = false;
				m_IsIdle = true;
				m_pMove->SetMovementInput(0, 0);
			}
		}
		else
		{
			m_IsChangeTunnel = false;
			m_IsIdle = true;
			m_pMove->SetMovementInput(0, 0);
		}
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
