#include "MiniginPCH.h"
#include "GameObject.h"
#include "Components.h"
#include "InputManager.h"
#include "Commands.h"

void dae::InputComponent::Initialize()
{
}

void dae::InputComponent::Update(float)
{
	auto input = ServiceLocator::GetInputManager();
	auto command = input->HandleInput();

	if (command != nullptr)
		command->Execute();
}