#pragma once
#include <XInput.h>
#include "Singleton.h"
#include "Command.h"
#include <SDL.h>

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		bool IsPressed(ControllerButton button) const;
		bool IsKeyDown(SDL_Keycode& key) const;
		bool IsKeyUp(SDL_Keycode& key) const;

		void AddCommand(Command* command, ControllerButton button);
	private:
		bool m_IsKeyDown = false;
		bool m_IsKeyUp = false;
		XINPUT_STATE currentState{};
		SDL_Event m_Event{};
		SDL_Keycode m_Key{};
		std::vector<Command*> m_pCommands{};
	};
}
