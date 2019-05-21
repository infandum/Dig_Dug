#include "MiniginPCH.h"
#include "NpcComponent.h"
#include "GameObject.h"
#include "ServiceLocator.h"

dae::NpcComponent::NpcComponent(NPCType type) :m_Type(type)
{
}

void dae::NpcComponent::Reset()
{
	m_IsDead = false;
	m_IsHit = false;
	m_isGhosting = false;

	GetGameObject()->SetIsActive(true);
	GetGameObject()->GetTransform()->Reset();
	GetGameObject()->GetComponent<MoveComponent>()->Reset();

	if (m_Type == NPCType::POOKA)
		GetGameObject()->GetSprite()->onNotify(NotifyEvent::EVENT_SPAWN);
}

void dae::NpcComponent::onNotify(GameObject & , NotifyEvent & )
{
}

void dae::NpcComponent::Initialize()
{
	auto tiles = ServiceLocator::GetLevelManager();
	tiles->AddEntity(this);

	if (m_Type == NPCType::POOKA)
		GetGameObject()->GetSprite()->onNotify(NotifyEvent::EVENT_IDLE);
}

void dae::NpcComponent::Update(float )
{
	if(m_IsDead)
	{
		GetGameObject()->SetIsActive(false);
	}

	if(m_Type == NPCType::POOKA)
	{
		if (!m_IsHit)
			GetGameObject()->GetSprite()->onNotify(NotifyEvent::EVENT_IDLE);
		else
			if (GetGameObject()->GetSprite()->IsAnimationEnded() && typeid(* GetGameObject()->GetSprite()->GetCurrentState()) == typeid(DeadEnemyState))
				Dead();

		//GetGameObject()->GetComponent<MoveComponent>()->SetIsOmniDirectional(true);
		//GetGameObject()->GetTransform()->SetVelocity({ g_MoveSpeed , -g_MoveSpeed, 0 });
		//GetGameObject()->GetComponent<MoveComponent>()->MoveToTile(0, 10);
		//GetGameObject()->GetTransform()->SetVelocity({ 0, -g_MoveSpeed, 0 });
		//

		if(GetGameObject()->GetSprite()->GetCurrentEvent() == NotifyEvent::EVENT_COLLISION)
			return;
	}
	
}

void dae::NpcComponent::Dead()
{
	m_IsDead = true;
	
}
