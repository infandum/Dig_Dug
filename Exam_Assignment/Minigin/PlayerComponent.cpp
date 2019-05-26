#include "MiniginPCH.h"
#include "PlayerComponent.h"
#include "ServiceLocator.h"
#include "InputManager.h"
#include "Commands.h"
#include "PlayerStates.h"

dae::PlayerComponent::PlayerComponent(PlayerType type) : m_Type(type)
{
	m_IsCrushed = false;
	m_IsDead = false;
	m_IsReset = true;
	m_isAttacking = false;
	m_IsAttackHit = false;
	m_AttackTimer = 0;
}

void dae::PlayerComponent::Reset()
{
	Respawn();

	m_Health = 3;
	m_Points = 0;

	GetGameObject()->GetSprite()->onNotify(NotifyEvent::EVENT_SPAWN);
	Notify(*GetGameObject(), NotifyEvent::EVENT_RESET);

	GetGameObject()->GetRenderer()->EnableRender();
	GetGameObject()->GetCollision()->EnableCollision();
}

void dae::PlayerComponent::onNotify(GameObject & , NotifyEvent & )
{
}

void dae::PlayerComponent::Initialize()
{
	m_pLevelManager = ServiceLocator::GetLevelManager();

	m_AttackSprite = std::make_shared<GameObject>();
	m_Attack = std::make_shared<GameObject>();
	switch (m_Type)
	{
	default:
		break;

	case PlayerType::PLAYER_DIGDUG:
		
		m_Attack->SetName("Spear");
		m_Attack->AddComponent(std::make_shared<RenderComponent>());
		m_Attack->AddComponent(std::make_shared<CollisionComponent>(true));
		m_Attack->AddComponent(std::make_shared<TransformComponent>(GetGameObject()->GetTransform()->GetPosition().x, GetGameObject()->GetTransform()->GetPosition().y));
		m_Attack->AddComponent(std::make_shared<MoveComponent>());
		GetGameObject()->AddChild(m_Attack);


		m_AttackSprite->SetName("Spear Sprite");
		m_AttackSprite->AddComponent(std::make_shared<RenderComponent>());
		m_AttackSprite->AddComponent(std::make_shared<TransformComponent>(-32.f, 0.f));
		m_AttackSprite->AddComponent(std::make_shared<MoveComponent>());
		m_AttackSprite->AddComponent(std::make_shared<TextureComponent>(ServiceLocator::GetResourceManager()->GetTexture(02)));
		m_AttackSprite->AddComponent(std::make_shared<SpriteComponent>(WeaponState()));
		m_AttackSprite->GetComponent<SpriteComponent>()->SetAnimationToState(9, std::make_shared<WeaponState>());
		m_AttackSprite->GetComponent<SpriteComponent>()->Pause();

		m_Attack->AddChild(m_AttackSprite);
		break;

	case PlayerType::PLAYER_FYGAR:
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
		break;
	}	
}


void dae::PlayerComponent::PlayerUpdate()
{
	const auto index = GetGameObject()->GetTransform()->GetPositionIndex();
	const auto tile = m_pLevelManager->GetTile(index.x, index.y);
	switch (m_Type)
	{
	case PlayerType::PLAYER_DIGDUG:

		break;
	case PlayerType::PLAYER_FYGAR:
		
		if (tile->GetTileState() == TileState::FREE)
		{
			m_isAttacking = false;
			m_IsCharging = false;
			GetGameObject()->GetSprite()->onNotify(NotifyEvent::EVENT_MOVE);
		}
			
		break;
	default: ;
	}
}

void dae::PlayerComponent::Update(float deltaTime)
{
	if (m_IsReset)
	{
		if (m_RespawnTimer >= m_RespawnMaxTime)
		{
			m_IsCrushed = false;
			m_IsReset = false;
			m_IsDead = false;
			GetGameObject()->GetSprite()->onNotify(NotifyEvent::EVENT_IDLE);
			GetGameObject()->GetCollision()->EnableCollision();
			GetGameObject()->GetRenderer()->EnableRender();

			m_RespawnTimer = 0.f;
		}
		m_RespawnTimer += deltaTime;
	}

	if(m_IsDead)
	{
		GetGameObject()->GetCollision()->EnableCollision(false);
		if (!IsGameOver())
			RespawnTime(deltaTime);
	}
	else
	{
		ExecuteCommand();
		
	}

	if(!m_IsDead)
	{
		AllignAttack();
		MoveAttack(deltaTime);
	}
	PlayerUpdate();

	CollisionEvents();
}

