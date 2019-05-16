#include "MiniginPCH.h"
#include "States.h"
#include "GameObject.h"
#include "ServiceLocator.h"

std::shared_ptr<dae::BaseState> dae::DirectionState::Swap(NotifyEvent event, GameObject& gameObject)
{
	UNREFERENCED_PARAMETER(event);
	UNREFERENCED_PARAMETER(gameObject);
	return nullptr;
}

void dae::DirectionState::Update(float& deltaTime, GameObject& gameObject)
{
	UNREFERENCED_PARAMETER(deltaTime);
	UNREFERENCED_PARAMETER(gameObject);
}

void dae::DirectionState::Animated(GameObject& gameObject)
{
	SpriteFlip(gameObject);
	//const auto gameObject.GetTransform();
	if (gameObject.GetTransform())
		switch (gameObject.GetComponent<MoveComponent>()->GetCurrentDirection())
		{
		case Direction::RIGHT:
			if (gameObject.GetSprite())
			{
				gameObject.GetSprite()->SetCurrentUV((m_Clip.Size.x * (gameObject.GetSprite()->GetActiveAnimationFrame()) + (m_Clip.UV.x)), m_Clip.UV.y, m_Clip.Size.x, m_Clip.Size.y);
			}
			break;
		case Direction::LEFT:
			if (gameObject.GetSprite())
			{
				gameObject.GetSprite()->SetCurrentUV((m_Clip.Size.x * gameObject.GetSprite()->GetActiveAnimationFrame()) + (m_Clip.UV.x + (gameObject.GetSprite()->GetCurrentUV().w * m_Clip.frames)), m_Clip.UV.y, m_Clip.Size.x, m_Clip.Size.y);
			}
			break;
		case Direction::UP:
			if (gameObject.GetSprite())
			{
				gameObject.GetSprite()->SetCurrentUV((m_Clip.Size.x * (gameObject.GetSprite()->GetActiveAnimationFrame()) + (m_Clip.UV.x)), m_Clip.UV.y, m_Clip.Size.x, m_Clip.Size.y);
			}
			if (gameObject.GetSprite() && m_Clip.hasUpDown)
			{
				if (m_Clip.hasUpDown)
				{
					if (gameObject.GetSprite()->GetFlipSprite())
						gameObject.GetSprite()->SetCurrentUV((gameObject.GetTexture()->GetSize().x - gameObject.GetSprite()->GetCurrentUV().w) - ((gameObject.GetSprite()->GetCurrentUV().w * gameObject.GetSprite()->GetActiveAnimationFrame()) + (m_Clip.UV.x + (gameObject.GetSprite()->GetCurrentUV().w * m_Clip.frames * 2))), m_Clip.UV.y, m_Clip.Size.x, m_Clip.Size.y);
					else
						gameObject.GetSprite()->SetCurrentUV((gameObject.GetSprite()->GetCurrentUV().w * gameObject.GetSprite()->GetActiveAnimationFrame()) + (m_Clip.UV.x + (gameObject.GetSprite()->GetCurrentUV().w * m_Clip.frames * 2)), m_Clip.UV.y, m_Clip.Size.x, m_Clip.Size.y);
				}
				else
				{
					if (gameObject.GetComponent<MoveComponent>()->GetPreviousDirection() == Direction::RIGHT || gameObject.GetComponent<MoveComponent>()->GetPreviousDirection() == Direction::LEFT)
						m_LastHorDir = gameObject.GetComponent<MoveComponent>()->GetPreviousDirection();

					if (m_LastHorDir == Direction::RIGHT)
						gameObject.GetSprite()->SetCurrentUV((m_Clip.Size.x * (gameObject.GetSprite()->GetActiveAnimationFrame()) + (m_Clip.UV.x)), m_Clip.UV.y, m_Clip.Size.x, m_Clip.Size.y);
					if (m_LastHorDir == Direction::LEFT)
						gameObject.GetSprite()->SetCurrentUV((m_Clip.Size.x * gameObject.GetSprite()->GetActiveAnimationFrame()) + (m_Clip.UV.x + (gameObject.GetSprite()->GetCurrentUV().w * m_Clip.frames)), m_Clip.UV.y, m_Clip.Size.x, m_Clip.Size.y);
				}
			}
			break;
			
		case Direction::DOWN:

			if (gameObject.GetSprite())
			{
				if(m_Clip.hasUpDown)
				{
					if (gameObject.GetSprite()->GetFlipSprite())
						gameObject.GetSprite()->SetCurrentUV((gameObject.GetTexture()->GetSize().x - gameObject.GetSprite()->GetCurrentUV().w) - ((gameObject.GetSprite()->GetCurrentUV().w * gameObject.GetSprite()->GetActiveAnimationFrame()) + (m_Clip.UV.x + (gameObject.GetSprite()->GetCurrentUV().w * m_Clip.frames * 3))), m_Clip.UV.y, m_Clip.Size.x, m_Clip.Size.y);
					else
						gameObject.GetSprite()->SetCurrentUV((gameObject.GetSprite()->GetCurrentUV().w * gameObject.GetSprite()->GetActiveAnimationFrame()) + (m_Clip.UV.x + (gameObject.GetSprite()->GetCurrentUV().w * m_Clip.frames * 3)), m_Clip.UV.y, m_Clip.Size.x, m_Clip.Size.y);
				}
				else
				{
					if (gameObject.GetComponent<MoveComponent>()->GetPreviousDirection() == Direction::RIGHT || gameObject.GetComponent<MoveComponent>()->GetPreviousDirection() == Direction::LEFT)
						m_LastHorDir = gameObject.GetComponent<MoveComponent>()->GetPreviousDirection();

					if (m_LastHorDir == Direction::RIGHT)
						gameObject.GetSprite()->SetCurrentUV((m_Clip.Size.x * (gameObject.GetSprite()->GetActiveAnimationFrame()) + (m_Clip.UV.x)), m_Clip.UV.y, m_Clip.Size.x, m_Clip.Size.y);
					if (m_LastHorDir == Direction::LEFT)
						gameObject.GetSprite()->SetCurrentUV((m_Clip.Size.x * gameObject.GetSprite()->GetActiveAnimationFrame()) + (m_Clip.UV.x + (gameObject.GetSprite()->GetCurrentUV().w * m_Clip.frames)), m_Clip.UV.y, m_Clip.Size.x, m_Clip.Size.y);
				}
			}
			break;
		default:
			;
		}
	/*if(m_Clip.TextureList.size() > 0)
	{	
		auto resource = ServiceLocator::GetResourceManager();	
		SpriteFlip(gameObject);


		if (gameObject.GetTransform())
			switch (gameObject.GetTransform()->GetCurrentDirection())
			{
			case Direction::UP:
				if (gameObject.GetTexture() && gameObject.GetSprite() && m_Clip.hasUpDown)
				{
					for(UINT frame = 0; frame < m_Clip.TextureList.at(static_cast<UINT>(Direction::UP)).size(); frame++)
					{
						if(gameObject.GetSprite()->GetActiveAnimationFrame() == frame)
							gameObject.GetTexture()->SetTexture(resource->GetTexture(m_Clip.TextureList.at(static_cast<UINT>(Direction::UP)).at(frame)));
					}
				}
				break;
			case Direction::DOWN:
				if (gameObject.GetTexture() && gameObject.GetSprite() && m_Clip.hasUpDown)
				{
					for (UINT frame = 0; frame < m_Clip.TextureList.at(static_cast<UINT>(Direction::DOWN)).size(); frame++)
					{
						if (gameObject.GetSprite()->GetActiveAnimationFrame() == frame)
							gameObject.GetTexture()->SetTexture(resource->GetTexture(m_Clip.TextureList.at(static_cast<UINT>(Direction::DOWN)).at(frame)));
					}
				}
				break;
			case Direction::LEFT:
				if (gameObject.GetTexture() && gameObject.GetSprite())
				{
					for (UINT frame = 0; frame < m_Clip.TextureList.at(static_cast<UINT>(Direction::LEFT)).size(); frame++)
					{
						if (gameObject.GetSprite()->GetActiveAnimationFrame() == frame)
							gameObject.GetTexture()->SetTexture(resource->GetTexture(m_Clip.TextureList.at(static_cast<UINT>(Direction::LEFT)).at(frame)));
					}
				}
				break;
			case Direction::RIGHT:
				if (gameObject.GetTexture() && gameObject.GetSprite())
				{
					for (UINT frame = 0; frame < m_Clip.TextureList.at(static_cast<UINT>(Direction::RIGHT)).size(); frame++)
					{
						if (gameObject.GetSprite()->GetActiveAnimationFrame() == frame)
							gameObject.GetTexture()->SetTexture(resource->GetTexture(m_Clip.TextureList.at(static_cast<UINT>(Direction::RIGHT)).at(frame)));
					}
				}
				break;
			default:
				;
			}
	}*/
}

