#include "MiniginPCH.h"
#include "PlayerStates.h"
#include "GameObject.h"
#include "ServiceLocator.h"

std::shared_ptr<dae::BaseState> dae::IdlePlayerState::Swap(NotifyEvent event, GameObject& gameObject)
{
	if (gameObject.GetComponent<PlayerComponent>()->IsCrushed())
		return gameObject.GetComponent<SpriteComponent>()->GetState<CrushedPlayerState>();

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
	if (gameObject.GetComponent<PlayerComponent>()->IsCrushed())
		return gameObject.GetComponent<SpriteComponent>()->GetState<CrushedPlayerState>();

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
	if (gameObject.GetComponent<PlayerComponent>()->IsCrushed())
		return gameObject.GetComponent<SpriteComponent>()->GetState<CrushedPlayerState>();

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
	if (gameObject.GetComponent<PlayerComponent>()->IsCrushed())
		return gameObject.GetComponent<SpriteComponent>()->GetState<CrushedPlayerState>();

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
		return gameObject.GetComponent<SpriteComponent>()->GetState<ActionPlayerState>();
	default:;
	}

	return nullptr;
}

std::shared_ptr<dae::BaseState> dae::ActionPlayerState::Swap(NotifyEvent event, GameObject& gameObject)
{
	if (gameObject.GetComponent<PlayerComponent>()->IsCrushed())
		return gameObject.GetComponent<SpriteComponent>()->GetState<CrushedPlayerState>();

	if (!gameObject.GetComponent<PlayerComponent>()->IsAttacking())
		return gameObject.GetComponent<SpriteComponent>()->GetState<IdlePlayerState>();

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
	case NotifyEvent::EVENT_ACTION:
		return nullptr;
	default:;
	}
	return nullptr;
}

std::shared_ptr<dae::BaseState> dae::DeadPlayerState::Swap(NotifyEvent event, GameObject& gameObject)
{
	switch (event)
	{
	case NotifyEvent::EVENT_SPAWN:
		return gameObject.GetComponent<SpriteComponent>()->GetState<IdlePlayerState>();
	default:
		return nullptr;
	}
}

std::shared_ptr<dae::BaseState> dae::CrushedPlayerState::Swap(NotifyEvent event, GameObject& gameObject)
{
	const auto move = gameObject.GetComponent<MoveComponent>();
	gameObject.GetCollision()->EnableCollision(false);

	const auto trans = gameObject.GetTransform();
	const iVector2 currTileIndex = { trans->GetPositionIndex().x , trans->GetPositionIndex().y };
	const auto currTile = m_pLevelManager->GetTile(currTileIndex.x, currTileIndex.y);

	if(event == NotifyEvent::EVENT_SPAWN)
	{
		m_IsCrushed = false;
		return gameObject.GetComponent<SpriteComponent>()->GetState<IdlePlayerState>();
	}

	if ((currTile->GetTileState() == TileState::USED && !currTile->GetIsConnectedBorder(Direction::DOWN)) && gameObject.GetComponent<MoveComponent>()->IsCentered())
	{
		gameObject.GetComponent<MoveComponent>()->SetMovementInput({ 0, 0, 0 });
		gameObject.GetComponent<PlayerComponent>()->Dead();
	}
	return nullptr;
}

//WEAPON STATE
//************
std::shared_ptr<dae::BaseState> dae::WeaponState::Swap(NotifyEvent event, GameObject& gameObject)
{
	if (event == NotifyEvent::EVENT_SPAWN)
	{
		return gameObject.GetComponent<SpriteComponent>()->GetState<WeaponState>();
	}

	return nullptr;
}