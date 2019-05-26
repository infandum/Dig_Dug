#include "MiniginPCH.h"
#include "GameObject.h"
#include "Components.h"
#include "InputManager.h"
#include "Commands.h"

void dae::InputComponent::ExecuteCommand() const
{
	auto input = ServiceLocator::GetInputManager();
	auto command = input->HandleInput(this->GetGameObject());

	if (command != nullptr)
	{
		command->Execute();
	}
}

void dae::InputComponent::onNotify(GameObject& , NotifyEvent& )
{
}

void dae::InputComponent::Initialize()
{
}

void dae::InputComponent::Update(float)
{
	ExecuteCommand();
}