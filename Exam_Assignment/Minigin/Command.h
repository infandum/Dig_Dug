#pragma once
#include <SDL_keycode.h>
#include "GameObject.h"

extern  const float g_MoveSpeed;

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

	protected:
		//std::shared_ptr<GameObject> m_GameObject{};
		ControllerButton m_Button{};
		SDL_Keycode m_Key{};
	};

	class UpCommand : public Command
	{
	public:
		void Execute(GameObject& gameObject) override;
	};

	inline void UpCommand::Execute(GameObject& gameObject)
	{
		auto& input = InputManager::GetInstance();
		if (gameObject.GetTransform())
		{
			if (input.IsKeyDown())
				gameObject.GetTransform()->SetVelocity({ 0, -g_MoveSpeed, 0 });
			if (input.IsKeyUp())
				gameObject.GetTransform()->SetVelocity({ 0, 0, 0 });
		}
	}

	class DownCommand : public Command
	{
	public:
		void Execute(GameObject& gameObject) override;
	};

	inline void DownCommand::Execute(GameObject& gameObject)
	{
		auto& input = InputManager::GetInstance();
		if (gameObject.GetTransform())
		{
			if (input.IsKeyDown())
				gameObject.GetTransform()->SetVelocity({ 0, g_MoveSpeed, 0 });
			if (input.IsKeyUp())
				gameObject.GetTransform()->SetVelocity({ 0, 0, 0 });
		}
	}

	class LeftCommand : public Command
	{
	public:
		void Execute(GameObject& gameObject) override;
	};

	inline void LeftCommand::Execute(GameObject& gameObject)
	{
		auto& input = InputManager::GetInstance();
		if (gameObject.GetTransform())
		{
			if (input.IsKeyDown())
				gameObject.GetTransform()->SetVelocity({ -g_MoveSpeed, 0, 0 });
			if (input.IsKeyUp())
				gameObject.GetTransform()->SetVelocity({ 0, 0, 0 });
		}
	}

	class RightCommand : public Command
	{
	public:
		void Execute(GameObject& gameObject) override;
	};

	inline void RightCommand::Execute(GameObject& gameObject)
	{
		auto& input = InputManager::GetInstance();
		if (gameObject.GetTransform())
		{
			if (input.IsKeyDown())
				gameObject.GetTransform()->SetVelocity({ g_MoveSpeed, 0, 0 });
			if (input.IsKeyUp())
				gameObject.GetTransform()->SetVelocity({ 0, 0, 0 });
		}
	}

	class AttackCommand : public Command
	{
	public:
		void Execute(GameObject& gameObject) override;
	};

	inline void AttackCommand::Execute(GameObject& gameObject)
	{
		std::cout << gameObject.GetName() << '\n';
	}
};