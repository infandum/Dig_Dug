#include "MiniginPCH.h"
#include "GameObject.h"
#include "Components.h"
#include "InputManager.h"
#include "Commands.h"

void dae::InputComponent::onNotify(NotifyEvent event)
{
	UNREFERENCED_PARAMETER(event);
}

void dae::InputComponent::Update(float& deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	if (m_TransformComponent == nullptr)
		m_TransformComponent = GetGameObject()->GetComponent<TransformComponent>();

	auto input = ServiceLocator::GetInputManager();
	auto command = input->HandleInput();

	if (command != nullptr)
		command->Execute(*GetGameObject());
}
