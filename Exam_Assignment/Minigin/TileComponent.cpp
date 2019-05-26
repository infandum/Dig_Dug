#include "MiniginPCH.h"
#include "GameObject.h"
#include "Components.h"
#include "TextureComponent.h"
#include "LevelManager.h"

#include "States.h"
#include "ServiceLocator.h"

dae::TileComponent::TileComponent(TileState state, int xIndex, int yIndex) : m_TileState(state) 
{
	m_TileIndex.x = xIndex;
	m_TileIndex.y = yIndex;

	
}


void dae::TileComponent::onNotify(GameObject& , NotifyEvent& )
{
}

void dae::TileComponent::Initialize()
{
	auto level = ServiceLocator::GetLevelManager();
	level->AddTile(this);
	auto resource = ServiceLocator::GetResourceManager();


	auto go = std::make_shared<GameObject>();
	go->AddComponent(std::make_shared<RenderComponent>());
	go->AddComponent(std::make_shared<TransformComponent>(0.f, 5.f));
	go->AddComponent(std::make_shared<TextureComponent>(resource->GetTexture(05)));
	go->GetRenderer()->EnableRender(false);
	GetGameObject()->AddChild(go);

	go = std::make_shared<GameObject>();
	go->AddComponent(std::make_shared<RenderComponent>());
	go->AddComponent(std::make_shared<TransformComponent>(27.f, 5.f));
	go->AddComponent(std::make_shared<TextureComponent>(resource->GetTexture(05)));
	go->GetRenderer()->EnableRender(false);
	GetGameObject()->AddChild(go);
	
	go = std::make_shared<GameObject>();
	go->AddComponent(std::make_shared<RenderComponent>());
	go->AddComponent(std::make_shared<TransformComponent>(5.f, 0.f));
	go->AddComponent(std::make_shared<TextureComponent>(resource->GetTexture(04)));
	go->GetRenderer()->EnableRender(false);
	GetGameObject()->AddChild(go);

	go = std::make_shared<GameObject>();
	go->AddComponent(std::make_shared<RenderComponent>());
	go->AddComponent(std::make_shared<TransformComponent>(5.f, 27.f));
	go->AddComponent(std::make_shared<TextureComponent>(resource->GetTexture(04)));
	go->GetRenderer()->EnableRender(false);
	GetGameObject()->AddChild(go);

	
}

void dae::TileComponent::Update(float)
{
	if (m_NeedsUpdate)
	{
		if (m_TileState == TileState::USED)
		GetGameObject()->GetRenderer()->EnableRender();
		else
		GetGameObject()->GetRenderer()->EnableRender(false);

		if (GetIsConnectedBorder(Direction::LEFT))
			GetGameObject()->GetChild(0)->GetRenderer()->EnableRender();
		else
			GetGameObject()->GetChild(0)->GetRenderer()->EnableRender(false);

		if (GetIsConnectedBorder(Direction::RIGHT))
			GetGameObject()->GetChild(1)->GetRenderer()->EnableRender();
		else
			GetGameObject()->GetChild(1)->GetRenderer()->EnableRender(false);

		if (GetIsConnectedBorder(Direction::UP))
			GetGameObject()->GetChild(2)->GetRenderer()->EnableRender();
		else
			GetGameObject()->GetChild(2)->GetRenderer()->EnableRender(false);

		if (GetIsConnectedBorder(Direction::DOWN))
			GetGameObject()->GetChild(3)->GetRenderer()->EnableRender();
		else
			GetGameObject()->GetChild(3)->GetRenderer()->EnableRender(false);

		m_NeedsUpdate = false;
	}
	
	
	
}

void dae::TileComponent::SetTileState(TileState state)
{
	
	m_TileState = state;
	m_NeedsUpdate = true;
}

void dae::TileComponent::SetTileState(TileState state, PlayerComponent* owner)
{
	m_TileOwner = owner;
	m_Used = true;
	SetTileState(state);
}

void dae::TileComponent::SetBorder(Direction dir, bool isCrossed)
{
	m_NeedsUpdate = true;
	switch (dir)
	{
	case Direction::RIGHT:
		m_IsBorderConnected[0] = isCrossed;
		break;
	case Direction::LEFT:
		m_IsBorderConnected[1] = isCrossed;
		break;
	case Direction::UP:
		m_IsBorderConnected[2] = isCrossed;
		break;
	case Direction::DOWN:
		m_IsBorderConnected[3] = isCrossed;
		break;
	default:;
	}
	//m_IsBorderConnected[static_cast<int>(dir)] = isCrossed;
}
