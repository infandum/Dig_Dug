#include "MiniginPCH.h"
#include "TileManager.h"
#include "GameObject.h"

extern const float g_MoveSpeed;

void dae::TileManager::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	double modX = 0.0f;
	double modY = 0.0f;
	if(m_pPlayer)
	{
		modX = fmod(round(m_pPlayer->GetComponent<TransformComponent>()->GetPosition().x), 32.0);
		modY = fmod(round(m_pPlayer->GetComponent<TransformComponent>()->GetPosition().y), 32.0);
	
		if (m_pPlayer->GetComponent<TransformComponent>()->IsCentered())
		{
			int x = static_cast<int>(round(m_pPlayer->GetComponent<TransformComponent>()->GetPosition().x / 32.0f));
			int y = static_cast<int>(round(m_pPlayer->GetComponent<TransformComponent>()->GetPosition().y / 32.0f));

			if(m_StartTile == nullptr)
			{ 
				m_StartTile = GetTile(x, y);
				//Dig out starting tile if player starts underground
				if(m_StartTile->GetTileState() == TileState::DIRT)
					m_StartTile->SetTileState(TileState::DUG);
			}

			if (modX >= 6 && modX <= 29)
			{
				x = static_cast<int>(round(m_pPlayer->GetComponent<TransformComponent>()->GetPosition().x / 32));
				//if(modX < 16)
				//	//TODO: PLACE INNER WALL RIGHT
				//else
				//	//TODO: PLACE INNER WALL LEFT
				
			}
			
			if (modY >= 3 && modX <= 29)
			{
				y = static_cast<int>(round(m_pPlayer->GetComponent<TransformComponent>()->GetPosition().y / 32));
				//if(modX < 16)
				//	//TODO: PLACE INNER WALL DOWN
				//else
				//	//TODO: PLACE INNER WALL UP
			}


			const auto tile = GetTile(x, y);
			if (tile != nullptr){
				if (tile != m_StartTile)
				{		
					//Check if Tiles are adjected
					if(m_StartTile->GetPositionIndex().x + 1 == tile->GetPositionIndex().x || m_StartTile->GetPositionIndex().x - 1 == tile->GetPositionIndex().x
					|| m_StartTile->GetPositionIndex().y + 1 == tile->GetPositionIndex().y || m_StartTile->GetPositionIndex().y - 1 == tile->GetPositionIndex().y)
					{
						const Direction dir = m_pPlayer->GetComponent<TransformComponent>()->DirectionFromVelocity();
						DigConnection(m_StartTile, tile, dir);
						if(GetTile(x, y)->GetTileState() != TileState::EMPITY)
							GetTile(x, y)->SetTileState(TileState::DUG);
					}
					m_StartTile = tile;
				}
			}
		}
	}
}

void dae::TileManager::AddTile(std::shared_ptr<TileComponent> tile)
{
	for (auto& component : m_pTileComponents)
	{
		if (component->GetPositionIndex().x == tile->GetPositionIndex().x && component->GetPositionIndex().y == tile->GetPositionIndex().y)
		{
			std::cout << "Tile Duplicate: " << "["<<component->GetPositionIndex().x << "," << component->GetPositionIndex().y << "] >> Already added!!\n";
			return;
		}
	}
	m_pTileComponents.push_back(tile);
}

std::shared_ptr<dae::TileComponent> dae::TileManager::GetTile(int x, int y)
{
	for (auto& component : m_pTileComponents)
	{
		if (component->GetPositionIndex().x == x && component->GetPositionIndex().y == y)
		{
			return component;
		}
	}
	return nullptr;
}

void dae::TileManager::DigConnection(std::shared_ptr<TileComponent> start, std::shared_ptr<TileComponent> end, Direction dir)
{

	switch (dir)
	{
	case Direction::UP:
		start->SetBorder(Direction::UP, true);
		end->SetBorder(Direction::DOWN, true);
		//std::cout << start->GetPositionIndex().x << ", " << start->GetPositionIndex().y << " <" << static_cast<int>(Direction::UP) << "," << static_cast<int>(Direction::DOWN) << "> " << end->GetPositionIndex().x << ", " << end->GetPositionIndex().y << std::endl;

		break;
	case Direction::DOWN:
		start->SetBorder(Direction::DOWN, true);
		end->SetBorder(Direction::UP, true);
		//std::cout << start->GetPositionIndex().x << ", " << start->GetPositionIndex().y << " <" << static_cast<int>(Direction::DOWN) << "," << static_cast<int>(Direction::UP) << "> " << end->GetPositionIndex().x << ", " << end->GetPositionIndex().y << std::endl;

		break;
	case Direction::LEFT:
		start->SetBorder(Direction::LEFT, true);
		end->SetBorder(Direction::RIGHT, true);
		//std::cout << start->GetPositionIndex().x << ", " << start->GetPositionIndex().y << " <" << static_cast<int>(Direction::LEFT) << "," << static_cast<int>(Direction::RIGHT) << "> " << end->GetPositionIndex().x << ", " << end->GetPositionIndex().y << std::endl;

		break;
	case Direction::RIGHT:
		start->SetBorder(Direction::RIGHT, true);
		end->SetBorder(Direction::LEFT, true);
		//std::cout << start->GetPositionIndex().x << ", " << start->GetPositionIndex().y << " <" << static_cast<int>(Direction::RIGHT) << "," << static_cast<int>(Direction::LEFT) << "> " << end->GetPositionIndex().x << ", " << end->GetPositionIndex().y << std::endl;

		break;
	}
	
}

void dae::TileManager::CreateTunnel(int xIndex, int yIndex, Direction dir, int distance)
{
	UNREFERENCED_PARAMETER(dir);
	auto tile = GetTile(xIndex, yIndex);
	if(tile == nullptr)
	{
		std::cout << "TileManager::CreateTunnel() > Starting tile add [" << xIndex << "," << yIndex << "] is NULL\n";
		return;
	}

	tile->SetTileState(TileState::DUG);
	for(auto i = 0; i < distance; ++i)
	{
		std::shared_ptr<TileComponent> nextTile = nullptr;
		switch (dir)
		{
		case Direction::UP:
			nextTile = GetTile(tile->GetPositionIndex().x, tile->GetPositionIndex().y - 1);
			break;
		case Direction::DOWN:
			nextTile = GetTile(tile->GetPositionIndex().x, tile->GetPositionIndex().y + 1);
			break;
		case Direction::LEFT:
			nextTile = GetTile(tile->GetPositionIndex().x - 1, tile->GetPositionIndex().y);
			break;
		case Direction::RIGHT:
			nextTile = GetTile(tile->GetPositionIndex().x + 1, tile->GetPositionIndex().y);
			break;
		}

		if(nextTile == nullptr)
			return;

		DigConnection(tile, nextTile, dir);
		tile = nextTile;
		nextTile->SetTileState(TileState::DUG);
	}
}
