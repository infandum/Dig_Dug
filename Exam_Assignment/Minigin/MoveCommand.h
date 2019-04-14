#pragma once
#include "Command.h"

namespace dae
{
	class MoveCommand : public Command
	{
	public:
		void Execute(GameObject& gameObject) override;

		void SetButton(ControllerButton button)override { m_Button = button; };
		ControllerButton GetButton() override { return m_Button; };

		void SetKey(const SDL_Keycode key) override { m_Key = key; }
		SDL_Keycode GetKey() override { return m_Key; }

		void KeyDown(SDL_Keycode key) const override;
		void KeyUp(SDL_Keycode key) const override;

	private:
		
		ControllerButton m_Button{};
		SDL_Keycode m_Key{};
	};
}