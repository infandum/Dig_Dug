#include "MiniginPCH.h"
#include "NpcStates.h"
#include "GameObject.h"
#include "Components.h"
#include "ServiceLocator.h"

//POOKA STATES
//************
std::shared_ptr<dae::BaseState> dae::PookaIdleState::Swap(NotifyEvent event, GameObject& gameObject)
{
	const auto index = gameObject.GetTransform()->GetPositionIndex();
	const auto tile = m_pLevelManager->GetTile(index.x, index.y);
	const auto move = gameObject.GetComponent<MoveComponent>();
	const auto npc = gameObject.GetComponent<NpcComponent>();
	switch (event)
	{
	case NotifyEvent::EVENT_IDLE:
		if (tile->GetTileState() == TileState::FREE)
			return gameObject.GetComponent<SpriteComponent>()->GetState<PookaGhostState>();

		return nullptr;
	case NotifyEvent::EVENT_MOVE:
		if (move->CheckTileSwapping() && move->IsCentered())
			return nullptr;

		if (gameObject.GetComponent<NpcComponent>()->IsGhosting() || tile->GetTileState() == TileState::FREE)
			return gameObject.GetComponent<SpriteComponent>()->GetState<PookaGhostState>();

		return gameObject.GetComponent<SpriteComponent>()->GetState<PookaMoveState>();
	case NotifyEvent::EVENT_COLLISION:
			
		if(npc->IsHit())
			return gameObject.GetComponent<SpriteComponent>()->GetState<PookaInflateState>();

		return gameObject.GetComponent<SpriteComponent>()->GetState<PookaCrushState>();
	case NotifyEvent::EVENT_SPAWN:
		return nullptr;
	case NotifyEvent::EVENT_ACTION:
		return gameObject.GetComponent<SpriteComponent>()->GetState<PookaCrushState>();
	default:;
	}
	return nullptr;
}

std::shared_ptr<dae::BaseState> dae::PookaMoveState::Swap(NotifyEvent event, GameObject& gameObject)
{
	const auto index = gameObject.GetTransform()->GetPositionIndex();
	const auto tile = m_pLevelManager->GetTile(index.x, index.y);
	const auto move = gameObject.GetComponent<MoveComponent>();
	const auto npc = gameObject.GetComponent<NpcComponent>();
	switch (event)
	{
	case NotifyEvent::EVENT_IDLE:
		if (tile->GetTileState() == TileState::FREE)
			return gameObject.GetComponent<SpriteComponent>()->GetState<PookaGhostState>();

		return gameObject.GetComponent<SpriteComponent>()->GetState<PookaIdleState>();
	case NotifyEvent::EVENT_MOVE:
		if (move->CheckTileSwapping() && move->IsCentered())
			return gameObject.GetComponent<SpriteComponent>()->GetState<PookaIdleState>();

		if (gameObject.GetComponent<NpcComponent>()->IsGhosting() || tile->GetTileState() == TileState::FREE)
			return gameObject.GetComponent<SpriteComponent>()->GetState<PookaGhostState>();

		return gameObject.GetComponent<SpriteComponent>()->GetState<PookaMoveState>();
	case NotifyEvent::EVENT_COLLISION:

		if (npc->IsHit())
			return gameObject.GetComponent<SpriteComponent>()->GetState<PookaInflateState>();

		return gameObject.GetComponent<SpriteComponent>()->GetState<PookaCrushState>();
	case NotifyEvent::EVENT_SPAWN:
		return gameObject.GetComponent<SpriteComponent>()->GetState<PookaIdleState>();
	case NotifyEvent::EVENT_ACTION:
		return gameObject.GetComponent<SpriteComponent>()->GetState<PookaCrushState>();
	default:;
	}
	return nullptr;
}

