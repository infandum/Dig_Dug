#include "MiniginPCH.h"
#include "MoveCommand.h"
#include "GameObject.h"

void dae::MoveCommand::Execute(GameObject& gameObject)
{
	UNREFERENCED_PARAMETER(gameObject);
	//m_GameObject = std::make_shared<GameObject>(gameObject);
	//if(m_KeyDown == SDL_KEYDOWN){
	//
	std::cout << gameObject.GetName() << ">> ATTACKS!!" << std::endl;
	//}

}

void dae::MoveCommand::KeyDown(SDL_Keycode key) const
{
	glm::vec3 dir;
	extern const float g_MoveSpeed;
	switch (key)
	{
	case SDLK_LEFT:
		dir = { -g_MoveSpeed, 0, 0 };
		m_GameObject->GetComponent<TransformComponent>()->SetVelocity(dir);
		break;
	case SDLK_RIGHT:
		dir = { g_MoveSpeed, 0, 0 };
		m_GameObject->GetComponent<TransformComponent>()->SetVelocity(dir);
		break;
	case SDLK_UP:
		dir = { 0, -g_MoveSpeed, 0 };
		m_GameObject->GetComponent<TransformComponent>()->SetVelocity(dir);
		break;
	case SDLK_DOWN:
		dir = { 0, g_MoveSpeed, 0 };
		m_GameObject->GetComponent<TransformComponent>()->SetVelocity(dir);
		break;
	default: ;
	}
}

void dae::MoveCommand::KeyUp(SDL_Keycode key) const
{
	glm::vec3 dir = { 0.0f, 0.f, 0.f };
	switch (key)
	{
	case SDLK_LEFT:
		m_GameObject->GetComponent<TransformComponent>()->SetVelocity(dir);
		break;
	case SDLK_RIGHT:
		m_GameObject->GetComponent<TransformComponent>()->SetVelocity(dir);
		break;
	case SDLK_UP:
		m_GameObject->GetComponent<TransformComponent>()->SetVelocity(dir);
		break;
	case SDLK_DOWN:
		m_GameObject->GetComponent<TransformComponent>()->SetVelocity(dir);
		break;
	default:;
	}
}
