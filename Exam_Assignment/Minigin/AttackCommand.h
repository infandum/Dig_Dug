#pragma once
#include "Command.h"
namespace dae
{
	class AttackCommand : public Command
	{
	public:
		void Execute(GameObject& gameObject) override;

		void SetButton(ControllerButton button)override { m_Button = button; };
		ControllerButton GetButton() override { return m_Button; };

		void SetKey(const SDL_Keycode key) override { m_Key = key; }
		SDL_Keycode GetKey() override { return m_Key; }
	private:
		ControllerButton m_Button{};
		SDL_Keycode m_Key{};
	};
}