std::shared_ptr<dae::BaseState> dae::PookaChaseState::Swap(NotifyEvent event, GameObject& gameObject)
{
	const auto index = gameObject.GetTransform()->GetPositionIndex();
	const auto tile = m_pLevelManager->GetTile(index.x, index.y);
	const auto move = gameObject.GetComponent<MoveComponent>();
	const auto npc = gameObject.GetComponent<NpcComponent>();
	switch (event)
	{
	case NotifyEvent::EVENT_IDLE:
		if (tile->GetTileState() == TileState::FREE)
			return gameObject.GetComponent<SpriteComponent>()->GetState<PookaGhostState>();

		return gameObject.GetComponent<SpriteComponent>()->GetState<PookaIdleState>();
	case NotifyEvent::EVENT_MOVE:
		if (move->CheckTileSwapping() && move->IsCentered())
			return gameObject.GetComponent<SpriteComponent>()->GetState<PookaIdleState>();

		if (gameObject.GetComponent<NpcComponent>()->IsGhosting() || tile->GetTileState() == TileState::FREE)
			return gameObject.GetComponent<SpriteComponent>()->GetState<PookaGhostState>();

		return gameObject.GetComponent<SpriteComponent>()->GetState<PookaMoveState>();
	case NotifyEvent::EVENT_COLLISION:

		if (npc->IsHit())
			return gameObject.GetComponent<SpriteComponent>()->GetState<PookaInflateState>();

		return gameObject.GetComponent<SpriteComponent>()->GetState<PookaCrushState>();
	case NotifyEvent::EVENT_SPAWN:
		return gameObject.GetComponent<SpriteComponent>()->GetState<PookaIdleState>();
	case NotifyEvent::EVENT_ACTION:
		return gameObject.GetComponent<SpriteComponent>()->GetState<PookaCrushState>();
	default:;
	}
	return nullptr;
}

std::shared_ptr<dae::BaseState> dae::PookaGhostState::Swap(NotifyEvent event, GameObject& gameObject)
{
	const auto index = gameObject.GetTransform()->GetPositionIndex();
	const auto tile = m_pLevelManager->GetTile(index.x, index.y);
	const auto move = gameObject.GetComponent<MoveComponent>();
	const auto npc = gameObject.GetComponent<NpcComponent>();
	switch (event)
	{
	case NotifyEvent::EVENT_IDLE:
		if (tile->GetTileState() == TileState::FREE)
			return gameObject.GetComponent<SpriteComponent>()->GetState<PookaGhostState>();

		return gameObject.GetComponent<SpriteComponent>()->GetState<PookaIdleState>();
	case NotifyEvent::EVENT_MOVE:
		if (move->CheckTileSwapping() && move->IsCentered())
			return gameObject.GetComponent<SpriteComponent>()->GetState<PookaIdleState>();

		if (gameObject.GetComponent<NpcComponent>()->IsGhosting() || tile->GetTileState() == TileState::FREE)
			return nullptr;

		return gameObject.GetComponent<SpriteComponent>()->GetState<PookaMoveState>();
	case NotifyEvent::EVENT_COLLISION:
		return nullptr;
	case NotifyEvent::EVENT_SPAWN:
		return gameObject.GetComponent<SpriteComponent>()->GetState<PookaIdleState>();
	default:;
	}
	return nullptr;
}

std::shared_ptr<dae::BaseState> dae::PookaInflateState::Swap(NotifyEvent event, GameObject& gameObject)
{
	const auto npc = gameObject.GetComponent<NpcComponent>();
	const auto sprite = gameObject.GetComponent<SpriteComponent>();
	gameObject.GetCollision()->EnableCollision(false);
	switch (event)
	{
	case NotifyEvent::EVENT_IDLE:
		sprite->SetActiveAnimationFrame(sprite->GetActiveAnimationFrame());
		return gameObject.GetComponent<SpriteComponent>()->GetState<PookaDeflateState>();
	case NotifyEvent::EVENT_COLLISION:
		if(sprite->IsAnimationEnded())
		{
			npc->Dead();
			return gameObject.GetComponent<SpriteComponent>()->GetState<PookaDeadState>();

		}


		if (npc->IsHit())
			return nullptr;

		return gameObject.GetComponent<SpriteComponent>()->GetState<PookaCrushState>();
	case NotifyEvent::EVENT_SPAWN:
		return gameObject.GetComponent<SpriteComponent>()->GetState<PookaIdleState>();
	case NotifyEvent::EVENT_ACTION:
		return gameObject.GetComponent<SpriteComponent>()->GetState<PookaCrushState>();
	default:;
	}
	return nullptr;
}

