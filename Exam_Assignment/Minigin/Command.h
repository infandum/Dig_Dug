#pragma once
#include <SDL_keycode.h>

namespace dae
{
	class GameObject;
	enum class ControllerButton;
	//class SDL_Keycode;
	class Command
	{
	public:
		virtual void Execute(GameObject& gameObject) = 0;
		virtual ~Command() = default;

		virtual void SetButton(ControllerButton button) { m_Button = button; }
		virtual ControllerButton GetButton() { return m_Button; }

		virtual void SetKey(const SDL_Keycode key) { m_Key = key; }
		virtual SDL_Keycode GetKey() { return m_Key; }

	/*	virtual void SetKey(SDL_Keycode key) = 0;
		virtual SDL_Keycode GetKey() = 0;

		virtual void KeyDown(SDL_Keycode) const = 0;
		virtual void KeyUp(SDL_Keycode) const  = 0;*/

	protected:
		std::shared_ptr<GameObject> m_GameObject{};
		ControllerButton m_Button{};
		SDL_Keycode m_Key{};
	};
};