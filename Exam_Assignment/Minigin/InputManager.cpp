#include "MiniginPCH.h"
#include "InputManager.h"
#include "DataStructs.h"
#include "Command.h"

bool dae::InputManager::ProcessInput()
{
	ZeroMemory(&currentState, sizeof(XINPUT_STATE));
	XInputGetState(0, &currentState);

	/*for (auto& command : m_pCommands)
	{
		if (IsPressed(command->GetButton()) || IsPressed(command->GetKey()))
		{
			if (command)
			return true;
		}
	}*/
	
	m_IsKeyUp = false;
	m_IsKeyDown = false;

	while (SDL_PollEvent(&m_Event)) {
		if (m_Event.type == SDL_QUIT) {
			return false;
		}
		if (m_Event.type == SDL_KEYDOWN) {
			m_IsKeyDown = true;
			m_KeyDown = m_Event.key.keysym.sym;
		}
		if (m_Event.type == SDL_KEYUP) {
			std::cout << "KeyUp\n";
			m_IsKeyUp = true;
			m_KeyUp = m_Event.key.keysym.sym;
		}
		if (m_Event.type == SDL_MOUSEBUTTONDOWN) {
			
		}
	}

	return true;
}

std::shared_ptr<dae::Command> dae::InputManager::HandleInput()
{
	//for (auto& command : m_pCommands)
	//{
	//	if (/*IsPressed(command->GetButton()) || */IsPressed(command->GetKey()))
	//	{
	//		return command;
	//	}
	//}
	return nullptr;
}

bool dae::InputManager::IsPressed(ControllerButton button) const
{
	return (currentState.Gamepad.wButtons & WORD(button)) != 0;
}

bool dae::InputManager::IsPressed(SDL_Keycode key) const
{
	return m_Event.key.keysym.sym == key;
}

bool dae::InputManager::IsKeyDown() const
{
	return m_IsKeyDown;
}

bool dae::InputManager::IsKeyDown(SDL_Keycode& key) const
{
	key = m_KeyDown;
	return m_IsKeyDown;
}

bool dae::InputManager::IsKeyUp(SDL_Keycode& key) const
{
	key = m_KeyUp;
	return m_IsKeyUp;
}

void dae::InputManager::AddCommand(std::shared_ptr<Command> command, ControllerButton button, SDL_Keycode key)
{
	//Duplicate check
	for (auto& com : m_pCommands)
	{
		if (typeid(*com) == typeid(*command) && com->GetButton() == button)
		{
			std::cout << "Duplicate Command >> " << typeid(*command).name() << std::endl;
			return;
		}
	}
	m_pCommands.push_back(command);
	m_pCommands.at(m_pCommands.size() - 1)->SetButton(button);
	m_pCommands.at(m_pCommands.size() - 1)->SetKey(key);
}