std::shared_ptr<dae::BaseState> dae::PookaDeflateState::Swap(NotifyEvent event, GameObject& gameObject)
{
	const auto move = gameObject.GetComponent<MoveComponent>();
	const auto npc = gameObject.GetComponent<NpcComponent>();
	const auto sprite = gameObject.GetComponent<SpriteComponent>();
	gameObject.GetCollision()->EnableCollision(true);
	switch (event)
	{
	case NotifyEvent::EVENT_IDLE:
		if (sprite->IsAnimationEnded())
			return gameObject.GetComponent<SpriteComponent>()->GetState<PookaIdleState>();

		return nullptr;
	
	case NotifyEvent::EVENT_COLLISION:

		if (npc->IsHit())
			return gameObject.GetComponent<SpriteComponent>()->GetState<PookaInflateState>();

		return gameObject.GetComponent<SpriteComponent>()->GetState<PookaCrushState>();
	case NotifyEvent::EVENT_SPAWN:
		return gameObject.GetComponent<SpriteComponent>()->GetState<PookaIdleState>();
	case NotifyEvent::EVENT_ACTION:
		return gameObject.GetComponent<SpriteComponent>()->GetState<PookaCrushState>();
	default:;
	}
	return nullptr;
}

std::shared_ptr<dae::BaseState> dae::PookaCrushState::Swap(NotifyEvent event, GameObject& gameObject)
{
	const auto move = gameObject.GetComponent<MoveComponent>();
	const auto npc = gameObject.GetComponent<NpcComponent>();
	gameObject.GetCollision()->EnableCollision(false);

	const auto trans = gameObject.GetTransform();
	const iVector2 nextTileIndex = { trans->GetPositionIndex().x , trans->GetPositionIndex().y + 1 };
	const auto nextTile = m_pLevelManager->GetTile(nextTileIndex.x, nextTileIndex.y);

	switch (event)
	{
	case NotifyEvent::EVENT_SPAWN:
		m_IsCrushed = false;
		m_DelayTimer = 0.f;
		return gameObject.GetComponent<SpriteComponent>()->GetState<PookaIdleState>();
	case NotifyEvent::EVENT_ACTION:
		if (nextTile->GetTileState() != TileState::USED && gameObject.GetComponent<MoveComponent>()->IsCentered())
		{
			gameObject.GetComponent<MoveComponent>()->SetMovementInput({ 0, 0, 0 });
			m_IsCrushed = true;
			if (m_DelayTimer >= m_DelayMaxTime)
				return gameObject.GetComponent<SpriteComponent>()->GetState<PookaDeadState>();
		}
		return nullptr;
	default:;
	}
	return nullptr;
}

void dae::PookaCrushState::Update(float& deltaTime, GameObject& )
{
	if (m_IsCrushed)
		m_DelayTimer += deltaTime;
}

std::shared_ptr<dae::BaseState> dae::PookaDeadState::Swap(NotifyEvent event, GameObject& gameObject)
{
	gameObject.Enable(false);
	if(event == NotifyEvent::EVENT_SPAWN)
	{
		gameObject.Enable(true);
		return gameObject.GetComponent<SpriteComponent>()->GetState<PookaIdleState>();
	}

	return nullptr;
}


