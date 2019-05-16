#include "MiniginPCH.h"
#include "PlayerComponent.h"
#include "ServiceLocator.h"
#include "InputManager.h"
#include "Commands.h"

dae::PlayerComponent::PlayerComponent(PlayerType type) : m_Type(type)
{
}

void dae::PlayerComponent::Initialize()
{
	/*auto tiles = ServiceLocator::GetLevelManager();
	tiles->AddPlayer(this);*/

	auto attack = std::make_shared<GameObject>();
	switch (m_Type)
	{
	default:
		break;

	case PlayerType::PLAYER_DIGDUG:
		
		attack->SetName("Spear");
		attack->AddComponent(std::make_shared<RenderComponent>());
		attack->AddComponent(std::make_shared<CollisionComponent>());
		attack->AddComponent(std::make_shared<TransformComponent>(GetGameObject()->GetTransform()->GetPosition().x + 32.f, GetGameObject()->GetTransform()->GetPosition().y));
		attack->AddComponent(std::make_shared<MoveComponent>());
		attack->AddComponent(std::make_shared<TextureComponent>());
		/*attack->AddComponent(std::make_shared<SpriteComponent>());*/
		attack->GetComponent<TextureComponent>()->SetTexture(ServiceLocator::GetResourceManager()->GetTexture(12));
		GetGameObject()->AddChild(attack);
		break;

	case PlayerType::PLAYER_FYGAR:
		attack->SetName("Fire");
		attack->AddComponent(std::make_shared<RenderComponent>());
		attack->AddComponent(std::make_shared<CollisionComponent>());
		attack->AddComponent(std::make_shared<TransformComponent>(GetGameObject()->GetTransform()->GetPosition().x + 32.f, GetGameObject()->GetTransform()->GetPosition().y ));
		attack->AddComponent(std::make_shared<MoveComponent>());
		attack->AddComponent(std::make_shared<TextureComponent>());
		/*attack->AddComponent(std::make_shared<SpriteComponent>());*/
		attack->GetComponent<TextureComponent>()->SetTexture(ServiceLocator::GetResourceManager()->GetTexture(11));
		GetGameObject()->AddChild(attack);
		break;
	}
}

void dae::PlayerComponent::Update(float )
{
	ExecuteCommand();

	switch (GetGameObject()->GetComponent<MoveComponent>()->GetCurrentDirection())
	{
	case Direction::RIGHT:
		GetGameObject()->GetChild(0)->GetTransform()->SetLocalPosition(32, 0);
		break;
	case Direction::LEFT:
		GetGameObject()->GetChild(0)->GetTransform()->SetLocalPosition(-32, 0);
		break;
	case Direction::UP:
		GetGameObject()->GetChild(0)->GetTransform()->SetLocalPosition(0, -32);
		break;
	case Direction::DOWN:
		GetGameObject()->GetChild(0)->GetTransform()->SetLocalPosition(0, 32);
		break;
	case Direction::NONE:
		GetGameObject()->GetChild(0)->GetTransform()->SetLocalPosition(32, 0);
		break;
	}
}
