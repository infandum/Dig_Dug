#include "MiniginPCH.h"
#include "PlayerComponent.h"
#include "ServiceLocator.h"
#include "InputManager.h"
#include "Commands.h"

dae::PlayerComponent::PlayerComponent(PlayerType type) : m_Type(type)
{
}

void dae::PlayerComponent::Attack(bool& isAttacking)
{
	if(!m_isAttacking && isAttacking)
	{
		m_AttackSprite->GetComponent<SpriteComponent>()->ResetCurrentAnimation();

		if (m_Type == PlayerType::PLAYER_FYGAR)
			m_IsCharging = true;
		
	}
	m_isAttacking = isAttacking;

	
	//m_Attack->SetIsFollowParent(!m_isAttacking);
}

void dae::PlayerComponent::SetHealth(int health)
{
	m_Health = health;
}

void dae::PlayerComponent::ChangeHealth(int amount)
{
	m_Health += amount;
}

void dae::PlayerComponent::Reset()
{
	m_IsDead = false;
	m_IsReset = true;
	m_isAttacking = false;
	m_IsAttackHit = false;
	GetGameObject()->SetIsActive(true);
}

void dae::PlayerComponent::Initialize()
{
	
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
		m_Attack->AddComponent(std::make_shared<TextureComponent>());
		m_Attack->GetComponent<TextureComponent>()->SetTexture(ServiceLocator::GetResourceManager()->GetTexture(12));
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
		m_Attack->AddComponent(std::make_shared<TextureComponent>());
		m_Attack->GetComponent<TextureComponent>()->SetTexture(ServiceLocator::GetResourceManager()->GetTexture(11));
		GetGameObject()->AddChild(m_Attack);

		m_AttackSprite->SetName("Fire Sprite");
		m_AttackSprite->AddComponent(std::make_shared<RenderComponent>());
		m_AttackSprite->AddComponent(std::make_shared<TransformComponent>(-32.f, 0.f));
		m_AttackSprite->AddComponent(std::make_shared<MoveComponent>());
		m_AttackSprite->AddComponent(std::make_shared<TextureComponent>(ServiceLocator::GetResourceManager()->GetTexture(02)));
		m_AttackSprite->AddComponent(std::make_shared<SpriteComponent>(WeaponState()));
		m_AttackSprite->GetComponent<SpriteComponent>()->SetAnimationToState(29, std::make_shared<WeaponState>());
		m_AttackSprite->GetComponent<SpriteComponent>()->Pause();

		m_Attack->AddChild(m_AttackSprite);
		break;
	}

	
}


void dae::PlayerComponent::Update(float)
{
	if (!IsDead())
	{
		ExecuteCommand();
	}

	AllignAttack();
	MoveAttack();

	CollisionEvents();

	if (m_IsReset)
	{
		GetGameObject()->GetSprite()->onNotify(NotifyEvent::EVENT_IDLE);
		m_IsReset = false;
	}
	GetGameObject()->GetComponent<RenderComponent>()->EnableRender(false);
}


void dae::PlayerComponent::AllignAttack() 
{
	auto AttackMove = m_Attack->GetComponent<MoveComponent>();
	auto AttackSpriteMove = m_AttackSprite->GetComponent<MoveComponent>();
	const auto PlayerMove = GetGameObject()->GetComponent<MoveComponent>();

	if(m_isAttacking)
		return;

	AttackMove->SetVelocity({ 0,0,0 });
	AttackSpriteMove->SetCurrentDirection(PlayerMove->GetCurrentDirection());

	m_Attack->GetComponent<CollisionComponent>()->EnableCollision(false);
	//m_Attack->GetComponent<RenderComponent>()->EnableRender(false);

	//m_AttackSprite->GetComponent<RenderComponent>()->EnableRender(false);

	if(GetGameObject()->GetSprite()->GetCurrentEvent() != NotifyEvent::EVENT_SPAWN)
		if (GetGameObject()->GetSprite()->GetCurrentEvent() != NotifyEvent::EVENT_MOVE)
			GetGameObject()->GetSprite()->onNotify(NotifyEvent::EVENT_IDLE);

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
				break;
			case Direction::LEFT:
				m_AttackSprite->GetTransform()->SetLocalPosition(-96, 0.f);
				break;
			case Direction::UP:
				if (m_AttackSprite->GetComponent<MoveComponent>()->GetPreviousDirection() == Direction::RIGHT || m_AttackSprite->GetComponent<MoveComponent>()->GetPreviousDirection() == Direction::LEFT)
					m_LastHorDir = m_AttackSprite->GetComponent<MoveComponent>()->GetPreviousDirection();

				if (m_LastHorDir == Direction::LEFT)
					m_AttackSprite->GetTransform()->SetLocalPosition(-96, 0.f);
				else
					m_AttackSprite->GetTransform()->SetLocalPosition(32.f, 0.f);

				break;
			case Direction::DOWN:
				if (m_AttackSprite->GetComponent<MoveComponent>()->GetPreviousDirection() == Direction::RIGHT || m_AttackSprite->GetComponent<MoveComponent>()->GetPreviousDirection() == Direction::LEFT)
					m_LastHorDir = m_AttackSprite->GetComponent<MoveComponent>()->GetPreviousDirection();

				if (m_LastHorDir == Direction::LEFT)
					m_AttackSprite->GetTransform()->SetLocalPosition(-96, 0.f);
				else
					m_AttackSprite->GetTransform()->SetLocalPosition(32.f, 0.f);
				break;
			case Direction::NONE:
				if (m_AttackSprite->GetComponent<MoveComponent>()->GetPreviousDirection() == Direction::RIGHT || m_AttackSprite->GetComponent<MoveComponent>()->GetPreviousDirection() == Direction::LEFT)
					m_LastHorDir = m_AttackSprite->GetComponent<MoveComponent>()->GetPreviousDirection();

				if (m_LastHorDir == Direction::LEFT)
					m_AttackSprite->GetTransform()->SetLocalPosition(-96, 0.f);
				else
					m_AttackSprite->GetTransform()->SetLocalPosition(32.f, 0.f);
				break;
			}
		break;
	}
}