//FYGAR STATES
//************
std::shared_ptr<dae::BaseState> dae::FygarIdleState::Swap(NotifyEvent event, GameObject& gameObject)
{
	const auto index = gameObject.GetTransform()->GetPositionIndex();
	const auto tile = m_pLevelManager->GetTile(index.x, index.y);
	const auto move = gameObject.GetComponent<MoveComponent>();
	const auto npc = gameObject.GetComponent<NpcComponent>();
	switch (event)
	{
	case NotifyEvent::EVENT_IDLE:
		if (tile->GetTileState() == TileState::FREE)
			return gameObject.GetComponent<SpriteComponent>()->GetState<FygarGhostState>();

		return nullptr;
	case NotifyEvent::EVENT_MOVE:
		if (move->CheckTileSwapping() && move->IsCentered())
			return nullptr;

		if (gameObject.GetComponent<NpcComponent>()->IsGhosting() || tile->GetTileState() == TileState::FREE)
			return gameObject.GetComponent<SpriteComponent>()->GetState<FygarGhostState>();

		return gameObject.GetComponent<SpriteComponent>()->GetState<FygarMoveState>();
	case NotifyEvent::EVENT_COLLISION:

		if (npc->IsHit())
			return gameObject.GetComponent<SpriteComponent>()->GetState<FygarInflateState>();

		return gameObject.GetComponent<SpriteComponent>()->GetState<FygarCrushState>();
	case NotifyEvent::EVENT_ACTION:
		if (tile->GetTileState() != TileState::FREE)
			return gameObject.GetComponent<SpriteComponent>()->GetState<FygarAttackState>();
		return nullptr;
	case NotifyEvent::EVENT_SPAWN:
		return nullptr;
	default:;
	}
	return nullptr;
}

std::shared_ptr<dae::BaseState> dae::FygarMoveState::Swap(NotifyEvent event, GameObject& gameObject)
{
	const auto index = gameObject.GetTransform()->GetPositionIndex();
	const auto tile = m_pLevelManager->GetTile(index.x, index.y);
	const auto move = gameObject.GetComponent<MoveComponent>();
	const auto npc = gameObject.GetComponent<NpcComponent>();
	switch (event)
	{
	case NotifyEvent::EVENT_IDLE:
		if (tile->GetTileState() == TileState::FREE)
			return gameObject.GetComponent<SpriteComponent>()->GetState<FygarGhostState>();

		return gameObject.GetComponent<SpriteComponent>()->GetState<FygarIdleState>();
	case NotifyEvent::EVENT_MOVE:
		if (move->CheckTileSwapping() && move->IsCentered())
			return gameObject.GetComponent<SpriteComponent>()->GetState<FygarIdleState>();

		if (gameObject.GetComponent<NpcComponent>()->IsGhosting() || tile->GetTileState() == TileState::FREE)
			return gameObject.GetComponent<SpriteComponent>()->GetState<FygarGhostState>();

		return gameObject.GetComponent<SpriteComponent>()->GetState<FygarMoveState>();
	case NotifyEvent::EVENT_COLLISION:

		if (npc->IsHit())
			return gameObject.GetComponent<SpriteComponent>()->GetState<FygarInflateState>();

		return gameObject.GetComponent<SpriteComponent>()->GetState<FygarCrushState>();
	case NotifyEvent::EVENT_ACTION:
		if (tile->GetTileState() != TileState::FREE)
			return gameObject.GetComponent<SpriteComponent>()->GetState<FygarAttackState>();
		return nullptr;
	case NotifyEvent::EVENT_SPAWN:
		return gameObject.GetComponent<SpriteComponent>()->GetState<FygarIdleState>();
	default:;
	}
	return nullptr;
}

