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
	m_isAttacking = isAttacking;
	m_Attack->SetIsFollowParent(!m_isAttacking);
}

void dae::PlayerComponent::SetHealth(int health)
{
	m_Health = health;
}

void dae::PlayerComponent::ChangeHealth(int amount)
{
	m_Health += amount;
}

void dae::PlayerComponent::Initialize()
{
	/*auto tiles = ServiceLocator::GetLevelManager();
	tiles->AddPlayer(this);*/

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
		/*attack->AddComponent(std::make_shared<SpriteComponent>());*/
		m_Attack->GetComponent<TextureComponent>()->SetTexture(ServiceLocator::GetResourceManager()->GetTexture(12));
		GetGameObject()->AddChild(m_Attack);


		m_AttackSprite->SetName("Spear Sprite");
		m_AttackSprite->AddComponent(std::make_shared<RenderComponent>());
		m_AttackSprite->AddComponent(std::make_shared<TransformComponent>(GetGameObject()->GetTransform()->GetPosition().x + 32.f, GetGameObject()->GetTransform()->GetPosition().y));
		m_AttackSprite->AddComponent(std::make_shared<MoveComponent>());
		m_AttackSprite->AddComponent(std::make_shared<TextureComponent>(ServiceLocator::GetResourceManager()->GetTexture(02)));
		m_AttackSprite->AddComponent(std::make_shared<SpriteComponent>(WeaponState()));
		m_AttackSprite->GetComponent<SpriteComponent>()->SetAnimationToState(7, std::make_shared<WeaponState>());
		//m_AttackSprite->GetComponent<TextureComponent>()->

		GetGameObject()->AddChild(m_AttackSprite);
		break;

	case PlayerType::PLAYER_FYGAR:
		m_Attack->SetName("Fire");
		m_Attack->AddComponent(std::make_shared<RenderComponent>());
		m_Attack->AddComponent(std::make_shared<CollisionComponent>(true));
		m_Attack->AddComponent(std::make_shared<TransformComponent>(GetGameObject()->GetTransform()->GetPosition().x, GetGameObject()->GetTransform()->GetPosition().y));
		m_Attack->AddComponent(std::make_shared<MoveComponent>());
		m_Attack->AddComponent(std::make_shared<TextureComponent>());
		/*attack->AddComponent(std::make_shared<SpriteComponent>());*/
		m_Attack->GetComponent<TextureComponent>()->SetTexture(ServiceLocator::GetResourceManager()->GetTexture(11));
		GetGameObject()->AddChild(m_Attack);
		break;
	}

	
}

void dae::PlayerComponent::AllignAttack() const
{
	auto move = m_Attack->GetComponent<MoveComponent>();
	move->SetVelocity({ 0,0,0 });

	m_Attack->GetComponent<CollisionComponent>()->EnableCollision(false);
	m_Attack->GetComponent<RenderComponent>()->EnableRender(false);

	//GetGameObject()->GetSprite()->onNotify(NotifyEvent::EVENT_IDLE);
	GetGameObject()->GetChild(0)->GetTransform()->SetLocalPosition(0, 0);
}

void dae::PlayerComponent::MoveAttack()
{
	auto AttackMove = m_Attack->GetComponent<MoveComponent>();
	auto Player = GetGameObject()->GetComponent<MoveComponent>();
	Player->SetVelocity({ 0, 0, 0 });
	m_Attack->SetIsActive(true);
	auto dist = std::sqrt(std::pow(m_Attack->GetTransform()->GetPosition().x - GetGameObject()->GetTransform()->GetPosition().x, 2) + std::pow(m_Attack->GetTransform()->GetPosition().y - GetGameObject()->GetTransform()->GetPosition().y, 2) + std::pow(m_Attack->GetTransform()->GetPosition().z - GetGameObject()->GetTransform()->GetPosition().z, 2));
	if (dist >= m_AttackRange + 16.f)
	{
		AttackMove->SetVelocity({ 0 ,0 ,0 });
		m_Attack->GetTransform()->SetPosition(GetGameObject()->GetTransform()->GetPosition() + DirectionAxis(Player->GetCurrentDirection()));
		m_AttackAtMaxRange = true;
		m_Attack->GetComponent<CollisionComponent>()->EnableCollision(false);
		m_Attack->GetComponent<RenderComponent>()->EnableRender(false);
	}
	else
	{
		m_Attack->GetComponent<CollisionComponent>()->EnableCollision(true);
		m_Attack->GetComponent<RenderComponent>()->EnableRender(true);
		m_AttackAtMaxRange = false;
	}
		

	if (!m_AttackAtMaxRange)
		switch (m_Type)
		{
		default:
			break;

		case PlayerType::PLAYER_DIGDUG:
			AttackMove->SetIsStatic(false);
			AttackMove->SetVelocity({ DirectionAxis(Player->GetCurrentDirection()) * m_AttackSpeed });

			break;

		case PlayerType::PLAYER_FYGAR:

			break;
		}
}

void dae::PlayerComponent::CollisionEvents()
{
	auto collision = GetGameObject()->GetComponent<CollisionComponent>();
	if(collision->GetHasCollision())
	{
		if (collision->GetCollision()->GetGameObject()->GetComponent<NpcComponent>())
		{
			std::cout << "Collision" << std::endl;
			if (GetGameObject()->GetSprite()->GetCurrentEvent() != NotifyEvent::EVENT_SPAWN)
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
			std::cout << "Trigger" << std::endl;
			if (collision->GetCollision()->GetGameObject()->GetSprite()->GetCurrentEvent() != NotifyEvent::EVENT_SPAWN)
				collision->GetCollision()->GetGameObject()->GetSprite()->onNotify(NotifyEvent::EVENT_COLLISION);

			GetGameObject()->GetSprite()->onNotify(NotifyEvent::EVENT_INTERACT);
			collision->SetHasCollision(false);
		}
	}
}

void dae::PlayerComponent::Update(float )
{
	if(IsDead())
		return;

	ExecuteCommand();

	if (!m_isAttacking)
		AllignAttack();
	else
		MoveAttack();

	CollisionEvents();
}
