#pragma once
#include <XInput.h>
#include "Singleton.h"
#include <SDL.h>

namespace dae
{
	enum class ControllerButton;
	class Command;
	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput();
		std::shared_ptr<Command> HandleInput();
			
		bool IsPressed(ControllerButton button) const;
		bool IsPressed(SDL_Keycode key) const;

		bool IsKeyDown() const;
		bool IsKeyUp() const;

		void AddCommand(std::shared_ptr<Command> command, ControllerButton button, SDL_Keycode key);
	private:
		
		XINPUT_STATE currentState{};
		SDL_Event m_Event{};

		SDL_Keycode m_KeyDown{};
		SDL_Keycode m_KeyUp{};

		bool m_IsKeyDown = false;
		bool m_IsKeyUp = false;

		std::vector<std::shared_ptr<Command>> m_pCommands{};

	};
}
