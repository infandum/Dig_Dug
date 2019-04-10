#include "MiniginPCH.h"
#include "GameObject.h"
#include "Components.h"
//#include <SDL.h>
#include "InputManager.h"

void dae::InputComponent::KeyUp(SDL_Keycode key)
{
	glm::vec3 dir = m_TransformComponent->GetDirection();
	switch (key)
	{
	case SDLK_LEFT:
		m_TransformComponent->SetDirection(dir);
		break;
	case SDLK_RIGHT:
		m_TransformComponent->SetDirection(dir);
		break;
	case SDLK_UP:
		m_TransformComponent->SetDirection(dir);
		break;
	case SDLK_DOWN:
		m_TransformComponent->SetDirection(dir);
		break;
	}
}

void dae::InputComponent::KeyDown(SDL_Keycode key)
{
	glm::vec3 dir = { 0, 0, 0 };
	switch (key)
	{
	case SDLK_LEFT:
		dir = { -1, 0, 0 };
		m_TransformComponent->SetDirection(dir);
		break;
	case SDLK_RIGHT:
		dir = { 1, 0, 0 };
		m_TransformComponent->SetDirection(dir);
		break;
	case SDLK_UP:
		dir = { 0, -1, 0 };
		m_TransformComponent->SetDirection(dir);
		break;
	case SDLK_DOWN:
		dir = { 0, 1, 0 };
		m_TransformComponent->SetDirection(dir);
		break;
	}
}

void dae::InputComponent::Update(float& deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	if (!m_TransformComponent)
		m_TransformComponent = GetGameObject()->GetComponent<TransformComponent>();
	auto& input = InputManager::GetInstance();

	SDL_Keycode key;
	if (input.IsKeyDown(key))
		KeyDown(key);
	else if (input.IsKeyUp(key))
		KeyUp(key);
}