void dae::PlayerComponent::RespawnTime(float deltaTime)
{
	if (GetGameObject()->GetSprite()->IsAnimationEnded())
	{
		GetGameObject()->GetRenderer()->EnableRender(false);
		if (m_RespawnTimer >= m_RespawnMaxTime)
		{
			m_pLevelManager->Respawn();
			if (IsGameOver())
				GetGameObject()->Enable(false);
		}

	}


	m_RespawnTimer += deltaTime;
}

void dae::PlayerComponent::Attack(bool& isAttacking)
{
	if (!m_isAttacking && isAttacking)
	{
		m_AttackSprite->GetComponent<SpriteComponent>()->ResetCurrentAnimation();

		if (m_Type == PlayerType::PLAYER_FYGAR)
			m_IsCharging = true;

	}

	if (m_isAttacking && !isAttacking)
	{
		GetGameObject()->GetSprite()->onNotify(NotifyEvent::EVENT_IDLE);

	}
	m_isAttacking = isAttacking;
}

void dae::PlayerComponent::SetHealth(int health)
{
	m_Health = health;
}

void dae::PlayerComponent::ChangeHealth(int amount)
{
	m_Health += amount;
}

void dae::PlayerComponent::EnableCrushing(const bool& enable)
{
	m_IsCrushed = enable;
	GetGameObject()->GetComponent<MoveComponent>()->SetMovementInput({ 0, 1, 0 });
}

void dae::PlayerComponent::AllignAttack() 
{
	auto AttackMove = m_Attack->GetComponent<MoveComponent>();
	auto AttackSpriteMove = m_AttackSprite->GetComponent<MoveComponent>();
	const auto PlayerMove = GetGameObject()->GetComponent<MoveComponent>();

	if(m_isAttacking || (m_IsCharging && m_isAttacking))
		return;

	AttackMove->SetVelocity({ 0,0,0 });
	AttackSpriteMove->SetCurrentDirection(PlayerMove->GetCurrentDirection());

	m_Attack->GetComponent<CollisionComponent>()->EnableCollision(false);
	m_Attack->GetComponent<RenderComponent>()->EnableRender(false);
	m_AttackSprite->GetComponent<RenderComponent>()->EnableRender(false);

	m_Attack->GetTransform()->SetLocalPosition(0, 0);

	switch (m_Type)
	{
	case PlayerType::PLAYER_DIGDUG:

			switch (GetGameObject()->GetComponent<MoveComponent>()->GetCurrentDirection())
			{
			default:;
			case Direction::RIGHT:
				m_AttackSprite->GetTransform()->SetLocalPosition(-32, 0.f);
				break;
			case Direction::LEFT:
				m_AttackSprite->GetTransform()->SetLocalPosition(0.f, 0.f);
				break;
			case Direction::UP:
				if (m_AttackSprite->GetSprite()->GetFlipSprite() == SDL_FLIP_NONE)
					m_AttackSprite->GetTransform()->SetLocalPosition(0.f, 0.f);
				else
					m_AttackSprite->GetTransform()->SetLocalPosition(-32.f, 0.f);

				break;
			case Direction::DOWN:
				if (m_AttackSprite->GetSprite()->GetFlipSprite() == SDL_FLIP_NONE)
					m_AttackSprite->GetTransform()->SetLocalPosition(0.f, -32.f);
				else
					m_AttackSprite->GetTransform()->SetLocalPosition(-32.f, -32.f);
				break;
			case Direction::NONE:
				m_AttackSprite->GetTransform()->SetLocalPosition(-32.f, 0.f);
				break;
			}

		break;

	case PlayerType::PLAYER_FYGAR:
		
			switch (GetGameObject()->GetComponent<MoveComponent>()->GetCurrentDirection())
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
			case Direction::UP:
				if (m_AttackSprite->GetComponent<MoveComponent>()->GetPreviousDirection() == Direction::RIGHT || m_AttackSprite->GetComponent<MoveComponent>()->GetPreviousDirection() == Direction::LEFT)
					m_LastHorDir = m_AttackSprite->GetComponent<MoveComponent>()->GetPreviousDirection();

				if (m_LastHorDir == Direction::LEFT)
				{
					m_Attack->GetTransform()->SetLocalPosition(-96, 0.f);
					m_AttackSprite->GetTransform()->SetLocalPosition(-96, 0.f);
				}
				else
				{
					m_Attack->GetTransform()->SetLocalPosition(0, 0.f);
					m_AttackSprite->GetTransform()->SetLocalPosition(32.f, 0.f);
				}

				break;
			case Direction::DOWN:
				if (m_AttackSprite->GetComponent<MoveComponent>()->GetPreviousDirection() == Direction::RIGHT || m_AttackSprite->GetComponent<MoveComponent>()->GetPreviousDirection() == Direction::LEFT)
					m_LastHorDir = m_AttackSprite->GetComponent<MoveComponent>()->GetPreviousDirection();

				if (m_LastHorDir == Direction::LEFT)
				{
					m_Attack->GetTransform()->SetLocalPosition(-96, 0.f);
					m_AttackSprite->GetTransform()->SetLocalPosition(-96, 0.f);
				}
				else
				{
					m_Attack->GetTransform()->SetLocalPosition(0, 0.f);
					m_AttackSprite->GetTransform()->SetLocalPosition(32.f, 0.f);
				}
				break;
			}
		break;
	}
}

