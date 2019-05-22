#pragma once
#include <SDL_keycode.h>
#include "GameObject.h"
#include "ServiceLocator.h"
#include "MoveComponent.h"

//TODO: RETHINK COMMANDS ASSIGNEMENT

namespace dae
{
	//6class GameObject;
	enum class ControllerButton;
	class Command
	{
	public:
		virtual void Execute() = 0;
		virtual ~Command() = default;

		virtual void SetButton(ControllerButton button) { m_Button = button; }
		virtual ControllerButton GetButton() { return m_Button; }

		virtual void SetKey(const SDL_Keycode key) { m_Key = key; }
		virtual SDL_Keycode GetKey() { return m_Key; }

		virtual void SetOwner(GameObject* owner) { m_pOwner = owner; }
		virtual GameObject* GetOwner() { return m_pOwner; }

	protected:

		virtual void notify(NotifyEvent event) const;
		bool m_DoOnce = false;
		ControllerButton m_Button{};
		SDL_Keycode m_Key{};
		const InputManager* m_Input = ServiceLocator::GetInputManager();
		GameObject* m_pOwner = nullptr;
	};

	inline void Command::notify( NotifyEvent event) const
	{
		if(m_pOwner->GetSprite())
			m_pOwner->GetSprite()->onNotify(event);
	}

	class ExitCommand : public Command
	{
	public:
		void Execute() override;
	};

	inline void ExitCommand::Execute()
	{
		/*auto input = ServiceLocator::GetInputManager();
		input->CloseWindow();*/
		if (m_Input->IsKeyDown())
		{
			
			if(!m_DoOnce)
			{
				auto scene = ServiceLocator::GetSceneManager();
				scene->NextScene();
				std::cout << "DO ONCE" << std::endl;
				m_DoOnce = true;
				
			}
			
		}

		if (m_Input->IsKeyUp())
		{
			m_DoOnce = false;
		}
	}


	class UpCommand : public Command
	{
	public:
		void Execute() override;
	};
	inline void UpCommand::Execute()
	{
		if (m_pOwner->GetComponent<MoveComponent>() && !m_pOwner->GetComponent<PlayerComponent>()->IsAttacking())
		{
			if (m_Input->IsKeyDown())
			{
				notify(NotifyEvent::EVENT_MOVE);

				m_pOwner->GetComponent<MoveComponent>()->SetVelocity({ 0, -m_pOwner->GetComponent<MoveComponent>()->GetMoveSpeed(), 0 });
			}

			if (m_Input->IsKeyUp())
			{
				notify(NotifyEvent::EVENT_IDLE);

				m_pOwner->GetComponent<MoveComponent>()->SetVelocity({ 0, 0, 0 });
			}

		}
	}

	class DownCommand : public Command
	{
	public:
		void Execute() override;
	};

	inline void DownCommand::Execute()
	{
		if (m_pOwner->GetComponent<MoveComponent>() && !m_pOwner->GetComponent<PlayerComponent>()->IsAttacking())
		{
			if (m_Input->IsKeyDown())
			{
				notify(NotifyEvent::EVENT_MOVE);

				m_pOwner->GetComponent<MoveComponent>()->SetVelocity({ 0, m_pOwner->GetComponent<MoveComponent>()->GetMoveSpeed(), 0 });
			}

			if (m_Input->IsKeyUp())
			{
				notify(NotifyEvent::EVENT_IDLE);

				m_pOwner->GetComponent<MoveComponent>()->SetVelocity({ 0, 0, 0 });
			}

		}
	}

	class LeftCommand : public Command
	{
	public:
		void Execute() override;
	};

	inline void LeftCommand::Execute()
	{
		if (m_pOwner->GetTransform() && !m_pOwner->GetComponent<PlayerComponent>()->IsAttacking())
		{
			if (m_Input->IsKeyDown())
			{
				notify(NotifyEvent::EVENT_MOVE);

				m_pOwner->GetComponent<MoveComponent>()->SetVelocity({ -m_pOwner->GetComponent<MoveComponent>()->GetMoveSpeed(), 0, 0 });
			}

			if (m_Input->IsKeyUp())
			{
				notify(NotifyEvent::EVENT_IDLE);

				m_pOwner->GetComponent<MoveComponent>()->SetVelocity({ 0, 0, 0 });
			}

		}
	}

	class RightCommand : public Command
	{
	public:
		void Execute() override;
	};

	inline void RightCommand::Execute()
	{
		
		if (m_pOwner->GetTransform() && !m_pOwner->GetComponent<PlayerComponent>()->IsAttacking())
		{
			if (m_Input->IsKeyDown())
			{
				notify(NotifyEvent::EVENT_MOVE);

				m_pOwner->GetComponent<MoveComponent>()->SetVelocity({ m_pOwner->GetComponent<MoveComponent>()->GetMoveSpeed(), 0, 0 });
			}
				
			if (m_Input->IsKeyUp())
			{
				notify(NotifyEvent::EVENT_IDLE);

				m_pOwner->GetComponent<MoveComponent>()->SetVelocity({ 0, 0, 0 });
			}
		}
	}

	class AttackCommand : public Command
	{
	public:
		void Execute() override;
	};

	inline void AttackCommand::Execute()
	{
		//std::cout << m_pOwner->GetName() << ">> ATTACKING" << '\n';
		bool attack;
		if (m_Input->IsKeyDown())
		{
			notify(NotifyEvent::EVENT_ACTION);
			m_pOwner->GetComponent<PlayerComponent>()->Attack(attack = true);
			m_pOwner->GetComponent<MoveComponent>()->SetVelocity({ 0, 0, 0 });
			/*if (gameObject.GetChildCount() > 0)
				if (gameObject.GetChild(0).get()->GetIsFollowingParent())
					gameObject.GetChild(0).get()->SetIsFollowParent(false);
				else
					gameObject.GetChild(0).get()->SetIsFollowParent(true);*/

			//if (m_pOwner->GetChildCount() > 0)
			//	if (m_pOwner->GetChild(0).get()->IsEnabled())
			//		m_pOwner->GetChild(0).get()->Enable(false);
			//	else
			//		m_pOwner->GetChild(0).get()->Enable(true);
		}

		if (m_Input->IsKeyUp())
		{
			notify(NotifyEvent::EVENT_IDLE);
			m_pOwner->GetComponent<PlayerComponent>()->Attack(attack = false);
		}
	}
};