#include "MiniginPCH.h"
#include "Components.h"
#include "GameObject.h"
#include "ServiceLocator.h"
#include "PlayerStates.h"

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
	m_IsCharging = false;
	m_isAttacking = false;
	m_ActionTimer = 0.f;
	m_MaxActionTimer = 0.f;

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

	if(m_Type == NPCType::FYGAR)
	{
		m_AttackSprite = std::make_shared<GameObject>();
		m_Attack = std::make_shared<GameObject>();
		m_Attack->SetName("Fire");
		m_Attack->AddComponent(std::make_shared<RenderComponent>());
		m_Attack->AddComponent(std::make_shared<CollisionComponent>(true));
		m_Attack->AddComponent(std::make_shared<TransformComponent>(GetGameObject()->GetTransform()->GetPosition().x, GetGameObject()->GetTransform()->GetPosition().y));
		m_Attack->AddComponent(std::make_shared<MoveComponent>());
		m_Attack->GetCollision()->SetSize({ 128, 32 });
		GetGameObject()->AddChild(m_Attack);


		m_AttackSprite->SetName("Fire Sprite");
		m_AttackSprite->AddComponent(std::make_shared<RenderComponent>());
		m_AttackSprite->AddComponent(std::make_shared<TransformComponent>(-32.f, 0.f));
		m_AttackSprite->AddComponent(std::make_shared<MoveComponent>());
		m_AttackSprite->AddComponent(std::make_shared<TextureComponent>(ServiceLocator::GetResourceManager()->GetTexture(02)));
		m_AttackSprite->AddComponent(std::make_shared<SpriteComponent>(WeaponState()));
		m_AttackSprite->GetComponent<SpriteComponent>()->SetAnimationToState(31, std::make_shared<WeaponState>());
		m_AttackSprite->GetComponent<SpriteComponent>()->Pause();

		GetGameObject()->AddChild(m_AttackSprite);
	}
}