void dae::PlayerComponent::MoveAttack(float deltaTime)
{
	auto AttackMove = m_Attack->GetComponent<MoveComponent>();
	auto AttackSpriteMove = m_AttackSprite->GetComponent<MoveComponent>();
	auto PlayerMove = GetGameObject()->GetComponent<MoveComponent>();

		switch (m_Type)
		{
		default:
			break;

		case PlayerType::PLAYER_DIGDUG:
			if(m_isAttacking)
			{
				PlayerMove->SetVelocity({ 0, 0, 0 });
				AttackSpriteMove->SetCurrentDirection(PlayerMove->GetCurrentDirection());

				const float dist = std::sqrt(
					std::pow(m_Attack->GetTransform()->GetPosition().x - GetGameObject()->GetTransform()->GetPosition().x, 2) + 
					std::pow(m_Attack->GetTransform()->GetPosition().y - GetGameObject()->GetTransform()->GetPosition().y, 2) + 
					std::pow(m_Attack->GetTransform()->GetPosition().z - GetGameObject()->GetTransform()->GetPosition().z, 2));
				if (dist >= m_AttackRange + 16.f)
				{
					AttackMove->SetVelocity({ 0 ,0 ,0 });
					AttackSpriteMove->SetVelocity({ 0 ,0 ,0 });

					m_AttackAtMaxRange = true;
					m_Attack->GetComponent<CollisionComponent>()->EnableCollision(false);
					//m_Attack->GetComponent<RenderComponent>()->EnableRender(false);
					//if(!m_IsAttackHit)
					//	m_AttackSprite->GetComponent<RenderComponent>()->EnableRender(false);
				}
				else
				{
					m_Attack->GetComponent<CollisionComponent>()->EnableCollision(true);
					m_AttackSprite->GetComponent<RenderComponent>()->EnableRender(true);
					m_AttackAtMaxRange = false;
				}

				if (!m_AttackAtMaxRange)
				{
					if (!m_IsAttackHit)
						AttackMove->SetVelocity({ DirectionAxis(PlayerMove->GetCurrentDirection()) * m_AttackSpeed });
					else
						AttackMove->SetVelocity({ 0, 0, 0 });
				}
			}			
			break;

		case PlayerType::PLAYER_FYGAR:
			if(m_isAttacking)
			{
				m_Attack->GetComponent<CollisionComponent>()->EnableCollision(false);
				m_Attack->GetComponent<RenderComponent>()->EnableRender(false);
			}
			if (m_IsCharging && !m_isAttacking)
			{
				m_AttackSprite->GetComponent<SpriteComponent>()->Pause(false);
				m_AttackSprite->GetComponent<RenderComponent>()->EnableRender(true);

				if(m_AttackSprite->GetComponent<SpriteComponent>()->IsAnimationEnded())
				{
					m_Attack->GetComponent<CollisionComponent>()->EnableCollision(true);
					m_Attack->GetComponent<RenderComponent>()->EnableRender(true);
					m_AttackSprite->GetComponent<SpriteComponent>()->Pause();
					
					m_AttackTimer += deltaTime;

					if(m_AttackTimer > m_AttackMaxTime)
					{
						m_IsCharging = false;
						m_AttackTimer = 0;
					}					
				}
			}
			break;
		}
}

