#pragma once
#include <XInput.h>
#include <SDL.h>
#include "SceneObject.h"

namespace dae
{
	class GameObject;
	enum class ControllerButton;
	class Command;
	class InputManager final
	{
	public:
		bool ProcessInput();
		std::shared_ptr<Command> HandleInput(SceneObject* owner);
			
		bool IsPressed(ControllerButton button) ;
		bool IsPressed(SDL_Keycode key) const;

		bool IsKeyDown() const;
		bool IsKeyUp() const;

		bool IsButtonDown() const;
		bool IsButtonUp() const;

		void AddCommand(std::shared_ptr<Command> command, ControllerButton button, SDL_Keycode key, GameObject* owner);

		void CloseWindow() { m_CloseWindow = true; }

	private:


		XINPUT_STATE currentState{};
		SDL_Event m_Event{};

		ControllerButton m_WasPressed = ControllerButton::ButtonNone;

		SDL_Keycode m_KeyDown{};
		SDL_Keycode m_KeyUp{};

		bool m_DoAgain = false;;

		bool m_IsKeyDown = false;
		bool m_IsKeyUp = false;

		bool m_IsButtonDown = false;
		bool m_IsButtonUp = false;

		bool m_CloseWindow = false;

		std::shared_ptr<Command> m_LastCommand = nullptr;

		std::vector<std::shared_ptr<Command>> m_pCommands;

	};
}
