#include "MiniginPCH.h"
#include "LevelManager.h"
#include "GameObject.h"


void dae::LevelManager::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	//GetTile(4, 6)->SetTileState(TileState::OCCUPIED);

	if (m_pPlayer != nullptr  && m_pPlayer->GetTransform() != nullptr)
	{

		if (m_StartTile == nullptr)
		{
			m_StartTile = GetTile(m_pPlayer->GetTransform()->GetPositionIndex().x, m_pPlayer->GetTransform()->GetPositionIndex().y);
			//Dig out starting tile if player starts underground
			if (m_StartTile->GetTileState() == TileState::DIRT)
				m_StartTile->SetTileState(TileState::DUG);
		}

		double modX = fmod(round(m_pPlayer->GetTransform()->GetPosition().x), 32.0);
		double modY = fmod(round(m_pPlayer->GetTransform()->GetPosition().y), 32.0);
		bool isSwappingTile = false;

		if(modX >= 2 && modX < 14)
		{
			//std::cout << "LEAVING TILE TO THE RIGHT\n";
		}
		else if (modX >= 14 && modX <= 18)
		{
			//std::cout << "CENTER\n";
			isSwappingTile = true;
			
		}
		else if( modX > 18 && modX <= 30)
		{
			//std::cout << "LEAVING TILE TO THE LEFT\n";
		}

		if (modY >= 2 && modY < 14)
		{
			//std::cout << "LEAVING TILE TO THE DOWN\n";
		}
		else if (modY >= 14 && modY <= 18)
		{
			//std::cout << "CENTER\n";
			isSwappingTile = true;
		}
		else if (modY > 18 && modY <= 30)
		{
			//std::cout << "LEAVING TILE TO THE UP\n";
		}

		if(isSwappingTile)
		{ 
			int x = static_cast<int>(round(m_pPlayer->GetComponent<TransformComponent>()->GetPosition().x / 32.0f));
			int y = static_cast<int>(round(m_pPlayer->GetComponent<TransformComponent>()->GetPosition().y / 32.0f));
			const auto nextTile = GetTile(x, y);
			if (nextTile != nullptr && nextTile != m_StartTile)
			{
				const auto dir = m_pPlayer->GetComponent<TransformComponent>()->GetDirectionFromVelocity();
				if (dir != Direction::NONE)
				{
					//TODO: FALSE POSITIVE TUNNEL CONNECTION (DIRECTION IS PROBALY BUGGY)
					DigConnection(m_StartTile, nextTile, dir);
					m_pPlayer->GetComponent<TransformComponent>()->SetPositionIndex({ x, y });
					if (GetTile(x, y)->GetTileState() != TileState::EMPITY)
						GetTile(x, y)->SetTileState(TileState::DUG);
					m_StartTile = nextTile;
				}
			}
		}
		//double modX = fmod(round(m_pPlayer->GetComponent<TransformComponent>()->GetPosition().x), 32.0);
		//double modY = fmod(round(m_pPlayer->GetComponent<TransformComponent>()->GetPosition().y), 32.0);
		//bool enterX = false, enterY = false;
		//if (m_pPlayer->GetComponent<TransformComponent>()->IsCentered())
		//{
		//	int x = static_cast<int>(round(m_pPlayer->GetComponent<TransformComponent>()->GetPosition().x / 32.0f));
		//	int y = static_cast<int>(round(m_pPlayer->GetComponent<TransformComponent>()->GetPosition().y / 32.0f));
		//	
		//	if(m_StartTile == nullptr)
		//	{ 
		//		m_StartTile = GetTile(static_cast<int>(round(m_pPlayer->GetComponent<TransformComponent>()->GetPosition().x / 32.0f)), static_cast<int>(round(m_pPlayer->GetComponent<TransformComponent>()->GetPosition().y / 32.0f)));
		//		//Dig out starting tile if player starts underground
		//		if(m_StartTile->GetTileState() == TileState::DIRT)
		//			m_StartTile->SetTileState(TileState::DUG);
		//	}
		//	
		//	if (modX >= 14 && modX <= 20)
		//	{
		//		x = static_cast<int>(round(m_pPlayer->GetComponent<TransformComponent>()->GetPosition().x / 32));
		//		enterX = true;
		//		std::cout << "Player Entering: X\n";
		//		//if(modX < 16)
		//		//	//TODO: PLACE INNER WALL RIGHT
		//		//else
		//		//	//TODO: PLACE INNER WALL LEFT
		//		
		//	}
		//	
		//	if (modY >= 14 && modX <= 20)
		//	{
		//		y = static_cast<int>(round(m_pPlayer->GetComponent<TransformComponent>()->GetPosition().y / 32));
		//		enterY = true;
		//		std::cout << "Player Entering: Y\n";
		//		//if(modX < 16)
		//		//	//TODO: PLACE INNER WALL DOWN
		//		//else
		//		//	//TODO: PLACE INNER WALL UP
		//	}
		//
		//	if (m_pPlayer->GetComponent<TransformComponent>()->IsCentered() && x != 0 && y != 0)
		//	{
		//		const auto tile = GetTile(x, y);
		//		if (tile != nullptr){
		//			if (tile != m_StartTile)
		//			{		
		//				//Check if Tiles are adjected
		//				if(m_StartTile->GetPositionIndex().x + 1 == tile->GetPositionIndex().x || m_StartTile->GetPositionIndex().x - 1 == tile->GetPositionIndex().x
		//				|| m_StartTile->GetPositionIndex().y + 1 == tile->GetPositionIndex().y || m_StartTile->GetPositionIndex().y - 1 == tile->GetPositionIndex().y)
		//				{
		//					const auto dir = m_pPlayer->GetComponent<TransformComponent>()->GetDirectionFromVelocity();
		//					if(dir != Direction::NONE)
		//					{
		//						
		//							DigConnection(m_StartTile, tile, dir);
		//							m_pPlayer->GetComponent<TransformComponent>()->SetPositionIndex({x, y});
		//							if(GetTile(x, y)->GetTileState() != TileState::EMPITY)
		//								GetTile(x, y)->SetTileState(TileState::DUG);
		//						
		//					}
		//				}
		//				m_StartTile = tile;
		//			}
		//		}
		//	}
		//}
	}
}

void dae::LevelManager::AddTile(std::shared_ptr<TileComponent> tile)
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

std::shared_ptr<dae::TileComponent> dae::LevelManager::GetTile(int x, int y)
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

void dae::LevelManager::DigConnection(std::shared_ptr<TileComponent> start, std::shared_ptr<TileComponent> end, Direction dir)
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
	default: ;
	}
	
}

void dae::LevelManager::CreateTunnel(int xIndex, int yIndex, Direction dir, int distance)
{
	UNREFERENCED_PARAMETER(dir);
	auto tile = GetTile(xIndex, yIndex);
	if(tile == nullptr)
	{
		std::cout << "LevelManager::CreateTunnel() > Starting tile add [" << xIndex << "," << yIndex << "] is NULL\n";
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
		default: ;
		}

		if(nextTile == nullptr)
			return;

		DigConnection(tile, nextTile, dir);
		tile = nextTile;
		nextTile->SetTileState(TileState::DUG);
	}
}