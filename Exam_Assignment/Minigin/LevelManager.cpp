#include "MiniginPCH.h"
#include "LevelManager.h"
#include "GameObject.h"
#include <glm/detail/type_vec3.hpp>

void dae::LevelManager::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	//TODO: TRACK NPCs
	//TODO: CLEAN UP AND REFRACTOR
	
	for (auto& player : m_pPlayers)
	{
		if (player != nullptr  && player->GetGameObject()->GetTransform() != nullptr)
		{

			if (m_StartTile == nullptr)
			{
				m_StartTile = GetTile(player->GetGameObject()->GetTransform()->GetPositionIndex().x, player->GetGameObject()->GetTransform()->GetPositionIndex().y);
				//Dig out starting tile if player starts underground
				if (m_StartTile->GetTileState() == TileState::DIRT)
					m_StartTile->SetTileState(TileState::DUG);
			}

			if (IsSwitchingTile(player->GetGameObject()->GetTransform()->GetPosition().x, player->GetGameObject()->GetTransform()->GetPosition().y))
			{
				int x = static_cast<int>(round(player->GetGameObject()->GetTransform()->GetPosition().x / 32.0f));
				int y = static_cast<int>(round(player->GetGameObject()->GetTransform()->GetPosition().y / 32.0f));
				const auto nextTile = GetTile(x, y);
				if (nextTile != nullptr && nextTile != m_StartTile)
				{
					const auto dir = player->GetGameObject()->GetTransform()->GetCurrentDirection();
					if (dir != Direction::NONE)
					{
						//TODO: FALSE POSITIVE TUNNEL CONNECTION (DIRECTION IS PROBALY BUGGY)
						DigConnection(m_StartTile, nextTile, dir);
						player->GetGameObject()->GetComponent<TransformComponent>()->SetPositionIndex({ x, y });
						if (GetTile(x, y)->GetTileState() != TileState::EMPITY)
							GetTile(x, y)->SetTileState(TileState::DUG);
						m_StartTile = nextTile;
					}
				}
			}
		}
	}
	for(auto& entity : m_pEntities)
	{
		if (entity != nullptr  && entity->GetGameObject()->GetTransform() != nullptr)
		{
			if (IsSwitchingTile(entity->GetGameObject()->GetTransform()->GetPosition().x, entity->GetGameObject()->GetTransform()->GetPosition().y))
			{
				int x = static_cast<int>(round(entity->GetGameObject()->GetTransform()->GetPosition().x / 32.0f));
				int y = static_cast<int>(round(entity->GetGameObject()->GetTransform()->GetPosition().y / 32.0f));
				entity->GetGameObject()->GetComponent<TransformComponent>()->SetPositionIndex({ x, y });
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

void dae::LevelManager::AddPlayer(InputComponent* pPlayer)
{
	for (auto& component : m_pPlayers)
	{
		if (typeid(*component) == typeid(*pPlayer))
		{
			std::cout << "Component Duplicate: " << typeid(*pPlayer).name() << " >> Already added!!";
			return;
		}
	}
	m_pPlayers.push_back(pPlayer);
}

void dae::LevelManager::RemovePlayer(InputComponent* pPlayer)
{
	const auto ent = std::find(m_pPlayers.begin(), m_pPlayers.end(), pPlayer);
	if (ent == m_pPlayers.end())
	{
		std::wcout << L"GameObject::RemoveComponent > Component is not attached to this GameObject!" << std::endl;
		return;
	}
	m_pPlayers.erase(ent);
}

void dae::LevelManager::AddEntity(NpcComponent* pEntity)
{
	for (auto& entity : m_pEntities)
	{
		if (typeid(*entity) == typeid(*pEntity))
		{
			std::cout << "Component Duplicate: " << typeid(*pEntity).name() << " >> Already added!!";
			return;
		}
	}
	m_pEntities.push_back(pEntity);
}

void dae::LevelManager::RemoveEntity(NpcComponent* pEntity)
{
	const auto entity = std::find(m_pEntities.begin(), m_pEntities.end(), pEntity);
	if (entity == m_pEntities.end())
	{
		std::wcout << L"GameObject::RemoveComponent > Component is not attached to this GameObject!" << std::endl;
		return;
	}
	m_pEntities.erase(entity);
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

bool dae::LevelManager::IsSwitchingTile(float posX, float posY) const
{
	double modX = fmod(round(posX), 32.0);
	double modY = fmod(round(posY), 32.0);
	bool isSwapping = false;
	bool isEnteringLeft = false;
	bool isEnterRight = false;
	bool isEnteringUp = false;
	bool isEnterDown = false;

	if (modX >= 2 && modX < 14)
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
		isSwapping = true;

	}
	else if (modX > 18 && modX <= 30)
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
		isSwapping = true;
	}
	else if (modY > 18 && modY <= 30)
	{
		//std::cout << "LEAVING TILE TO THE UP\n";
		/*if (m_pPlayer->GetTransform()->GetCurrentDirection() == Direction::UP)
			m_pPlayer->GetTransform()->isSwappingTile = true;*/
		isEnterDown = true;
	}

	return isSwapping;
}
