#include "MiniginPCH.h"
#include "PlayerComponent.h"
#include "ServiceLocator.h"
#include "InputManager.h"
#include "Commands.h"

dae::PlayerComponent::PlayerComponent()
{
	auto tiles = ServiceLocator::GetLevelManager();
	tiles->AddPlayer(this);
}

void dae::PlayerComponent::Initialize()
{
	
}

void dae::PlayerComponent::Update(float )
{
	/*auto input = ServiceLocator::GetInputManager();
	auto command = input->HandleInput();

	if (command != nullptr)
		command->Execute(*GetGameObject());*/
}