void dae::DirectionState::SpriteFlip(GameObject & gameObject) const
{
	if (gameObject.GetTransform())
		switch (gameObject.GetComponent<MoveComponent>()->GetCurrentDirection())
		{
		default:;
		case Direction::UP:
			if (gameObject.GetSprite() && m_Clip.hasUpDown)
			{
				if (gameObject.GetComponent<MoveComponent>()->GetPreviousDirection() == Direction::RIGHT)
					gameObject.GetSprite()->SetFlipSprite(SDL_FLIP_NONE);
				if (gameObject.GetComponent<MoveComponent>()->GetPreviousDirection() == Direction::LEFT)
					gameObject.GetSprite()->SetFlipSprite(SDL_FLIP_HORIZONTAL);
			}
			break;
		case Direction::DOWN:
			if (gameObject.GetSprite() && m_Clip.hasUpDown)
			{
				if (gameObject.GetComponent<MoveComponent>()->GetPreviousDirection() == Direction::RIGHT)
					gameObject.GetSprite()->SetFlipSprite(SDL_FLIP_HORIZONTAL);
				if (gameObject.GetComponent<MoveComponent>()->GetPreviousDirection() == Direction::LEFT)
					gameObject.GetSprite()->SetFlipSprite(SDL_FLIP_NONE);
			}
			break;
		case Direction::LEFT:
			if (gameObject.GetSprite())
				gameObject.GetSprite()->SetFlipSprite(SDL_FLIP_NONE);
			break;
		case Direction::RIGHT:
			if (gameObject.GetSprite())
				gameObject.GetSprite()->SetFlipSprite(SDL_FLIP_NONE);
			break;
		case Direction::NONE:
			if (gameObject.GetSprite())
				gameObject.GetSprite()->SetFlipSprite(SDL_FLIP_NONE);
			break;
		}
}

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
			return std::make_shared<DigPlayerState>();
		
			return std::make_shared<MovePlayerState>();
	case NotifyEvent::EVENT_ACTION:
		return std::make_shared<AttackPlayerState>();
	case NotifyEvent::EVENT_COLLISION:
		return std::make_shared<DeadPlayerState>();
	case NotifyEvent::EVENT_SPAWN:
		gameObject.GetComponent<MoveComponent>()->SetIsStatic(false);
		return nullptr;
	default: ;
	}

	return nullptr;
}

