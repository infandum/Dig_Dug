#include "MiniginPCH.h"
#include "GameObject.h"
#include "Components.h"
#include "InputManager.h"
#include "Commands.h"

dae::InputComponent::InputComponent()
{
	auto tiles = ServiceLocator::GetLevelManager();
	tiles->AddPlayer(this);
}

void dae::InputComponent::Update(float& deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	auto input = ServiceLocator::GetInputManager();
	auto command = input->HandleInput();

	if (command != nullptr)
		command->Execute(*GetGameObject());
}
