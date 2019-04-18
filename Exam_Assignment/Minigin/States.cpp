#include "MiniginPCH.h"
#include "States.h"
#include "GameObject.h"
#include "ServiceLocator.h"

std::shared_ptr<dae::BaseState> dae::DirectionState::Swap(GameObject& gameObject)
{
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
	auto resource = ServiceLocator::GetResourceManager();	
	SpriteFlip(gameObject);
	auto anim = ServiceLocator::GetAnimationManager();
	auto clip = anim->GetAnimationClips(m_StateAnimClipId);
	if (gameObject.GetTransform() && m_StateAnimClipId != 0)
		switch (gameObject.GetTransform()->GetCurrentDirection())
		{
		case Direction::UP:
			if (gameObject.GetTexture() && gameObject.GetSprite())
			{
				for(UINT frame = 0; frame < clip.at(static_cast<UINT>(Direction::UP)).size(); frame++)
				{
					if(gameObject.GetSprite()->GetActiveAnimationFrame() == frame)
						gameObject.GetTexture()->SetTexture(resource->GetTexture(clip.at(static_cast<UINT>(Direction::UP)).at(frame)));
				}
			}
			break;
		case Direction::DOWN:
			if (gameObject.GetTexture() && gameObject.GetSprite())
			{
				for (UINT frame = 0; frame < clip.at(static_cast<UINT>(Direction::DOWN)).size(); frame++)
				{
					if (gameObject.GetSprite()->GetActiveAnimationFrame() == frame)
						gameObject.GetTexture()->SetTexture(resource->GetTexture(clip.at(static_cast<UINT>(Direction::DOWN)).at(frame)));
				}
			}
			break;
		case Direction::LEFT:
			if (gameObject.GetTexture() && gameObject.GetSprite())
			{
				for (UINT frame = 0; frame < clip.at(static_cast<UINT>(Direction::LEFT)).size(); frame++)
				{
					if (gameObject.GetSprite()->GetActiveAnimationFrame() == frame)
						gameObject.GetTexture()->SetTexture(resource->GetTexture(clip.at(static_cast<UINT>(Direction::LEFT)).at(frame)));
				}
			}
			break;
		case Direction::RIGHT:
			if (gameObject.GetTexture() && gameObject.GetSprite())
			{
				for (UINT frame = 0; frame < clip.at(static_cast<UINT>(Direction::RIGHT)).size(); frame++)
				{
					if (gameObject.GetSprite()->GetActiveAnimationFrame() == frame)
						gameObject.GetTexture()->SetTexture(resource->GetTexture(clip.at(static_cast<UINT>(Direction::RIGHT)).at(frame)));
				}
			}
			break;
		default: ;
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

std::shared_ptr<dae::BaseState> dae::IdleState::Swap(GameObject & gameObject)
{
	UNREFERENCED_PARAMETER(gameObject);
	return nullptr;
}

//void dae::IdleState::Update(float & deltaTime, GameObject & gameObject)
//{
//	UNREFERENCED_PARAMETER(deltaTime);
//	UNREFERENCED_PARAMETER(gameObject);
//}

std::shared_ptr<dae::BaseState> dae::DigState::Swap(GameObject& gameObject)
{
	UNREFERENCED_PARAMETER(gameObject);
	return nullptr;
}

//void dae::DigState::Update(float& deltaTime, GameObject& gameObject)
//{
//	UNREFERENCED_PARAMETER(deltaTime);
//	UNREFERENCED_PARAMETER(gameObject);
//
//}