std::shared_ptr<dae::BaseState> dae::FygarChaseState::Swap(NotifyEvent event, GameObject& gameObject)
{
	const auto index = gameObject.GetTransform()->GetPositionIndex();
	const auto tile = m_pLevelManager->GetTile(index.x, index.y);
	const auto move = gameObject.GetComponent<MoveComponent>();
	const auto npc = gameObject.GetComponent<NpcComponent>();
	switch (event)
	{
	case NotifyEvent::EVENT_IDLE:
		if (tile->GetTileState() == TileState::FREE)
			return gameObject.GetComponent<SpriteComponent>()->GetState<FygarGhostState>();

		return gameObject.GetComponent<SpriteComponent>()->GetState<FygarIdleState>();
	case NotifyEvent::EVENT_MOVE:
		if (move->CheckTileSwapping() && move->IsCentered())
			return gameObject.GetComponent<SpriteComponent>()->GetState<FygarIdleState>();

		if (gameObject.GetComponent<NpcComponent>()->IsGhosting() || tile->GetTileState() == TileState::FREE)
			return gameObject.GetComponent<SpriteComponent>()->GetState<FygarGhostState>();

		return gameObject.GetComponent<SpriteComponent>()->GetState<FygarMoveState>();
	case NotifyEvent::EVENT_COLLISION:

		if (npc->IsHit())
			return gameObject.GetComponent<SpriteComponent>()->GetState<FygarInflateState>();

		return gameObject.GetComponent<SpriteComponent>()->GetState<FygarCrushState>();
	case NotifyEvent::EVENT_ACTION:
		if (tile->GetTileState() != TileState::FREE)
			return gameObject.GetComponent<SpriteComponent>()->GetState<FygarAttackState>();
		return nullptr;
	case NotifyEvent::EVENT_SPAWN:
		return gameObject.GetComponent<SpriteComponent>()->GetState<FygarIdleState>();
	default:;
	}
	return nullptr;
}

std::shared_ptr<dae::BaseState> dae::FygarGhostState::Swap(NotifyEvent event, GameObject& gameObject)
{
	const auto index = gameObject.GetTransform()->GetPositionIndex();
	const auto tile = m_pLevelManager->GetTile(index.x, index.y);
	const auto move = gameObject.GetComponent<MoveComponent>();
	const auto npc = gameObject.GetComponent<NpcComponent>();
	switch (event)
	{
	case NotifyEvent::EVENT_IDLE:
		if (tile->GetTileState() == TileState::FREE)
			return gameObject.GetComponent<SpriteComponent>()->GetState<FygarGhostState>();

		return gameObject.GetComponent<SpriteComponent>()->GetState<FygarIdleState>();
	case NotifyEvent::EVENT_MOVE:
		if (move->CheckTileSwapping() && move->IsCentered())
			return gameObject.GetComponent<SpriteComponent>()->GetState<FygarIdleState>();

		if (gameObject.GetComponent<NpcComponent>()->IsGhosting() || tile->GetTileState() == TileState::FREE)
			return nullptr;

		return gameObject.GetComponent<SpriteComponent>()->GetState<FygarMoveState>();
	case NotifyEvent::EVENT_COLLISION:
		return nullptr;
	case NotifyEvent::EVENT_SPAWN:
		return gameObject.GetComponent<SpriteComponent>()->GetState<FygarIdleState>();
	default:;
	}
	return nullptr;
}

std::shared_ptr<dae::BaseState> dae::FygarChargingState::Swap(NotifyEvent event, GameObject& gameObject)
{
	const auto index = gameObject.GetTransform()->GetPositionIndex();
	const auto tile = m_pLevelManager->GetTile(index.x, index.y);
	const auto move = gameObject.GetComponent<MoveComponent>();
	const auto npc = gameObject.GetComponent<NpcComponent>();
	switch (event)
	{
	case NotifyEvent::EVENT_IDLE:
		if (tile->GetTileState() == TileState::FREE)
			return gameObject.GetComponent<SpriteComponent>()->GetState<FygarGhostState>();

		return gameObject.GetComponent<SpriteComponent>()->GetState<FygarIdleState>();
	case NotifyEvent::EVENT_MOVE:
		if (move->CheckTileSwapping() && move->IsCentered())
			return gameObject.GetComponent<SpriteComponent>()->GetState<FygarIdleState>();

		if (gameObject.GetComponent<NpcComponent>()->IsGhosting() || tile->GetTileState() == TileState::FREE)
			return nullptr;
		if(npc->IsAttacking())
			return gameObject.GetComponent<SpriteComponent>()->GetState<FygarMoveState>();
		return nullptr;
	case NotifyEvent::EVENT_ACTION:

		return gameObject.GetComponent<SpriteComponent>()->GetState<FygarAttackState>();
	case NotifyEvent::EVENT_SPAWN:
		return gameObject.GetComponent<SpriteComponent>()->GetState<FygarIdleState>();
	default:;
	}
	return nullptr;
}

