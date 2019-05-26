#include "MiniginPCH.h"
#include "InputManager.h"
#include "ServiceLocator.h"
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
		GetButtonState(command->GetButton());
		if ((IsPressed(command->GetButton()) || IsPressed(command->GetKey())) && command->GetOwner() == owner)
		{	
			if(m_WasPressed != command->GetButton())
			{
				m_WasPressed = command->GetButton();
			}
				
			return command;
		}
	}
	//m_WasPressed = ControllerButton::ButtonNone;
	return nullptr;
}

bool dae::InputManager::IsPressed(ControllerButton button) 
{
	bool isPressed = (currentState.Gamepad.wButtons & WORD(button)) != 0;
	return isPressed;
}

bool dae::InputManager::IsPressed(SDL_Keycode key) const
{
	return m_KeyDown == key || m_KeyUp == key;
}

bool dae::InputManager::WasPressed(ControllerButton button)
{
	if(button != ControllerButton::ButtonNone)
		return m_WasPressed == button;

	return false;
}

void dae::InputManager::GetButtonState(ControllerButton button)
{
	if (WasPressed(button))
	{
		if (IsPressed(button))
			m_IsKeyDown = true;
		else
			m_IsKeyUp = true;
	}
	else
	{
		if (IsPressed(button))
			m_IsKeyDown = true;
		else
			m_IsKeyUp = false;
	}
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