void dae::PlayerComponent::CollisionEvents()
{
	//PLAYER COLLISION
	//****************
	auto collision = GetGameObject()->GetComponent<CollisionComponent>();
	if(collision->GetHasCollision())
	{
		if (collision->GetCollision()->GetGameObject()->GetComponent<NpcComponent>() || collision->GetCollision()->GetGameObject()->GetComponent<PlayerComponent>())
		{
			std::cout << "Collision" << std::endl;
			//HIT ENEMY PLAYER
			if(collision->GetCollision()->GetGameObject()->GetComponent<PlayerComponent>())
				if(collision->GetCollision()->GetGameObject()->GetComponent<PlayerComponent>()->GetType() != m_Type && !collision->GetCollision()->GetGameObject()->GetComponent<PlayerComponent>()->IsDead())
				{
					Dead();
					collision->GetCollision()->GetGameObject()->GetComponent<PlayerComponent>()->Dead();
				}

			//HIT NPC
			if (collision->GetCollision()->GetGameObject()->GetComponent<NpcComponent>() && m_Type == PlayerType::PLAYER_DIGDUG)
				if (GetGameObject()->GetSprite()->GetCurrentEvent() != NotifyEvent::EVENT_SPAWN && !collision->GetCollision()->GetGameObject()->GetComponent<NpcComponent>()->IsHit() && !collision->GetCollision()->GetGameObject()->GetComponent<NpcComponent>()->IsInflated())
				{			
					Dead();
				}			
			collision->SetHasCollision(false);
		}
	}



	//ATTACK COLLISION
	//****************
	collision = m_Attack->GetComponent<CollisionComponent>();
	if (collision->GetHasCollision())
	{
		//ATTACK ENEMY NPC
		if (collision->GetCollision()->GetGameObject()->GetComponent<NpcComponent>())
		{
			if (!collision->GetCollision()->GetGameObject()->GetComponent<NpcComponent>()->IsDead() && !collision->GetCollision()->GetGameObject()->GetComponent<NpcComponent>()->IsGhosting())
				if (collision->GetCollision()->GetGameObject()->GetSprite() && !collision->GetGameObject()->GetComponent<MoveComponent>()->GetIsStatic())
					if (collision->GetCollision()->GetGameObject()->GetSprite()->GetCurrentEvent() != NotifyEvent::EVENT_SPAWN)
					{
						collision->GetCollision()->GetGameObject()->GetSprite()->onNotify(NotifyEvent::EVENT_COLLISION);
						collision->GetCollision()->GetGameObject()->GetComponent<NpcComponent>()->Hit(this);
						GetGameObject()->GetSprite()->onNotify(NotifyEvent::EVENT_INTERACT);
						m_IsAttackHit = true;
					}
					else
					{
						collision->GetCollision()->GetGameObject()->GetComponent<NpcComponent>()->SetHit(false);
						collision->GetCollision()->GetGameObject()->GetSprite()->onNotify(NotifyEvent::EVENT_IDLE);
					}
						

			collision->SetHasCollision(false);

			if(!m_isAttacking)
				collision->GetCollision()->GetGameObject()->GetComponent<NpcComponent>()->SetHit(false);
		}
		//ATTACK ENEMY PLAYER
		if (collision->GetCollision()->GetGameObject()->GetComponent<PlayerComponent>())
		{
			if (collision->GetCollision()->GetGameObject()->GetComponent<PlayerComponent>()->GetType() != m_Type)
			{
				collision->GetCollision()->GetGameObject()->GetComponent<PlayerComponent>()->SetHit(true);
				collision->GetCollision()->GetGameObject()->GetComponent<PlayerComponent>()->Dead();
				m_IsAttackHit = true;
			}
			else
			{
				collision->GetCollision()->GetGameObject()->GetComponent<PlayerComponent>()->SetHit(false);
				collision->GetCollision()->GetGameObject()->GetSprite()->onNotify(NotifyEvent::EVENT_IDLE);
			}
			collision->SetHasCollision(false);
		}
	}
	else
	{
		m_IsAttackHit = false;
	}
		
}

void dae::PlayerComponent::Dead()
{
	GetGameObject()->GetSprite()->onNotify(NotifyEvent::EVENT_COLLISION);
	GetGameObject()->GetCollision()->EnableCollision(false);
	GetGameObject()->GetComponent<MoveComponent>()->SetVelocity({ 0,0,0 });
	m_IsDead = true;
	
}

void dae::PlayerComponent::Respawn()
{
	GetGameObject()->Enable(true);
	GetGameObject()->GetRenderer()->EnableRender(true);
	GetGameObject()->GetTransform()->Reset();
	GetGameObject()->GetComponent<MoveComponent>()->Reset();

	
	if (m_IsDead)
		m_Health--;

	m_AttackTimer = 0;
	m_IsReset = true;
	m_RespawnTimer = 0.f;

	m_isAttacking = false;
	m_AttackAtMaxRange = false;
	m_IsCharging = false;
	m_IsAttackHit = false;

	m_IsCrushed = false;
	m_IsDead = false;

	m_IsHit = false;

	

	Notify(*GetGameObject(), NotifyEvent::EVENT_VALUE_CHECK);
	GetGameObject()->GetSprite()->onNotify(NotifyEvent::EVENT_SPAWN);	
}