std::shared_ptr<dae::BaseState> dae::FygarAttackState::Swap(NotifyEvent event, GameObject& gameObject)
{
	const auto index = gameObject.GetTransform()->GetPositionIndex();
	const auto tile = m_pLevelManager->GetTile(index.x, index.y);
	const auto move = gameObject.GetComponent<MoveComponent>();
	const auto npc = gameObject.GetComponent<NpcComponent>();
	switch (event)
	{
	case NotifyEvent::EVENT_IDLE:
		if (tile->GetTileState() == TileState::FREE)
			return gameObject.GetComponent<SpriteComponent>()->GetState<FygarGhostState>();

		return gameObject.GetComponent<SpriteComponent>()->GetState<FygarIdleState>();
	case NotifyEvent::EVENT_MOVE:
		if (move->CheckTileSwapping() && move->IsCentered())
			return gameObject.GetComponent<SpriteComponent>()->GetState<PookaIdleState>();

		if (gameObject.GetComponent<NpcComponent>()->IsGhosting() || tile->GetTileState() == TileState::FREE)
			return nullptr;

		return gameObject.GetComponent<SpriteComponent>()->GetState<FygarMoveState>();
	case NotifyEvent::EVENT_ACTION:
		return nullptr;
	case NotifyEvent::EVENT_SPAWN:
		return gameObject.GetComponent<SpriteComponent>()->GetState<FygarIdleState>();
	default:;
	}
	return nullptr;
}

std::shared_ptr<dae::BaseState> dae::FygarInflateState::Swap(NotifyEvent event, GameObject& gameObject)
{
	const auto npc = gameObject.GetComponent<NpcComponent>();
	const auto sprite = gameObject.GetComponent<SpriteComponent>();
	gameObject.GetCollision()->EnableCollision(false);
	switch (event)
	{
	case NotifyEvent::EVENT_IDLE:
		sprite->SetActiveAnimationFrame(sprite->GetActiveAnimationFrame());
		return gameObject.GetComponent<SpriteComponent>()->GetState<FygarDeflateState>();
	case NotifyEvent::EVENT_COLLISION:
		if (sprite->IsAnimationEnded())
		{
			npc->Dead();
			return gameObject.GetComponent<SpriteComponent>()->GetState<FygarDeadState>();

		}


		if (npc->IsHit())
			return nullptr;

		return gameObject.GetComponent<SpriteComponent>()->GetState<FygarCrushState>();
	case NotifyEvent::EVENT_SPAWN:
		return gameObject.GetComponent<SpriteComponent>()->GetState<FygarIdleState>();
	default:;
	}
	return nullptr;
}

