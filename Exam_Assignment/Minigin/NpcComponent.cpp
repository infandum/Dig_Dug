#include "MiniginPCH.h"
#include "NpcComponent.h"
#include "GameObject.h"
#include "ServiceLocator.h"

extern  const float g_MoveSpeed;

dae::NpcComponent::NpcComponent()
{
	auto tiles = ServiceLocator::GetLevelManager();
	tiles->AddEntity(this);
}

void dae::NpcComponent::Initialize()
{
}

void dae::NpcComponent::Update(float )
{
	GetGameObject()->GetTransform()->SetIsOmniDirectional(true);
	//GetGameObject()->GetTransform()->SetVelocity({ g_MoveSpeed , -g_MoveSpeed, 0 });
	GetGameObject()->GetTransform()->MoveToTile(0, 10);
	//GetGameObject()->GetTransform()->SetVelocity({ 0, -g_MoveSpeed, 0 });
	GetGameObject()->GetSprite()->onNotify(NotifyEvent::EVENT_IDLE);
}