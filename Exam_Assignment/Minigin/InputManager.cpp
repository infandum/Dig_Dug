#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>


bool dae::InputManager::ProcessInput()
{
	ZeroMemory(&currentState, sizeof(XINPUT_STATE));
	XInputGetState(0, &currentState);

	
	while (SDL_PollEvent(&m_Event)) {
		if (m_Event.type == SDL_QUIT) {
			return false;
		}
		if (m_Event.type == SDL_KEYDOWN) {
			m_IsKeyDown = true;
			m_IsKeyUp = false;
			m_Key = m_Event.key.keysym.sym;
		}
		if (m_Event.type == SDL_KEYUP) {
			m_IsKeyUp = true;
			m_IsKeyDown = false;
			m_Key = m_Event.key.keysym.sym;
		}
		if (m_Event.type == SDL_MOUSEBUTTONDOWN) {
			
		}
	}
	return true;
}

bool dae::InputManager::IsPressed(ControllerButton button) const
{
	switch (button)
	{
	case ControllerButton::ButtonA:
		return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_A;
	case ControllerButton::ButtonB:
		return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_B;
	case ControllerButton::ButtonX:
		return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_X;
	case ControllerButton::ButtonY:
		return currentState.Gamepad.wButtons & XINPUT_GAMEPAD_Y;
	default: return false;
	}
}

bool dae::InputManager::IsKeyDown(SDL_Keycode& key) const
{
	key = m_Key;
	return m_IsKeyDown;
}

bool dae::InputManager::IsKeyUp(SDL_Keycode& key) const
{
	key = m_Key;
	return m_IsKeyUp;
}

void dae::InputManager::AddCommand(Command* command, ControllerButton button)
{
	//Duplicate check
	for (auto& com : m_pCommands)
	{
		if (typeid(*com) == typeid(*command) && com->GetButton() == button)
		{
			std::cout << "Duplicate Command >> " << typeid(*command).name() << std::endl;
			delete command;
			command = nullptr;
			return;
		}
	}
	m_pCommands.push_back(command);
	m_pCommands.at(m_pCommands.size() - 1)->SetButton(button);
}
