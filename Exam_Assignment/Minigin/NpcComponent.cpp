#include "MiniginPCH.h"
#include "NpcComponent.h"
#include "GameObject.h"
#include "ServiceLocator.h"

dae::NpcComponent::NpcComponent(NPCType type) :m_Type(type)
{
}

void dae::NpcComponent::Initialize()
{
	auto tiles = ServiceLocator::GetLevelManager();
	tiles->AddEntity(this);
}

void dae::NpcComponent::Update(float )
{
	if(m_Type == NPCType::POOKA)
	{
		GetGameObject()->GetComponent<MoveComponent>()->SetIsOmniDirectional(true);
		//GetGameObject()->GetTransform()->SetVelocity({ g_MoveSpeed , -g_MoveSpeed, 0 });
		GetGameObject()->GetComponent<MoveComponent>()->MoveToTile(0, 10);
		//GetGameObject()->GetTransform()->SetVelocity({ 0, -g_MoveSpeed, 0 });
		GetGameObject()->GetSprite()->onNotify(NotifyEvent::EVENT_IDLE);
	}
	
}