std::shared_ptr<dae::BaseState> dae::MovePlayerState::Swap(NotifyEvent event, GameObject& gameObject)
{
	switch (event)
	{
	case NotifyEvent::EVENT_IDLE:
		return std::make_shared<IdlePlayerState>();
	case NotifyEvent::EVENT_MOVE:
		if (!gameObject.GetComponent<MoveComponent>()->CheckOccupiedTileMove())
			return std::make_shared<IdlePlayerState>();

		if (gameObject.GetComponent<MoveComponent>()->CheckTileSwapping())
			return std::make_shared<DigPlayerState>();

		return nullptr;
	case NotifyEvent::EVENT_ACTION:
		return std::make_shared<AttackPlayerState>();
	case NotifyEvent::EVENT_COLLISION:
		return std::make_shared<DeadPlayerState>();
	default:;
	}

	return nullptr;
}

std::shared_ptr<dae::BaseState> dae::DigPlayerState::Swap(NotifyEvent event, GameObject& gameObject)
{	
	switch (event)
	{
	case NotifyEvent::EVENT_IDLE:
		return std::make_shared<IdlePlayerState>();
	case NotifyEvent::EVENT_MOVE:
		if (!gameObject.GetComponent<MoveComponent>()->CheckOccupiedTileMove())
			return std::make_shared<IdlePlayerState>();

		if (!gameObject.GetComponent<MoveComponent>()->CheckTileSwapping())
			return std::make_shared<MovePlayerState>();

		return nullptr;
	case NotifyEvent::EVENT_ACTION:
		return std::make_shared<AttackPlayerState>();
	case NotifyEvent::EVENT_COLLISION:
		return std::make_shared<DeadPlayerState>();
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
		return std::make_shared<IdlePlayerState>();
	case NotifyEvent::EVENT_MOVE:
		return std::make_shared<IdlePlayerState>();
	case NotifyEvent::EVENT_ACTION:
		return nullptr;
	case NotifyEvent::EVENT_COLLISION:
		return std::make_shared<DeadPlayerState>();
	case NotifyEvent::EVENT_INTERACT:
		return std::make_shared<PumpPlayerState>();
	default:;
	}

	return nullptr;
}

std::shared_ptr<dae::BaseState> dae::PumpPlayerState::Swap(NotifyEvent event, GameObject& gameObject)
{
	UNREFERENCED_PARAMETER(event);
	UNREFERENCED_PARAMETER(gameObject);
	switch (event)
	{
	case NotifyEvent::EVENT_IDLE:
		return std::make_shared<IdlePlayerState>();
	case NotifyEvent::EVENT_MOVE:
		return std::make_shared<MovePlayerState>();
	case NotifyEvent::EVENT_COLLISION:
		return std::make_shared<DeadPlayerState>();
	case NotifyEvent::EVENT_INTERACT:
		return nullptr;
	default:;
	}
	return nullptr;
}

std::shared_ptr<dae::BaseState> dae::DeadPlayerState::Swap(NotifyEvent event, GameObject& gameObject)
{
	UNREFERENCED_PARAMETER(gameObject);
	gameObject.GetComponent<MoveComponent>()->SetIsStatic(true);
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
		gameObject.GetComponent<MoveComponent>()->SetIsStatic(false);
		return std::make_shared<IdlePlayerState>();
	default:;
	}

	return nullptr;
}

std::shared_ptr<dae::BaseState> dae::WeaponState::Swap(NotifyEvent , GameObject& )
{
	return nullptr;
}