std::shared_ptr<dae::BaseState> dae::FygarDeflateState::Swap(NotifyEvent event, GameObject& gameObject)
{
	const auto move = gameObject.GetComponent<MoveComponent>();
	const auto npc = gameObject.GetComponent<NpcComponent>();
	const auto sprite = gameObject.GetComponent<SpriteComponent>();
	gameObject.GetCollision()->EnableCollision(true);
	switch (event)
	{
	case NotifyEvent::EVENT_IDLE:
		if (sprite->IsAnimationEnded())
			return gameObject.GetComponent<SpriteComponent>()->GetState<FygarIdleState>();

		return nullptr;

	case NotifyEvent::EVENT_COLLISION:

		if (npc->IsHit())
			return gameObject.GetComponent<SpriteComponent>()->GetState<FygarInflateState>();

		return gameObject.GetComponent<SpriteComponent>()->GetState<FygarCrushState>();
	case NotifyEvent::EVENT_SPAWN:
		return gameObject.GetComponent<SpriteComponent>()->GetState<FygarIdleState>();
	default:;
	}
	return nullptr;
}

std::shared_ptr<dae::BaseState> dae::FygarCrushState::Swap(NotifyEvent event, GameObject& gameObject)
{
	const auto move = gameObject.GetComponent<MoveComponent>();
	const auto npc = gameObject.GetComponent<NpcComponent>();
	gameObject.GetCollision()->EnableCollision(false);

	const auto trans = gameObject.GetTransform();
	const iVector2 nextTileIndex = { trans->GetPositionIndex().x , trans->GetPositionIndex().y + 1 };
	const auto nextTile = m_pLevelManager->GetTile(nextTileIndex.x, nextTileIndex.y);

	switch (event)
	{
	case NotifyEvent::EVENT_SPAWN:
		m_IsCrushed = false;
		m_DelayTimer = 0.f;
		return gameObject.GetComponent<SpriteComponent>()->GetState<PookaIdleState>();
	case NotifyEvent::EVENT_ACTION:
		if (nextTile->GetTileState() != TileState::USED && gameObject.GetComponent<MoveComponent>()->IsCentered())
		{
			gameObject.GetComponent<MoveComponent>()->SetMovementInput({ 0, 0, 0 });
			m_IsCrushed = true;
			if (m_DelayTimer >= m_DelayMaxTime)
				return gameObject.GetComponent<SpriteComponent>()->GetState<FygarDeadState>();
		}
		return nullptr;
	default:;
	}
	return nullptr;
}

void dae::FygarCrushState::Update(float& deltaTime, GameObject& )
{
	if (m_IsCrushed)
		m_DelayTimer += deltaTime;

}

std::shared_ptr<dae::BaseState> dae::FygarDeadState::Swap(NotifyEvent event, GameObject& gameObject)
{
	gameObject.Enable(false);
	if (event == NotifyEvent::EVENT_SPAWN)
	{
		gameObject.Enable(true);
		return gameObject.GetComponent<SpriteComponent>()->GetState<FygarIdleState>();
	}

	return nullptr;
}

std::shared_ptr<dae::BaseState> dae::RockIdleState::Swap(NotifyEvent , GameObject& gameObject)
{
	gameObject.GetComponent<MoveComponent>()->SetMovementInput({ 0, 1, 0 });
	const auto trans = gameObject.GetTransform();
	const iVector2 nextTileIndex = { trans->GetPositionIndex().x , trans->GetPositionIndex().y + 1 };
	const auto nextTile = m_pLevelManager->GetTile(nextTileIndex.x, nextTileIndex.y);

	if (nextTile->GetTileState() == TileState::USED)
	{
		gameObject.GetComponent<NpcComponent>()->Hit(nextTile->GetTileOwner());
		return gameObject.GetComponent<SpriteComponent>()->GetState<RockLoseState>();
	}
		

	return nullptr;
}

std::shared_ptr<dae::BaseState> dae::RockFallingState::Swap(NotifyEvent event, GameObject& gameObject)
{
	if (event == NotifyEvent::EVENT_SPAWN)
	{
		gameObject.GetComponent<MoveComponent>()->SetIsStatic(true);
		return gameObject.GetComponent<SpriteComponent>()->GetState<RockIdleState>();
	}

	const auto trans = gameObject.GetTransform();
	const iVector2 nextTileIndex = { trans->GetPositionIndex().x , trans->GetPositionIndex().y + 1 };
	const auto nextTile = m_pLevelManager->GetTile(nextTileIndex.x, nextTileIndex.y);
	

	if (nextTile->GetTileState() != TileState::USED && gameObject.GetComponent<MoveComponent>()->IsCentered())
	{
		gameObject.GetComponent<MoveComponent>()->SetMovementInput({ 0, 0, 0 });
		gameObject.GetComponent<NpcComponent>()->Dead();
		return gameObject.GetComponent<SpriteComponent>()->GetState<RockDeadState>();
	}

	return nullptr;
}