void dae::NpcComponent::StartAttacking()
{
	
	if (m_pLevelManager->GetPlayerCount() > 1)
	{
		if (RandomIntBetween(0, 100 * static_cast<int>(m_pLevelManager->GetPlayerCount())) <= 50)
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


	m_NewDir = m_pTarget->GetGameObject()->GetTransform()->GetPositionIndex().x >= GetGameObject()->GetTransform()->GetPositionIndex().x ? Direction::RIGHT : Direction::LEFT;
	GetGameObject()->GetComponent<MoveComponent>()->SetCurrentDirection(m_NewDir);
	m_ActionMaxTime = RandomFloatBetween(0.75f, m_AttackMaxTime);
	GetGameObject()->GetSprite()->onNotify(NotifyEvent::EVENT_ACTION);
	m_IsCharging = true;
	m_IsIdle = false;
	m_ActionTimer = 0.f;
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

	
	if (m_Type == NPCType::ROCK)
		if (!m_IsHit && !m_IsCrushed)
			GetGameObject()->GetSprite()->onNotify(NotifyEvent::EVENT_IDLE);
	
	if (m_Type != NPCType::ROCK)
		if (!m_IsHit && !m_IsCrushed)
		{	
	
			if (m_IsIdle)
			{
				GetGameObject()->GetSprite()->onNotify(NotifyEvent::EVENT_IDLE);
				if (m_ActionTimer >= m_ActionMaxTime)
				{
					auto rnd = RandomIntBetween(0, 100);
					if (rnd <= 65.f )
					{
						if (!m_IsChasing)
						{
							StartChasing();
						}
					}
					else if (rnd <= 85.f && !m_isGhosting  && m_Type == NPCType::FYGAR)
					{
						if (!m_IsCharging)
						{
							StartAttacking();
						}
						
					}
					else if (rnd <= 90.f)
					{
						if (!m_IsChangeTunnel)
						{
							StartTunneling();
						}
					}
					else
					{
						if (!m_IsMoving)
						{
							StartIdleMove();
						}
					}
					
							
				}
				else
				{
					m_ActionTimer += deltaTime;
				}

			}
			else
			{
				/*if(m_MovingMaxTime >= m_MaxActionMaxTime)
				{
					m_IsIdle = true;
					m_IsMoving = false;
					m_IsChasing = false;
					m_IsChangeTunnel = false;
					m_IsCharging = false;
					m_isAttacking = false;
					m_MaxActionTimer = 0.f;
					m_ActionTimer = 0.f;

				}
				m_MaxActionTimer += deltaTime;*/
			}
			
			Tunneling();
			IdleMove(deltaTime);
			Chasing(deltaTime);

			if(m_Type == NPCType::FYGAR)
			{
				Fire(deltaTime);
				Attacking(deltaTime);
				AllignAttack();
				CollisionEvents();
			}
		}

		const auto index = GetGameObject()->GetTransform()->GetPositionIndex();
		const auto tile = m_pLevelManager->GetTile(index.x, index.y);

		if (tile->GetTileState() == TileState::FREE)
			m_isGhosting = true;
		else
			m_isGhosting = false;
	
}

void dae::NpcComponent::StartIdleMove()
{
	auto tiles = m_pLevelManager->GetTile(GetGameObject()->GetTransform()->GetPositionIndex());

	if (tiles->GetTileState() != TileState::USED)
	{
		m_ActionTimer = 0.f;
		return;
	}

	bool OpenBorder = tiles->GetIsConnectedBorder(m_NewDir);

	while (!OpenBorder)
	{
		m_NewDir = static_cast<Direction>(rand() % static_cast<int>(Direction::NONE));
		OpenBorder = tiles->GetIsConnectedBorder(m_NewDir);
	}

	m_ActionMaxTime = RandomFloatBetween(0.5f, m_MovingMaxTime);

	GetGameObject()->GetSprite()->onNotify(NotifyEvent::EVENT_MOVE);
	m_IsMoving = true;
	m_IsIdle = false;
	m_ActionTimer = 0.f;
}

void dae::NpcComponent::StopMovement()
{
	m_pMove->SetMovementInput(0, 0, 0);
	m_IsIdle = true;
	m_IsMoving = false;
	m_ActionMaxTime = RandomFloatBetween(0.25f, m_IdleMaxTime);
	//wstd::cout << GetGameObject()->GetName() << " STOP IDLE MOVING\n";
}

void dae::NpcComponent::IdleMove(float deltaTime)
{

	const auto index = GetGameObject()->GetTransform()->GetPositionIndex();

	const auto currTile = m_pLevelManager->GetTile(index.x, index.y);
	

	const auto nextTile = m_pLevelManager->GetTile(index.x + static_cast<int>(DirectionAxis(m_NewDir).x), index.y + static_cast<int>(DirectionAxis(m_NewDir).y));

	const auto CurrDirOpenBorder = m_pLevelManager->GetTile(index.x, index.y)->GetIsConnectedBorder(m_NewDir);
	
	if (m_IsMoving)
	{
		if(currTile != nullptr)
			if (currTile->GetTileState() != TileState::USED)
			{
				StartTunneling();
				m_IsMoving = false;
				return;
			}

		if (nextTile != nullptr)
		{
			
			if(!CurrDirOpenBorder && GetGameObject()->GetComponent<MoveComponent>()->IsCentered())
			{
				m_ActionTimer = 0.f;
				StopMovement();
				//std::cout << GetGameObject()->GetName() << " BORDER STOP\n";
				return;
			}

			if (nextTile->GetTileState() != TileState::USED && GetGameObject()->GetComponent<MoveComponent>()->IsCentered())
			{
				m_ActionTimer = 0.f;
				StopMovement();
				//std::cout << GetGameObject()->GetName() << " TILE STOP\n";
				return;
			}

			if (m_ActionTimer >= m_ActionMaxTime)
			{
				m_ActionTimer = 0.f;
				StopMovement();
				//std::cout << GetGameObject()->GetName() << " TIMER STOP\n";
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
				//std::cout << GetGameObject()->GetName() << " MOVE STOP\n";
				StopMovement();
			}

			m_ActionTimer += deltaTime;
		}
		else
		{
			m_ActionTimer = 0.f;
			m_pMove->FlipDirection();
			//std::cout << GetGameObject()->GetName() << " MAP STOP\n";
			StopMovement();
		}

	}
}

void dae::NpcComponent::StartChasing()
{
	if (m_pLevelManager->GetPlayerCount() > 1)
	{
		const auto rnd = RandomIntBetween(0, 100 * static_cast<int>(m_pLevelManager->GetPlayerCount()));
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

	m_IsChasing = true;
	m_IsIdle = false;
	m_ActionTimer = 0.f;

	m_ActionMaxTime = RandomFloatBetween(0.75f, m_MovingMaxTime);
	GetGameObject()->GetSprite()->onNotify(NotifyEvent::EVENT_MOVE);
}

void dae::NpcComponent::SetChaseTarget(const int& index)
{
	m_pTarget = m_pLevelManager->GetPlayer(index);	
}

void dae::NpcComponent::StopChasing()
{
	m_pMove->SetMovementInput(0, 0, 0);
	m_IsIdle = true;
	m_IsChasing = false;
	m_ActionMaxTime = RandomFloatBetween(0.25f, m_IdleMaxTime);
	std::cout << GetGameObject()->GetName() << " STOP CHASING\n";

}

void dae::NpcComponent::Chasing(float deltaTime)
{
	//TODO: FIX BORDER CROSSING
	if (m_IsChasing)
	{
		
		m_TargetLocation = m_pTarget->GetGameObject()->GetTransform()->GetPositionIndex();


		const auto index = GetGameObject()->GetTransform()->GetPositionIndex();

		const auto DistanceX = m_TargetLocation.x - index.x;
		const auto DistanceY = m_TargetLocation.y - index.y;

		//const auto CurrDirOpenBorder = m_pLevelManager->GetTile(index.x, index.y)->GetIsConnectedBorder(m_NewDir);

		float DirX = 0;
		float DirY = 0;

		if (static_cast<int>(DistanceX) != 0)
			DirX = static_cast<float>(DistanceX / abs(DistanceX));

		if (static_cast<int>(DistanceY) != 0)
			DirY = static_cast<float>(DistanceY / abs(DistanceY));

		const auto XTile = m_pLevelManager->GetTile(index.x + static_cast<int>(DirX), index.y);
		const auto YTile = m_pLevelManager->GetTile(index.x, index.y + static_cast<int>(DirY));

		if (XTile != nullptr&& YTile != nullptr)
		{
			GetGameObject()->GetSprite()->onNotify(NotifyEvent::EVENT_MOVE);

			if (XTile->GetTileState() != TileState::USED && YTile->GetTileState() != TileState::USED && GetGameObject()->GetComponent<MoveComponent>()->IsCentered())
			{
				m_ActionTimer = 0.f;
				StopChasing();
				std::cout << GetGameObject()->GetName() << " TILE STOP\n";
				return;
			}

			if (m_ActionTimer >= m_ActionMaxTime)
			{
				m_ActionTimer = 0.f;
				StopChasing();
				std::cout << GetGameObject()->GetName() << " TIMER STOP\n";

				return;
			}

			if (XTile->GetTileState() == TileState::USED)
			{
				m_pMove->SetMovementInput(DirX, 0);
				m_pMove->SetCurrentDirection(AxisDirection({ DirX, 0, 0 }));
				std::cout << GetGameObject()->GetName() << " TRY HORIZONTAL\n";

			}
			else if (YTile->GetTileState() == TileState::USED)
			{
				m_pMove->SetMovementInput(0, DirY);
				m_pMove->SetCurrentDirection(AxisDirection({ 0, DirY, 0 }));
				std::cout << GetGameObject()->GetName() << " TRY VERTICAL\n";
			}
			else if (XTile->GetTileState() != TileState::USED && YTile->GetTileState() != TileState::USED && GetGameObject()->GetComponent<MoveComponent>()->IsCentered())
			{
				m_ActionTimer = 0.f;
				StopChasing();
				std::cout << GetGameObject()->GetName() << " MOVE STOP\n";
			}

			m_ActionTimer += deltaTime;
		}
		else
		{
			m_ActionTimer = 0.f;
			m_pMove->FlipDirection();
			StopChasing();
			std::cout << GetGameObject()->GetName() << " MAP STOP\n";

		}

	}
}

void dae::NpcComponent::StartTunneling()
{
	if (m_pLevelManager->GetPlayerCount() > 1)
	{
		const auto rnd = RandomIntBetween(0, 100 * static_cast<int>(m_pLevelManager->GetPlayerCount()));
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


	m_IsChangeTunnel = true;
	m_IsIdle = false;

	m_TargetLocation = m_pTarget->GetGameObject()->GetTransform()->GetPositionIndex();

	GetGameObject()->GetSprite()->onNotify(NotifyEvent::EVENT_MOVE);
}

void dae::NpcComponent::StopTunneling()
{
	m_ActionTimer = 0.f;
	m_IsChangeTunnel = false;
	m_IsIdle = true;
	m_ActionMaxTime = RandomFloatBetween(0.25f, m_IdleMaxTime);
	m_pMove->SetMovementInput(0, 0);
}

void dae::NpcComponent::Tunneling()
{
	if (m_IsChangeTunnel)
	{
		const auto index = GetGameObject()->GetTransform()->GetPositionIndex();

		const auto DistanceX = m_TargetLocation.x - index.x;
		const auto DistanceY = m_TargetLocation.y - index.y;
		float DirX = 0;
		float DirY = 0;

		if(static_cast<int>(DistanceX) != 0)
			DirX = static_cast<float>(DistanceX / abs(DistanceX));
		
		if(static_cast<int>(DistanceY) != 0)
			DirY = static_cast<float>(DistanceY / abs(DistanceY));

	

		const auto XTile = m_pLevelManager->GetTile(index.x + static_cast<int>(DirX), index.y);
		const auto YTile = m_pLevelManager->GetTile(index.x, index.y + static_cast<int>(DirY));

		if (XTile && YTile)
		{
			if(static_cast<int>(DistanceX) == 0 && static_cast<int>(DistanceY) == 0 && GetGameObject()->GetComponent<MoveComponent>()->IsCentered())
			{
				StopTunneling();
				std::cout << GetGameObject()->GetName() << " GHOSTING ARRIVED\n";
				return;
			}


			const auto rnd = RandomIntBetween(0, 100);
			auto m_FirstHor = false;
			if(GetGameObject()->GetComponent<MoveComponent>()->IsCentered())
			{
				if(rnd <= 50 && DirX != 0)
				{
					m_FirstHor = true;
				}
			}

			if ((XTile->GetTileState() != TileState::OCCUPIED || XTile->GetTileState() != TileState::BLOCKED) && DirX != 0 && m_FirstHor && GetGameObject()->GetComponent<MoveComponent>()->IsCentered())
			{
				m_pMove->SetMovementInput(static_cast<float>(DirX), 0);
			}
			else if((YTile->GetTileState() != TileState::OCCUPIED || YTile->GetTileState() != TileState::BLOCKED) && DirY != 0 && GetGameObject()->GetComponent<MoveComponent>()->IsCentered())
			{
				m_pMove->SetMovementInput(0, static_cast<float>(DirY));
			}
			else if (DirX <= 0 && DirY <= 0 && GetGameObject()->GetComponent<MoveComponent>()->IsCentered())
			{
				StopTunneling();
			}

		}
		else
		{
			StopTunneling();
		}
	}
}

void dae::NpcComponent::AllignAttack() const
{
	auto AttackMove = m_Attack->GetComponent<MoveComponent>();
	auto AttackSpriteMove = m_AttackSprite->GetComponent<MoveComponent>();
	const auto NpcMove = GetGameObject()->GetComponent<MoveComponent>();

	if(m_Type == NPCType::FYGAR)
	{
		
		switch (m_NewDir)
		{
		default:;
		case Direction::RIGHT:
			m_AttackSprite->GetTransform()->SetLocalPosition(32, 0.f);
			m_Attack->GetTransform()->SetLocalPosition(0, 0.f);
			break;
		case Direction::LEFT:
			m_AttackSprite->GetTransform()->SetLocalPosition(-96, 0.f);
			m_Attack->GetTransform()->SetLocalPosition(-96, 0.f);
			break;
		}
	}

	if (m_isAttacking)
		return;

	AttackMove->SetVelocity({ 0,0,0 });
	AttackSpriteMove->SetCurrentDirection(NpcMove->GetCurrentDirection());

	m_Attack->GetComponent<CollisionComponent>()->EnableCollision(false);
	m_Attack->GetComponent<RenderComponent>()->EnableRender(false);
	m_AttackSprite->GetComponent<RenderComponent>()->EnableRender(false);

	m_Attack->GetTransform()->SetLocalPosition(0, 0);
}

void dae::NpcComponent::Fire(float deltaTime)
{
	if(m_isAttacking)
	{
		if (m_AttackSprite->GetComponent<SpriteComponent>()->IsAnimationEnded())
		{
			m_Attack->GetComponent<CollisionComponent>()->EnableCollision(true);
			m_Attack->GetComponent<RenderComponent>()->EnableRender(true);
			m_AttackSprite->GetComponent<SpriteComponent>()->Pause();
			

			if (m_ActionTimer >= m_FireMaxTime)
			{
				m_IsIdle = true;
				m_isAttacking = false;			
				m_ActionTimer = 0.0f;
				m_ActionMaxTime = RandomFloatBetween(0.25f, m_IdleMaxTime);

				m_AttackSprite->GetComponent<RenderComponent>()->EnableRender(true);
				m_AttackSprite->GetComponent<SpriteComponent>()->ResetCurrentAnimation();
				m_Attack->GetComponent<CollisionComponent>()->EnableCollision(false);
				m_Attack->GetComponent<RenderComponent>()->EnableRender(false);

			}

			m_ActionTimer += deltaTime;
		}
	}	
}

void dae::NpcComponent::CollisionEvents() const
{
	//ATTACK COLLISION
	//****************
	auto collision = m_Attack->GetComponent<CollisionComponent>();
	if (collision->GetHasCollision())
	{
		//ATTACK PLAYER
		if (collision->GetCollision()->GetGameObject()->GetComponent<PlayerComponent>())
		{
			collision->GetCollision()->GetGameObject()->GetComponent<PlayerComponent>()->SetHit(true);
			collision->GetCollision()->GetGameObject()->GetComponent<PlayerComponent>()->Dead();
			collision->SetHasCollision(false);
		}
	}
}

void dae::NpcComponent::Attacking(float deltaTime)
{
	if(m_IsCharging)
	{
		m_Attack->GetComponent<CollisionComponent>()->EnableCollision(false);

		if(m_ActionTimer >= m_ActionMaxTime)
		{
			GetGameObject()->GetSprite()->onNotify(NotifyEvent::EVENT_INTERACT);

			m_AttackSprite->GetComponent<SpriteComponent>()->Pause(false);		
			m_AttackSprite->GetComponent<RenderComponent>()->EnableRender(true);

			m_IsCharging = false;
			m_isAttacking = true;		
			m_ActionTimer = 0.f;
			return;
			
		}

		m_ActionTimer += deltaTime;
	}
}

void dae::NpcComponent::EnableCrushing(const bool& enable)
{
	m_IsCrushed = enable;
	GetGameObject()->GetComponent<MoveComponent>()->SetMovementInput({ 0, 1, 0 });
}

void dae::NpcComponent::SetHit(const bool& isHit)
{
	m_IsHit = isHit;
	if (isHit)
	{
		m_pMove->SetMovementInput(0, 0);
	} 
	else
	{
		GetGameObject()->GetSprite()->onNotify(NotifyEvent::EVENT_IDLE);
	}
		
}

void dae::NpcComponent::Hit(PlayerComponent* player)
{

	m_player = player;
	m_pMove->SetMovementInput(0, 0);
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
