#pragma once
#include <SDL_keycode.h>
#include "GameObject.h"
#include "ServiceLocator.h"

extern  const float g_MoveSpeed;

//TODO: RETHINK COMMANDS ASSIGNEMENT

namespace dae
{
	class GameObject;
	enum class ControllerButton;
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

		virtual void notify(GameObject& gameObject, NotifyEvent event) const;

		ControllerButton m_Button{};
		SDL_Keycode m_Key{};
		const InputManager* m_Input = ServiceLocator::GetInputManager();
	};

	class UpCommand : public Command
	{
	public:
		void Execute(GameObject& gameObject) override;
	};

	inline void Command::notify(GameObject& gameObject, NotifyEvent event) const
	{
		if(gameObject.GetSprite())
			gameObject.GetSprite()->onNotify(event);
	}

	inline void UpCommand::Execute(GameObject& gameObject)
	{
		if (gameObject.GetTransform())
		{
			if (m_Input->IsKeyDown())
			{
				notify(gameObject, NotifyEvent::EVENT_MOVE);

				gameObject.GetTransform()->SetVelocity({ 0, -g_MoveSpeed, 0 });
			}

			if (m_Input->IsKeyUp())
			{
				notify(gameObject, NotifyEvent::EVENT_IDLE);

				gameObject.GetTransform()->SetVelocity({ 0, 0, 0 });
			}

		}
	}

	class DownCommand : public Command
	{
	public:
		void Execute(GameObject& gameObject) override;
	};

	inline void DownCommand::Execute(GameObject& gameObject)
	{
		if (gameObject.GetTransform())
		{
			if (m_Input->IsKeyDown())
			{
				notify(gameObject, NotifyEvent::EVENT_MOVE);

				gameObject.GetTransform()->SetVelocity({ 0, g_MoveSpeed, 0 });
			}

			if (m_Input->IsKeyUp())
			{
				notify(gameObject, NotifyEvent::EVENT_IDLE);

				gameObject.GetTransform()->SetVelocity({ 0, 0, 0 });
			}

		}
	}

	class LeftCommand : public Command
	{
	public:
		void Execute(GameObject& gameObject) override;
	};

	inline void LeftCommand::Execute(GameObject& gameObject)
	{
		if (gameObject.GetTransform())
		{
			if (m_Input->IsKeyDown())
			{
				notify(gameObject, NotifyEvent::EVENT_MOVE);

				gameObject.GetTransform()->SetVelocity({ -g_MoveSpeed, 0, 0 });
			}

			if (m_Input->IsKeyUp())
			{
				notify(gameObject, NotifyEvent::EVENT_IDLE);

				gameObject.GetTransform()->SetVelocity({ 0, 0, 0 });
			}

		}
	}

	class RightCommand : public Command
	{
	public:
		void Execute(GameObject& gameObject) override;
	};

	inline void RightCommand::Execute(GameObject& gameObject)
	{
		
		if (gameObject.GetTransform())
		{
			if (m_Input->IsKeyDown())
			{
				notify(gameObject, NotifyEvent::EVENT_MOVE);

				gameObject.GetTransform()->SetVelocity({ g_MoveSpeed, 0, 0 });
			}
				
			if (m_Input->IsKeyUp())
			{
				notify(gameObject, NotifyEvent::EVENT_IDLE);

				gameObject.GetTransform()->SetVelocity({ 0, 0, 0 });
			}
				
		}
	}

	class AttackCommand : public Command
	{
	public:
		void Execute(GameObject& gameObject) override;
	};

	inline void AttackCommand::Execute(GameObject& gameObject)
	{
		std::cout << gameObject.GetName() << ">> ATTACKING" << '\n';
		if (m_Input->IsKeyDown())
		{
			notify(gameObject, NotifyEvent::EVENT_ACTION);
			/*if (gameObject.GetChildCount() > 0)
				if (gameObject.GetChild(0).get()->GetIsFollowingParent())
					gameObject.GetChild(0).get()->SetIsFollowParent(false);
				else
					gameObject.GetChild(0).get()->SetIsFollowParent(true);*/

			if (gameObject.GetChildCount() > 0)
				if (gameObject.GetChild(0).get()->GetIsActive())
					gameObject.GetChild(0).get()->SetIsActive(false);
				else
					gameObject.GetChild(0).get()->SetIsActive(true);
		}

		if (m_Input->IsKeyUp())
		{
			notify(gameObject, NotifyEvent::EVENT_IDLE);
		}
	}
};