void dae::PlayerComponent::MoveAttack()
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

			if (m_IsCharging && !m_isAttacking)
			{
				m_AttackSprite->GetComponent<SpriteComponent>()->Pause(false);
				//m_Attack->GetCollision()->SetSize({ 64, 32 });
				if(m_AttackSprite->GetComponent<SpriteComponent>()->IsAnimationEnded())
					m_AttackSprite->GetComponent<SpriteComponent>()->Pause();
			}
				


			break;
		}
}

void dae::PlayerComponent::CollisionEvents()
{
	auto collision = GetGameObject()->GetComponent<CollisionComponent>();
	if(collision->GetHasCollision())
	{
		if (collision->GetCollision()->GetGameObject()->GetComponent<NpcComponent>() || collision->GetCollision()->GetGameObject()->GetComponent<PlayerComponent>())
		{
			std::cout << "Collision" << std::endl;
			if(collision->GetCollision()->GetGameObject()->GetComponent<PlayerComponent>())
				if(collision->GetCollision()->GetGameObject()->GetComponent<PlayerComponent>()->GetType() != m_Type/* && !collision->GetCollision()->GetGameObject()->GetComponent<PlayerComponent>()->IsDead()*/)
				{
					GetGameObject()->GetSprite()->onNotify(NotifyEvent::EVENT_COLLISION);
					m_IsDead = true;
					/*collision->GetCollision()->GetGameObject()->GetSprite()->onNotify(NotifyEvent::EVENT_COLLISION);
					collision->GetCollision()->GetGameObject()->GetComponent<PlayerComponent>()->m_IsDead = true;*/
				}

			if (collision->GetCollision()->GetGameObject()->GetComponent<NpcComponent>())
				if (GetGameObject()->GetSprite()->GetCurrentEvent() != NotifyEvent::EVENT_SPAWN && !collision->GetCollision()->GetGameObject()->GetNPC()->IsDead())
				{
					GetGameObject()->GetSprite()->onNotify(NotifyEvent::EVENT_COLLISION);
					m_IsDead = true;
				}			
			collision->SetHasCollision(false);
		}
	}

	collision = m_Attack->GetComponent<CollisionComponent>();
	if (collision->GetHasCollision())
	{
		if (collision->GetCollision()->GetGameObject()->GetComponent<NpcComponent>())
		{
			if (!collision->GetCollision()->GetGameObject()->GetComponent<NpcComponent>()->IsDead())
				if (collision->GetCollision()->GetGameObject()->GetSprite() && !collision->GetGameObject()->GetComponent<MoveComponent>()->GetIsStatic())
					if (collision->GetCollision()->GetGameObject()->GetSprite()->GetCurrentEvent() != NotifyEvent::EVENT_SPAWN)
					{
						collision->GetCollision()->GetGameObject()->GetSprite()->onNotify(NotifyEvent::EVENT_COLLISION);
						collision->GetCollision()->GetGameObject()->GetComponent<NpcComponent>()->SetHit(true);
						GetGameObject()->GetSprite()->onNotify(NotifyEvent::EVENT_INTERACT);
						m_IsAttackHit = true;
					}

			collision->SetHasCollision(false);

			if(!m_isAttacking)
				collision->GetCollision()->GetGameObject()->GetComponent<NpcComponent>()->SetHit(false);
		}
		if (collision->GetCollision()->GetGameObject()->GetComponent<PlayerComponent>())
		{
			if (collision->GetCollision()->GetGameObject()->GetComponent<PlayerComponent>()->GetType() != m_Type)
			{
				m_IsAttackHit = true;
			}
		}
	}
	else
	{
		m_IsAttackHit = false;
	}
		
}
