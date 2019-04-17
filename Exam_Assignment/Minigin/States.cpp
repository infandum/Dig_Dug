#include "MiniginPCH.h"
#include "States.h"
#include "GameObject.h"
#include "ServiceLocator.h"

std::shared_ptr<dae::BaseState> dae::DirectionState::Swap(GameObject& gameObject)
{
	if(gameObject.GetTransform())
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
			return std::shared_ptr<DirectionState>();
		case Direction::LEFT:		
			if (gameObject.GetSprite())
				gameObject.GetSprite()->SetFlipSprite(SDL_FLIP_NONE);
			break;
		case Direction::RIGHT:
			if(gameObject.GetSprite())
				gameObject.GetSprite()->SetFlipSprite(SDL_FLIP_NONE);
			break;
		case Direction::NONE:
			if (gameObject.GetSprite())
				gameObject.GetSprite()->SetFlipSprite(SDL_FLIP_NONE);
			break;
		}
	return nullptr;
}

void dae::DirectionState::Update(float& deltaTime, GameObject& gameObject)
{
	auto resource = ServiceLocator::GetResourceManager();
	UNREFERENCED_PARAMETER(deltaTime);
	if (gameObject.GetTransform())
		switch (gameObject.GetTransform()->GetCurrentDirection())
		{
		case Direction::UP:
			if (gameObject.GetTexture())
			{
				gameObject.GetTexture()->SetTexture(resource->GetTexture(1101));
			}
			break;
		case Direction::DOWN:
			if (gameObject.GetTexture())
			{
				gameObject.GetTexture()->SetTexture(resource->GetTexture(1111));
			}
			break;
		case Direction::LEFT:
			if (gameObject.GetTexture())
			{
				gameObject.GetTexture()->SetTexture(resource->GetTexture(1121));
			}
			break;
		case Direction::RIGHT:
			if (gameObject.GetTexture())
			{
				gameObject.GetTexture()->SetTexture(resource->GetTexture(1131));
			}
			break;
		default: ;
		}
}

std::shared_ptr<dae::BaseState> dae::UpState::Swap(GameObject& gameObject)
{
	UNREFERENCED_PARAMETER(gameObject);
	switch (gameObject.GetTransform()->GetCurrentDirection())
	{
	default: ;
	case Direction::UP:
		return std::make_shared<UpState>();
	case Direction::DOWN:
		return std::make_shared<DownState>();
	case Direction::LEFT:
		return std::make_shared<LeftState>();
	case Direction::RIGHT:
		return std::make_shared<RightState>();
	case Direction::NONE:
		return nullptr;
	}
}

void dae::UpState::Update(float& deltaTime, GameObject& gameObject)
{
	UNREFERENCED_PARAMETER(deltaTime);
	if(gameObject.GetTexture())
	{
		auto resource = ServiceLocator::GetResourceManager();
		gameObject.GetTexture()->SetTexture(resource->GetTexture(1101));
	}
}

std::shared_ptr<dae::BaseState> dae::DownState::Swap(GameObject& gameObject)
{
	UNREFERENCED_PARAMETER(gameObject);
	if(gameObject.GetTransform()->GetPreviousDirection() == Direction::RIGHT)
		gameObject.GetSprite()->SetFlipSprite(SDL_FLIP_HORIZONTAL);
	if (gameObject.GetTransform()->GetPreviousDirection() == Direction::LEFT)
		gameObject.GetSprite()->SetFlipSprite(SDL_FLIP_NONE);

	switch (gameObject.GetTransform()->GetCurrentDirection())
	{
	default:;
	case Direction::UP:
		return std::make_shared<UpState>();
	case Direction::DOWN:
		return std::make_shared<DownState>();
	case Direction::LEFT:
		return std::make_shared<LeftState>();
	case Direction::RIGHT:
		return std::make_shared<RightState>();
	case Direction::NONE:
		return nullptr;
	}
}

void dae::DownState::Update(float& deltaTime, GameObject& gameObject)
{
	UNREFERENCED_PARAMETER(deltaTime);
	if (gameObject.GetTexture())
	{
		auto resource = ServiceLocator::GetResourceManager();
		gameObject.GetTexture()->SetTexture(resource->GetTexture(1111));
	}
}

std::shared_ptr<dae::BaseState> dae::LeftState::Swap(GameObject& gameObject)
{
	UNREFERENCED_PARAMETER(gameObject);
	gameObject.GetSprite()->SetFlipSprite(SDL_FLIP_NONE);
	switch (gameObject.GetTransform()->GetCurrentDirection())
	{
	default:;
	case Direction::UP:
		return std::make_shared<UpState>();
	case Direction::DOWN:
		return std::make_shared<DownState>();
	case Direction::LEFT:
		return std::make_shared<LeftState>();
	case Direction::RIGHT:
		return std::make_shared<RightState>();
	case Direction::NONE:
		return nullptr;
	}
}

void dae::LeftState::Update(float& deltaTime, GameObject& gameObject)
{
	UNREFERENCED_PARAMETER(deltaTime);
	if (gameObject.GetTexture())
	{
		auto resource = ServiceLocator::GetResourceManager();
		gameObject.GetTexture()->SetTexture(resource->GetTexture(1121));
	}
}

std::shared_ptr<dae::BaseState> dae::RightState::Swap(GameObject& gameObject)
{
	UNREFERENCED_PARAMETER(gameObject);
	/*gameObject.GetSprite()->SetFlipSprite(SDL_FLIP_NONE);*/
	switch (gameObject.GetTransform()->GetCurrentDirection())
	{
	default:;
	case Direction::UP:
		return std::make_shared<UpState>();
	case Direction::DOWN:
		return std::make_shared<DownState>();
	case Direction::LEFT:
		return std::make_shared<LeftState>();
	case Direction::RIGHT:
		return std::make_shared<RightState>();
	case Direction::NONE:
		return nullptr;
	}
}

void dae::RightState::Update(float& deltaTime, GameObject& gameObject)
{
	UNREFERENCED_PARAMETER(deltaTime);
	if (gameObject.GetTexture())
	{
		auto resource = ServiceLocator::GetResourceManager();
		gameObject.GetTexture()->SetTexture(resource->GetTexture(1131));
	}
}