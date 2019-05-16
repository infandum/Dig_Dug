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


void dae::TileComponent::Initialize()
{
	auto level = ServiceLocator::GetLevelManager();
	level->AddTile(this);
}

void dae::TileComponent::Update(float)
{

	//TODO:: TILE STATE
	/*const auto state = m_pState->Swap(*GetGameObject());
	if (state != nullptr)
	{
		m_pState = state;
	}*/

	const auto resource = ServiceLocator::GetResourceManager();
	if (m_NeedsUpdate)
	{
		if (GetGameObject())
		{
			switch (m_TileState)
			{
			default:;
			case TileState::FREE:
				if (GetGameObject()->GetComponent<TextureComponent>())
					GetGameObject()->GetComponent<TextureComponent>()->SetTexture(std::make_shared<Texture2D>(nullptr));
				break;
			case TileState::USED:
				if (GetGameObject()->GetComponent<TextureComponent>())
					GetGameObject()->GetComponent<TextureComponent>()->SetTexture(resource->GetTexture(11));
				break;
			case TileState::BLOCKED:
				if (GetGameObject()->GetComponent<TextureComponent>())
					GetGameObject()->GetComponent<TextureComponent>()->SetTexture(resource->GetTexture(12));
				break;
			case TileState::OCCUPIED:
				if (GetGameObject()->GetComponent<TextureComponent>())
					GetGameObject()->GetComponent<TextureComponent>()->SetTexture(resource->GetTexture(13));
				break;
			case TileState::EMPITY:
				if (GetGameObject()->GetComponent<TextureComponent>())
					GetGameObject()->GetComponent<TextureComponent>()->SetTexture(std::make_shared<Texture2D>(nullptr));
				break;
			}
		}
		m_NeedsUpdate = false;
	}
}

void dae::TileComponent::SetTileState(TileState state)
{
	m_TileState = state;
	m_NeedsUpdate = true;
}

void dae::TileComponent::SetBorder(Direction dir, bool isCrossed)
{
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
