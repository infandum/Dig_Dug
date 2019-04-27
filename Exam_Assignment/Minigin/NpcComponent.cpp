#include "MiniginPCH.h"
#include "NpcComponent.h"
#include "GameObject.h"

extern  const float g_MoveSpeed;

void dae::NpcComponent::Update(float& deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	GetGameObject()->GetTransform()->SetVelocity({ 0, -g_MoveSpeed, 0 });
}
