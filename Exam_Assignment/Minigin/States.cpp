#include "MiniginPCH.h"
#include "States.h"
#include "GameObject.h"
#include "ServiceLocator.h"

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