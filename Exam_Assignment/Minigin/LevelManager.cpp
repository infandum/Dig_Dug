#include "MiniginPCH.h"
#include "LevelManager.h"
#include "GameObject.h"


void dae::LevelManager::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	//GetTile(4, 6)->SetTileState(TileState::OCCUPIED);
	//TODO: TRACK NPCs
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
		bool isEnteringLeft = false;
		bool isEnterRight = false;
		bool isEnteringUp = false;
		bool isEnterDown = false;

		if(modX >= 2 && modX < 14)
		{
			//std::cout << "LEAVING TILE TO THE RIGHT\n";
			/*if (m_pPlayer->GetTransform()->GetCurrentDirection() == Direction::RIGHT)
				m_pPlayer->GetTransform()->isSwappingTile = true;*/
			isEnteringLeft = true;
		}
		else if (modX >= 14 && modX <= 18)
		{
			//std::cout << "CENTER\n";
			//m_pPlayer->GetTransform()->isSwappingTile = true;
			isSwappingTile = true;
			
		}
		else if( modX > 18 && modX <= 30)
		{
			//std::cout << "LEAVING TILE TO THE LEFT\n";
			/*if (m_pPlayer->GetTransform()->GetCurrentDirection() == Direction::LEFT)
				m_pPlayer->GetTransform()->isSwappingTile = true;*/
			isEnterRight = true;
		}

		if (modY >= 2 && modY < 14)
		{
			//std::cout << "LEAVING TILE TO THE DOWN\n";
			/*if(m_pPlayer->GetTransform()->GetCurrentDirection() == Direction::DOWN)
				m_pPlayer->GetTransform()->isSwappingTile = true;*/
			isEnteringUp = true;
		}
		else if (modY >= 14 && modY <= 18)
		{
			//std::cout << "CENTER\n";
			
			/*m_pPlayer->GetTransform()->isSwappingTile = true;*/
			isSwappingTile = true;
		}
		else if (modY > 18 && modY <= 30)
		{
			//std::cout << "LEAVING TILE TO THE UP\n";
			/*if (m_pPlayer->GetTransform()->GetCurrentDirection() == Direction::UP)
				m_pPlayer->GetTransform()->isSwappingTile = true;*/
			isEnterDown = true;
		}

		if(isSwappingTile)
		{ 
			int x = static_cast<int>(round(m_pPlayer->GetTransform()->GetPosition().x / 32.0f));
			int y = static_cast<int>(round(m_pPlayer->GetTransform()->GetPosition().y / 32.0f));
			const auto nextTile = GetTile(x, y);
			if (nextTile != nullptr && nextTile != m_StartTile)
			{
				const auto dir = m_pPlayer->GetTransform()->GetCurrentDirection();
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
	}
}

void dae::LevelManager::AddTile(TileComponent* tile)
{
	for (auto& component : m_pTileComponents)
	{
		if (component->GetPositionIndex().x == tile->GetPositionIndex().x && component->GetPositionIndex().y == tile->GetPositionIndex().y)
		{
			std::cout << "Tile Duplicate: " << "[" << component->GetPositionIndex().x << "," << component->GetPositionIndex().y << "] >> Already added!!\n";
			return;
		}
	}

	m_pTileComponents.push_back(tile);
}

dae::TileComponent* dae::LevelManager::GetTile(int x, int y)
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

void dae::LevelManager::DigConnection(TileComponent* start, TileComponent* end, Direction dir)
{

	switch (dir)
	{
	case Direction::UP:
		start->SetBorder(Direction::UP, true);
		end->SetBorder(Direction::DOWN, true);

		break;
	case Direction::DOWN:
		start->SetBorder(Direction::DOWN, true);
		end->SetBorder(Direction::UP, true);

		break;
	case Direction::LEFT:
		start->SetBorder(Direction::LEFT, true);
		end->SetBorder(Direction::RIGHT, true);

		break;
	case Direction::RIGHT:
		start->SetBorder(Direction::RIGHT, true);
		end->SetBorder(Direction::LEFT, true);

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
		TileComponent* nextTile = nullptr;
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