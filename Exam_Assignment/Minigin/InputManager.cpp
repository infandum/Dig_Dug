#include "MiniginPCH.h"
#include "InputManager.h"
#include "ServiceLocator.h"
#include "Scene.h"
#include "DataStructs.h"
#include "Commands.h"

bool dae::InputManager::ProcessInput()
{
	ZeroMemory(&currentState, sizeof(XINPUT_STATE));
	XInputGetState(0, &currentState);
	
	m_IsKeyUp = false;
	m_IsKeyDown = false;
	m_KeyDown = 0;
	m_KeyUp = 0;

	if(m_CloseWindow)
		return false;

	while (SDL_PollEvent(&m_Event)) {
		if (m_Event.type == SDL_QUIT) {
			return false;
		}
		if (m_Event.type == SDL_KEYDOWN) {
			m_IsKeyDown = true;
			m_KeyDown = m_Event.key.keysym.sym;
		}
		if (m_Event.type == SDL_KEYUP) {
			m_IsKeyUp = true;
			m_KeyUp = m_Event.key.keysym.sym;
		}
		if (m_Event.type == SDL_MOUSEBUTTONDOWN) {
			
		}
	}

	return true;
}

std::shared_ptr<dae::Command> dae::InputManager::HandleInput(SceneObject* owner)
{
	for (auto& command : m_pCommands)
	{
		if ((IsPressed(command->GetButton()) || IsPressed(command->GetKey())) && command->GetOwner() == owner)
		{
			return command;
		}
	}
	return nullptr;
}

bool dae::InputManager::IsPressed(ControllerButton button) const
{
		return (currentState.Gamepad.wButtons & WORD(button)) != 0;
}

bool dae::InputManager::IsPressed(SDL_Keycode key) const
{
	return m_KeyDown == key || m_KeyUp == key;
}

bool dae::InputManager::IsKeyDown() const
{
	return m_IsKeyDown;
}

bool dae::InputManager::IsKeyUp() const
{
	return m_IsKeyUp;
}

void dae::InputManager::AddCommand(std::shared_ptr<Command> command, ControllerButton button, SDL_Keycode key, GameObject* owner)
{
	//Duplicate check
	for (auto& com : m_pCommands)
	{
		if (typeid(*com) == typeid(*command) && com->GetOwner() == owner)
		{
			std::cout << "Duplicate Command >> GameObject: already has Command of type : " << typeid(*command).name()  << std::endl;
			return;
		}

		if ((com->GetButton() == button && com->GetKey() == key) && com->GetOwner() == owner)
		{
			std::cout << "Duplicate Command >> Key id = " << static_cast<int>(key) << " Command type: " << typeid(*command).name() << std::endl;
			return;
		}
	}
	m_pCommands.push_back(command);
	m_pCommands.at(m_pCommands.size() - 1)->SetButton(button);
	m_pCommands.at(m_pCommands.size() - 1)->SetKey(key);
	m_pCommands.at(m_pCommands.size() - 1)->SetOwner(owner);
}