void dae::RockFallingState::Update(float& , GameObject& gameObject)
{
	const auto collision = gameObject.GetComponent<CollisionComponent>();
	if (collision->GetHasCollision())
	{
		if (collision->GetCollision()->GetGameObject()->GetComponent<NpcComponent>())
		{
			//HIT NPC
			if (!collision->GetCollision()->GetGameObject()->GetComponent<NpcComponent>()->IsCrushed())
			{
					collision->GetGameObject()->GetComponent<NpcComponent>()->HasHit();
					collision->GetCollision()->GetGameObject()->GetComponent<NpcComponent>()->Hit(collision->GetCollision()->GetGameObject()->GetComponent<NpcComponent>()->HitByPlayer());
					collision->GetCollision()->GetGameObject()->GetComponent<NpcComponent>()->EnableCrushing();
					collision->GetCollision()->GetGameObject()->GetComponent<SpriteComponent>()->onNotify(NotifyEvent::EVENT_ACTION);
			}
			//collision->SetHasCollision(false);
		}
	}
}

std::shared_ptr<dae::BaseState> dae::RockLoseState::Swap(NotifyEvent event, GameObject& gameObject)
{
	if (event == NotifyEvent::EVENT_SPAWN)
	{
		gameObject.GetComponent<MoveComponent>()->SetIsStatic(true);
		return gameObject.GetComponent<SpriteComponent>()->GetState<RockIdleState>();
	}

	const auto trans = gameObject.GetTransform();
	const iVector2 nextTileIndex = { trans->GetPositionIndex().x , trans->GetPositionIndex().y + 1 };
	const auto nextTile = m_pLevelManager->GetTile(nextTileIndex.x, nextTileIndex.y);
	const auto currtile = m_pLevelManager->GetTile(trans->GetPositionIndex().x, trans->GetPositionIndex().y);

	if (nextTile->GetTileState() == TileState::USED && !nextTile->IsOccupied())
	{
		if(m_IsFree)
		{
			if (m_DelayTimer >= m_DelayMaxTime)
			{
				m_IsFree = false;
				m_DelayTimer = 0.f;
				gameObject.GetComponent<MoveComponent>()->SetIsStatic(false);
				
				const auto dig = currtile->HasBeenUsed();

				currtile->SetTileState(dig ? TileState::USED : TileState::FREE);

				if(dig)
					m_pLevelManager->DigConnection(currtile, nextTile, Direction::DOWN);

				return gameObject.GetComponent<SpriteComponent>()->GetState<RockFallingState>();
			}			
		}
		else
		{
			m_IsFree = true;
		}
		
	}

	return nullptr;
}

void dae::RockLoseState::Update(float& deltaTime, GameObject& )
{
	if(m_IsFree)
	{
		m_DelayTimer += deltaTime;
	}
}

std::shared_ptr<dae::BaseState> dae::RockDeadState::Swap(NotifyEvent event, GameObject& gameObject)
{
	if(gameObject.GetComponent<SpriteComponent>()->IsAnimationEnded())
		gameObject.Enable(false);
	
	if (event == NotifyEvent::EVENT_SPAWN)
	{
		gameObject.Enable(true);
		gameObject.GetComponent<MoveComponent>()->SetIsStatic(true);
		return gameObject.GetComponent<SpriteComponent>()->GetState<RockIdleState>();
	}

	return nullptr;
}