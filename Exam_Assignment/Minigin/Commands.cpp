#include "MiniginPCH.h"
#include "Commands.h"
#include "GameObject.h"

void dae::Command::notify(GameObject* gameObject, NotifyEvent event) const
{
	if (gameObject->GetSprite())
		gameObject->GetSprite()->onNotify(event);
}

void dae::UpCommand::Execute(GameObject* gameObject)
{
	auto input = ServiceLocator::GetInputManager();
	if (gameObject.GetComponent<MoveComponent>())
	{
		if (input->IsKeyDown())
		{
			notify(gameObject, NotifyEvent::EVENT_MOVE);

			gameObject.GetComponent<MoveComponent>()->SetVelocity({ 0, -g_MoveSpeed, 0 });
		}

		if (input->IsKeyUp())
		{
			notify(gameObject, NotifyEvent::EVENT_IDLE);

			gameObject.GetComponent<MoveComponent>()->SetVelocity({ 0, 0, 0 });
		}

	}
}

void dae::DownCommand::Execute(GameObject* gameObject)
{
	if (gameObject.GetComponent<MoveComponent>())
	{
		if (m_Input->IsKeyDown())
		{
			notify(gameObject, NotifyEvent::EVENT_MOVE);

			gameObject.GetComponent<MoveComponent>()->SetVelocity({ 0, g_MoveSpeed, 0 });
		}

		if (m_Input->IsKeyUp())
		{
			notify(gameObject, NotifyEvent::EVENT_IDLE);

			gameObject.GetComponent<MoveComponent>()->SetVelocity({ 0, 0, 0 });
		}

	}
}

void dae::LeftCommand::Execute(GameObject* gameObject)
{
	if (gameObject.GetTransform())
	{
		if (m_Input->IsKeyDown())
		{
			notify(gameObject, NotifyEvent::EVENT_MOVE);

			gameObject.GetComponent<MoveComponent>()->SetVelocity({ -g_MoveSpeed, 0, 0 });
		}

		if (m_Input->IsKeyUp())
		{
			notify(gameObject, NotifyEvent::EVENT_IDLE);

			gameObject.GetComponent<MoveComponent>()->SetVelocity({ 0, 0, 0 });
		}

	}
}

void dae::RightCommand::Execute(GameObject* gameObject)
{

	if (gameObject.GetTransform())
	{
		if (m_Input->IsKeyDown())
		{
			notify(gameObject, NotifyEvent::EVENT_MOVE);

			gameObject.GetComponent<MoveComponent>()->SetVelocity({ g_MoveSpeed, 0, 0 });
		}

		if (m_Input->IsKeyUp())
		{
			notify(gameObject, NotifyEvent::EVENT_IDLE);

			gameObject.GetComponent<MoveComponent>()->SetVelocity({ 0, 0, 0 });
		}

	}
}

void dae::AttackCommand::Execute(GameObject* gameObject)
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