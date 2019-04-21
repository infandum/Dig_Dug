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
	if(m_Clip.TextureList.size() > 0)
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
	}
}

void dae::DirectionState::SpriteFlip(GameObject & gameObject) const
{
	if (gameObject.GetTransform())
		switch (gameObject.GetTransform()->GetCurrentDirection())
		{
		default:;
		case Direction::UP:
			if (gameObject.GetSprite())
			{
				if (gameObject.GetTransform()->GetPreviousDirection() == Direction::RIGHT)
					gameObject.GetSprite()->SetFlipSprite(SDL_FLIP_NONE);
				if (gameObject.GetTransform()->GetPreviousDirection() == Direction::LEFT)
					gameObject.GetSprite()->SetFlipSprite(SDL_FLIP_HORIZONTAL);
			}
			break;
		case Direction::DOWN:
			if (gameObject.GetSprite())
			{
				if (gameObject.GetTransform()->GetPreviousDirection() == Direction::RIGHT)
					gameObject.GetSprite()->SetFlipSprite(SDL_FLIP_HORIZONTAL);
				if (gameObject.GetTransform()->GetPreviousDirection() == Direction::LEFT)
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

std::shared_ptr<dae::BaseState> dae::IdleState::Swap(NotifyEvent event, GameObject& gameObject)
{
	UNREFERENCED_PARAMETER(event);
	UNREFERENCED_PARAMETER(gameObject);
	switch (event)
	{
	case NotifyEvent::EVENT_IDLE:
		return nullptr;
	case NotifyEvent::EVENT_MOVE:
		if (gameObject.GetTransform()->isSwappingTile)
			return std::make_shared<DigState>();
		
			return std::make_shared<MoveState>();
	case NotifyEvent::EVENT_DIG:
		return std::make_shared<DigState>();
	case NotifyEvent::EVENT_ATTACK:
		return std::make_shared<AttackState>();
	default: ;
	}

	return nullptr;
}

std::shared_ptr<dae::BaseState> dae::MoveState::Swap(NotifyEvent event, GameObject& gameObject)
{
	UNREFERENCED_PARAMETER(event);
	UNREFERENCED_PARAMETER(gameObject);
	switch (event)
	{
	case NotifyEvent::EVENT_IDLE:
		return std::make_shared<IdleState>();
	case NotifyEvent::EVENT_MOVE:
		if (gameObject.GetTransform()->isSwappingTile)
			return std::make_shared<DigState>();

		return nullptr;
	case NotifyEvent::EVENT_DIG:
		return std::make_shared<DigState>();
	case NotifyEvent::EVENT_ATTACK:
		return std::make_shared<AttackState>();
	default:;
	}

	return nullptr;
}

std::shared_ptr<dae::BaseState> dae::DigState::Swap(NotifyEvent event, GameObject& gameObject)
{	
	UNREFERENCED_PARAMETER(event);
	UNREFERENCED_PARAMETER(gameObject);
	switch (event)
	{
	case NotifyEvent::EVENT_IDLE:
		return std::make_shared<IdleState>();
	case NotifyEvent::EVENT_MOVE:
		
		if (!gameObject.GetTransform()->isSwappingTile)
			return std::make_shared<MoveState>();
		return nullptr;
	case NotifyEvent::EVENT_DIG:
		return nullptr;
	case NotifyEvent::EVENT_ATTACK:
		return std::make_shared<AttackState>();
	default:;
	}
	return nullptr;
}

std::shared_ptr<dae::BaseState> dae::AttackState::Swap(NotifyEvent event, GameObject& gameObject)
{
	UNREFERENCED_PARAMETER(event);
	UNREFERENCED_PARAMETER(gameObject);
	switch (event)
	{
	case NotifyEvent::EVENT_IDLE:
		return std::make_shared<IdleState>();
	case NotifyEvent::EVENT_MOVE:
		return std::make_shared<IdleState>();
	case NotifyEvent::EVENT_DIG:
		return std::make_shared<DigState>();
	case NotifyEvent::EVENT_ATTACK:
		return nullptr;
	default:;
	}

	return nullptr;
}
