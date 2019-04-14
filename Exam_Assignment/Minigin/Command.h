#pragma once
#include <SDL.h>

namespace dae
{
	class GameObject;
	enum class ControllerButton;
	class Command
	{
	public:
		virtual void Execute(GameObject& gameObject) = 0;
		virtual ~Command() = default;

		virtual void SetButton(ControllerButton button) = 0;
		virtual ControllerButton GetButton() = 0;

		virtual void SetKey(SDL_Keycode key) = 0;
		virtual SDL_Keycode GetKey() = 0;

		virtual void KeyDown(SDL_Keycode) const = 0;
		virtual void KeyUp(SDL_Keycode) const  = 0;

	protected:
		std::shared_ptr<GameObject> m_GameObject;
	};
};