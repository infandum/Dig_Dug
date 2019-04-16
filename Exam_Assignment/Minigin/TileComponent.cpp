#include "MiniginPCH.h"
#include "GameObject.h"
#include "Components.h"
#include "TextureComponent.h"
#include "LevelManager.h"

#include "States.h"
#include "ServiceLocator.h"

dae::TileComponent::TileComponent(TileState state, int xIndex, int yIndex) : m_TileState(state) 
{
	auto tiles = ServiceLocator::GetLevelManager();
	m_TileIndex.x = xIndex; 
	m_TileIndex.y = yIndex;
	std::shared_ptr<TileComponent> tile;
	tile.reset(this);
	tiles->AddTile(tile);
}

void dae::TileComponent::SetTileState(TileState state)
{
	/*m_pState = std::make_shared<DirtState>();*/
	m_TileState = state;
	m_NeedsUpdate = true;
}

void dae::TileComponent::SetBorder(Direction dir, bool isCrossed)
{
	switch (dir)
	{
	case Direction::UP:
		m_IsBorderConnected[0] = isCrossed;
		break;
	case Direction::DOWN:
		m_IsBorderConnected[1] = isCrossed;
		break;
	case Direction::LEFT:
		m_IsBorderConnected[2] = isCrossed;
		break;
	case Direction::RIGHT:
		m_IsBorderConnected[3] = isCrossed;
		break;
	default: ;
	}
	//m_IsBorderConnected[static_cast<int>(dir)] = isCrossed;
}

void dae::TileComponent::Update(float& deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	//TODO:: TILE STATE
	/*const auto state = m_pState->Swap(*GetGameObject());
	if (state != nullptr)
	{
		m_pState = state;
	}*/

	const auto resource = ServiceLocator::GetResourceManager();
	if(m_NeedsUpdate)
	{ 
		if (GetGameObject())
		{
			switch (m_TileState)
			{
			default:;
			case TileState::DIRT:
				if (GetGameObject()->GetComponent<TextureComponent>())
					GetGameObject()->GetComponent<TextureComponent>()->SetTexture(std::make_shared<Texture2D>(nullptr));
				break;
			case TileState::DUG:
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
