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
	auto tiles = ServiceLocator::GetLevelManager();
	tiles->AddPlayer(this);
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
		attack->GetComponent<TextureComponent>()->SetTexture(ServiceLocator::GetResourceManager()->GetTexture(12));
		GetGameObject()->AddChild(attack);
		break;
	}
}

void dae::PlayerComponent::Update(float )
{
	auto input = ServiceLocator::GetInputManager();
	auto command = input->HandleInput();

	if (command != nullptr && command->GetOwner() == GetGameObject())
		command->Execute();
}
