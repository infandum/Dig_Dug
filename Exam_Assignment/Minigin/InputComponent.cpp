#include "MiniginPCH.h"
#include "GameObject.h"
#include "Components.h"
#include "InputManager.h"
#include "Commands.h"

void dae::InputComponent::KeyUp(SDL_Keycode key) const
{
	glm::vec3 dir = { 0.0f, 0.f, 0.f };
	switch (key)
	{
	case SDLK_LEFT:
		m_TransformComponent->SetVelocity(dir);
		break;
	case SDLK_RIGHT:
		m_TransformComponent->SetVelocity(dir);
		break;
	case SDLK_UP:
		m_TransformComponent->SetVelocity(dir);
		break;
	case SDLK_DOWN:
		m_TransformComponent->SetVelocity(dir);
		break;
	default: ;
	}
}

void dae::InputComponent::KeyDown(SDL_Keycode key) const
{
	glm::vec3 dir;
	extern const float g_MoveSpeed;
	switch (key)
	{
	case SDLK_LEFT:
		dir = { -g_MoveSpeed, 0, 0 };
		m_TransformComponent->SetVelocity(dir);
		break;
	case SDLK_RIGHT:
		dir = { g_MoveSpeed, 0, 0 };
		m_TransformComponent->SetVelocity(dir);
		break;
	case SDLK_UP:
		dir = { 0, -g_MoveSpeed, 0 };
		m_TransformComponent->SetVelocity(dir);
		break;
	case SDLK_DOWN:
		dir = { 0, g_MoveSpeed, 0 };
		m_TransformComponent->SetVelocity(dir);
		break;
	default: ;
	}
}

void dae::InputComponent::Update(float& deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	if (m_TransformComponent == nullptr)
		m_TransformComponent = GetGameObject()->GetComponent<TransformComponent>();

	auto& input = InputManager::GetInstance();

	//input.IsKeyDown()

	/*std::shared_ptr<Command> command = input.HandleInput();
	if (command)
		command->Execute(*GetGameObject());*/

	//SDL_Event e;
	SDL_Keycode key;
	if (input.IsKeyDown(key))
		KeyDown(key);
	else if (input.IsKeyUp(key))
		KeyUp(key);
}