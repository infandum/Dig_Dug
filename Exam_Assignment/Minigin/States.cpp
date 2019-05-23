#include "MiniginPCH.h"
#include "States.h"
#include "GameObject.h"

std::shared_ptr<dae::BaseState> dae::DirectionState::Swap(NotifyEvent , GameObject& )
{
	return nullptr;
}

void dae::DirectionState::Update(float& , GameObject& )
{}

void dae::DirectionState::Animated(GameObject& gameObject)
{
	
	SpriteFlip(gameObject);
	//const auto gameObject.GetTransform();
	
	if(m_Clip.Name.empty())
		return;
	
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
				if (!m_Clip.IsSingle)
					gameObject.GetSprite()->SetCurrentUV((m_Clip.Size.x * gameObject.GetSprite()->GetActiveAnimationFrame()) + (m_Clip.UV.x + (gameObject.GetSprite()->GetCurrentUV().w * m_Clip.Frames)), m_Clip.UV.y, m_Clip.Size.x, m_Clip.Size.y);
				else 
				{
					gameObject.GetSprite()->SetCurrentUV((m_Clip.Size.x * (gameObject.GetSprite()->GetActiveAnimationFrame()) + (m_Clip.UV.x)), m_Clip.UV.y, m_Clip.Size.x, m_Clip.Size.y);
				}
			}
			break;
		case Direction::UP:
			if (gameObject.GetSprite())
			{
				if (m_Clip.HasUpDown)
				{
					if (gameObject.GetSprite()->GetFlipSprite())
						gameObject.GetSprite()->SetCurrentUV((gameObject.GetTexture()->GetSize().x - gameObject.GetSprite()->GetCurrentUV().w) - ((gameObject.GetSprite()->GetCurrentUV().w * gameObject.GetSprite()->GetActiveAnimationFrame()) + (m_Clip.UV.x + (gameObject.GetSprite()->GetCurrentUV().w * m_Clip.Frames * 2))), m_Clip.UV.y, m_Clip.Size.x, m_Clip.Size.y);
					else
						gameObject.GetSprite()->SetCurrentUV((gameObject.GetSprite()->GetCurrentUV().w * gameObject.GetSprite()->GetActiveAnimationFrame()) + (m_Clip.UV.x + (gameObject.GetSprite()->GetCurrentUV().w * m_Clip.Frames * 2)), m_Clip.UV.y, m_Clip.Size.x, m_Clip.Size.y);
				}
				else if(m_Clip.IsSingle)
				{
					gameObject.GetSprite()->SetCurrentUV((m_Clip.Size.x * (gameObject.GetSprite()->GetActiveAnimationFrame()) + (m_Clip.UV.x)), m_Clip.UV.y, m_Clip.Size.x, m_Clip.Size.y);
				}
				else
				{
					if (gameObject.GetComponent<MoveComponent>()->GetPreviousDirection() == Direction::RIGHT || gameObject.GetComponent<MoveComponent>()->GetPreviousDirection() == Direction::LEFT)
						m_LastHorDir = gameObject.GetComponent<MoveComponent>()->GetPreviousDirection();

					if (m_LastHorDir == Direction::RIGHT)
						gameObject.GetSprite()->SetCurrentUV((m_Clip.Size.x * (gameObject.GetSprite()->GetActiveAnimationFrame()) + (m_Clip.UV.x)), m_Clip.UV.y, m_Clip.Size.x, m_Clip.Size.y);
					if (m_LastHorDir == Direction::LEFT)
						gameObject.GetSprite()->SetCurrentUV((m_Clip.Size.x * gameObject.GetSprite()->GetActiveAnimationFrame()) + (m_Clip.UV.x + (gameObject.GetSprite()->GetCurrentUV().w * m_Clip.Frames)), m_Clip.UV.y, m_Clip.Size.x, m_Clip.Size.y);
				}
			}
			break;
			
		case Direction::DOWN:

			if (gameObject.GetSprite())
			{
				if(m_Clip.HasUpDown)
				{
					if (gameObject.GetSprite()->GetFlipSprite())
						gameObject.GetSprite()->SetCurrentUV((gameObject.GetTexture()->GetSize().x - gameObject.GetSprite()->GetCurrentUV().w) - ((gameObject.GetSprite()->GetCurrentUV().w * gameObject.GetSprite()->GetActiveAnimationFrame()) + (m_Clip.UV.x + (gameObject.GetSprite()->GetCurrentUV().w * m_Clip.Frames * 3))), m_Clip.UV.y, m_Clip.Size.x, m_Clip.Size.y);
					else
						gameObject.GetSprite()->SetCurrentUV((gameObject.GetSprite()->GetCurrentUV().w * gameObject.GetSprite()->GetActiveAnimationFrame()) + (m_Clip.UV.x + (gameObject.GetSprite()->GetCurrentUV().w * m_Clip.Frames * 3)), m_Clip.UV.y, m_Clip.Size.x, m_Clip.Size.y);
				}
				else if (m_Clip.IsSingle)
				{
					gameObject.GetSprite()->SetCurrentUV((m_Clip.Size.x * (gameObject.GetSprite()->GetActiveAnimationFrame()) + (m_Clip.UV.x)), m_Clip.UV.y, m_Clip.Size.x, m_Clip.Size.y);
				}
				else
				{
					if (gameObject.GetComponent<MoveComponent>()->GetPreviousDirection() == Direction::RIGHT || gameObject.GetComponent<MoveComponent>()->GetPreviousDirection() == Direction::LEFT)
						m_LastHorDir = gameObject.GetComponent<MoveComponent>()->GetPreviousDirection();

					if (m_LastHorDir == Direction::RIGHT)
						gameObject.GetSprite()->SetCurrentUV((m_Clip.Size.x * (gameObject.GetSprite()->GetActiveAnimationFrame()) + (m_Clip.UV.x)), m_Clip.UV.y, m_Clip.Size.x, m_Clip.Size.y);
					 if (m_LastHorDir == Direction::LEFT)
						gameObject.GetSprite()->SetCurrentUV((m_Clip.Size.x * gameObject.GetSprite()->GetActiveAnimationFrame()) + (m_Clip.UV.x + (gameObject.GetSprite()->GetCurrentUV().w * m_Clip.Frames)), m_Clip.UV.y, m_Clip.Size.x, m_Clip.Size.y);
				}
			}
			break;
		case Direction::NONE:
			if (!m_Clip.HasUpDown)
			{
				if (m_LastHorDir == Direction::RIGHT)
					gameObject.GetSprite()->SetCurrentUV((m_Clip.Size.x * (gameObject.GetSprite()->GetActiveAnimationFrame()) + (m_Clip.UV.x)), m_Clip.UV.y, m_Clip.Size.x, m_Clip.Size.y);
				if (m_LastHorDir == Direction::LEFT)
					gameObject.GetSprite()->SetCurrentUV((m_Clip.Size.x * gameObject.GetSprite()->GetActiveAnimationFrame()) + (m_Clip.UV.x + (gameObject.GetSprite()->GetCurrentUV().w * m_Clip.Frames)), m_Clip.UV.y, m_Clip.Size.x, m_Clip.Size.y);
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
				if (gameObject.GetTexture() && gameObject.GetSprite() && m_Clip.HasUpDown)
				{
					for(UINT frame = 0; frame < m_Clip.TextureList.at(static_cast<UINT>(Direction::UP)).size(); frame++)
					{
						if(gameObject.GetSprite()->GetActiveAnimationFrame() == frame)
							gameObject.GetTexture()->SetTexture(resource->GetTexture(m_Clip.TextureList.at(static_cast<UINT>(Direction::UP)).at(frame)));
					}
				}
				break;
			case Direction::DOWN:
				if (gameObject.GetTexture() && gameObject.GetSprite() && m_Clip.HasUpDown)
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
			if (gameObject.GetSprite() && m_Clip.HasUpDown)
			{
				if (gameObject.GetComponent<MoveComponent>()->GetPreviousDirection() == Direction::RIGHT)
					gameObject.GetSprite()->SetFlipSprite(SDL_FLIP_NONE);
				if (gameObject.GetComponent<MoveComponent>()->GetPreviousDirection() == Direction::LEFT)
					gameObject.GetSprite()->SetFlipSprite(SDL_FLIP_HORIZONTAL);
			}
			else
				gameObject.GetSprite()->SetFlipSprite(SDL_FLIP_NONE);
			break;
		case Direction::DOWN:
			if (gameObject.GetSprite() && m_Clip.HasUpDown)
			{
				if (gameObject.GetComponent<MoveComponent>()->GetPreviousDirection() == Direction::RIGHT)
					gameObject.GetSprite()->SetFlipSprite(SDL_FLIP_HORIZONTAL);
				if (gameObject.GetComponent<MoveComponent>()->GetPreviousDirection() == Direction::LEFT)
					gameObject.GetSprite()->SetFlipSprite(SDL_FLIP_NONE);
			}
			else
				gameObject.GetSprite()->SetFlipSprite(SDL_FLIP_NONE);
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
