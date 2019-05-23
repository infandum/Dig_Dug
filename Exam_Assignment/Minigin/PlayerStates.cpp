#include "MiniginPCH.h"
#include "PlayerStates.h"
#include "GameObject.h"
#include "ServiceLocator.h"

std::shared_ptr<dae::BaseState> dae::IdlePlayerState::Swap(NotifyEvent event, GameObject& gameObject)
{
	switch (event)
	{
	case NotifyEvent::EVENT_IDLE:
		return nullptr;
	case NotifyEvent::EVENT_MOVE:
		if (!gameObject.GetComponent<MoveComponent>()->CheckOccupiedTileMove())
			return nullptr;

		if (gameObject.GetComponent<MoveComponent>()->CheckTileSwapping())
			return gameObject.GetComponent<SpriteComponent>()->GetState<DigPlayerState>();// std::make_shared<DigPlayerState>();

		return gameObject.GetComponent<SpriteComponent>()->GetState<MovePlayerState>();
	case NotifyEvent::EVENT_ACTION:
		return gameObject.GetComponent<SpriteComponent>()->GetState<AttackPlayerState>();
	case NotifyEvent::EVENT_COLLISION:
		return gameObject.GetComponent<SpriteComponent>()->GetState<DeadPlayerState>();
	case NotifyEvent::EVENT_SPAWN:
		return nullptr;
	default:;
	}

	return nullptr;
}

std::shared_ptr<dae::BaseState> dae::MovePlayerState::Swap(NotifyEvent event, GameObject& gameObject)
{
	switch (event)
	{
	case NotifyEvent::EVENT_IDLE:
		return gameObject.GetComponent<SpriteComponent>()->GetState<IdlePlayerState>();
	case NotifyEvent::EVENT_MOVE:
		if (!gameObject.GetComponent<MoveComponent>()->CheckOccupiedTileMove())
			return gameObject.GetComponent<SpriteComponent>()->GetState<IdlePlayerState>();

		if (gameObject.GetComponent<MoveComponent>()->CheckTileSwapping())
			return gameObject.GetComponent<SpriteComponent>()->GetState<DigPlayerState>();

		return nullptr;
	case NotifyEvent::EVENT_ACTION:
		return gameObject.GetComponent<SpriteComponent>()->GetState<AttackPlayerState>();
	case NotifyEvent::EVENT_COLLISION:
		return gameObject.GetComponent<SpriteComponent>()->GetState<DeadPlayerState>();
	default:;
	}

	return nullptr;
}

std::shared_ptr<dae::BaseState> dae::DigPlayerState::Swap(NotifyEvent event, GameObject& gameObject)
{
	switch (event)
	{
	case NotifyEvent::EVENT_IDLE:
		return gameObject.GetComponent<SpriteComponent>()->GetState<IdlePlayerState>();
	case NotifyEvent::EVENT_MOVE:
		if (!gameObject.GetComponent<MoveComponent>()->CheckOccupiedTileMove())
			return gameObject.GetComponent<SpriteComponent>()->GetState<IdlePlayerState>();

		if (!gameObject.GetComponent<MoveComponent>()->CheckTileSwapping())
			return gameObject.GetComponent<SpriteComponent>()->GetState<MovePlayerState>();

		return nullptr;
	case NotifyEvent::EVENT_ACTION:
		if (gameObject.GetComponent<PlayerComponent>()->GetType() == PlayerType::PLAYER_DIGDUG)
			return gameObject.GetComponent<SpriteComponent>()->GetState<AttackPlayerState>();

		return nullptr;
	case NotifyEvent::EVENT_COLLISION:
		return gameObject.GetComponent<SpriteComponent>()->GetState<DeadPlayerState>();
	default:;
	}
	return nullptr;
}

std::shared_ptr<dae::BaseState> dae::AttackPlayerState::Swap(NotifyEvent event, GameObject& gameObject)
{
	UNREFERENCED_PARAMETER(gameObject);
	switch (event)
	{
	case NotifyEvent::EVENT_IDLE:
		return gameObject.GetComponent<SpriteComponent>()->GetState<IdlePlayerState>();
	case NotifyEvent::EVENT_MOVE:
		return gameObject.GetComponent<SpriteComponent>()->GetState<MovePlayerState>();
	case NotifyEvent::EVENT_ACTION:
		return nullptr;
	case NotifyEvent::EVENT_COLLISION:
		return gameObject.GetComponent<SpriteComponent>()->GetState<DeadPlayerState>();
	case NotifyEvent::EVENT_INTERACT:
		return gameObject.GetComponent<SpriteComponent>()->GetState<AttackPlayerState>();
	default:;
	}

	return nullptr;
}

std::shared_ptr<dae::BaseState> dae::ActionPlayerState::Swap(NotifyEvent event, GameObject& gameObject)
{
	UNREFERENCED_PARAMETER(event);
	UNREFERENCED_PARAMETER(gameObject);
	switch (event)
	{
	case NotifyEvent::EVENT_IDLE:
		return gameObject.GetComponent<SpriteComponent>()->GetState<IdlePlayerState>();
	case NotifyEvent::EVENT_MOVE:
		return gameObject.GetComponent<SpriteComponent>()->GetState<MovePlayerState>();
	case NotifyEvent::EVENT_COLLISION:
		return gameObject.GetComponent<SpriteComponent>()->GetState<DeadPlayerState>();
	case NotifyEvent::EVENT_INTERACT:
		return nullptr;
	default:;
	}
	return nullptr;
}

std::shared_ptr<dae::BaseState> dae::DeadPlayerState::Swap(NotifyEvent event, GameObject& gameObject)
{
	UNREFERENCED_PARAMETER(gameObject);
	switch (event)
	{
	case NotifyEvent::EVENT_IDLE:
		return nullptr;
	case NotifyEvent::EVENT_MOVE:
		return nullptr;
	case NotifyEvent::EVENT_ACTION:
		return nullptr;
	case NotifyEvent::EVENT_COLLISION:
		gameObject.GetComponent<SpriteComponent>()->onNotify(NotifyEvent::EVENT_IDLE);
		return nullptr;
	case NotifyEvent::EVENT_SPAWN:
		return gameObject.GetComponent<SpriteComponent>()->GetState<IdlePlayerState>();
	default:;
	}

	return nullptr;
}

std::shared_ptr<dae::BaseState> dae::CrushedPlayerState::Swap(NotifyEvent event, GameObject& gameObject)
{
	UNREFERENCED_PARAMETER(event);
	UNREFERENCED_PARAMETER(gameObject);
	return nullptr;
}

//WEAPON STATE
//************
std::shared_ptr<dae::BaseState> dae::WeaponState::Swap(NotifyEvent, GameObject&)
{
	return nullptr;
}