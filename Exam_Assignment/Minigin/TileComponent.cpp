#include "MiniginPCH.h"
#include "TileComponent.h"
#include "GameObject.h"
#include "TextureComponent.h"
#include "TileManager.h"
#include "ResourceManager.h"

dae::TileComponent::TileComponent(TileState state, int xIndex, int yIndex) : m_TileState(state) 
{
	auto& tiles = TileManager::GetInstance();
	m_TileIndex.x = xIndex; 
	m_TileIndex.y = yIndex;
	tiles.AddTile(this);
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
	case Direction::UP:
		m_IsBorderCrossed[0] = isCrossed;
		break;
	case Direction::DOWN:
		m_IsBorderCrossed[1] = isCrossed;
		break;
	case Direction::LEFT:
		m_IsBorderCrossed[2] = isCrossed;
		break;
	case Direction::RIGHT:
		m_IsBorderCrossed[3] = isCrossed;
		break;
	}
	//m_IsBorderCrossed[static_cast<int>(dir)] = isCrossed;
}

void dae::TileComponent::Update(float& deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	auto& resource = ResourceManager::GetInstance();
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
					GetGameObject()->GetComponent<TextureComponent>()->SetTexture(resource.GetTexture(11));
				break;
			case TileState::BLOCKED:
				if (GetGameObject()->GetComponent<TextureComponent>())
					GetGameObject()->GetComponent<TextureComponent>()->SetTexture(resource.GetTexture(12));
				break;
			case TileState::OCCUPIED:
				if (GetGameObject()->GetComponent<TextureComponent>())
					GetGameObject()->GetComponent<TextureComponent>()->SetTexture(std::make_shared<Texture2D>(nullptr));
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
