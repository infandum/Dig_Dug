#include "MiniginPCH.h"
#include "LevelManager.h"
#include "GameObject.h"
#include <glm/detail/type_vec3.hpp>
#include "ServiceLocator.h"

void dae::LevelManager::Reset()
{
	m_WinTimer = 0.f;
	m_Won = false;

	if (m_pTileComponents.empty())
		return;

	if (!m_pEntities.empty())
		if(!m_pEntities[m_ActiveSceneIndex].empty())
			for (auto i = 0; i < m_pEntities[m_ActiveSceneIndex].size(); i++)
			{
				m_pEntities[m_ActiveSceneIndex][i]->GetGameObject()->Enable(true);
				m_pEntities[m_ActiveSceneIndex][i]->Reset();
			}

	if (!m_pPlayers.empty())
		if (!m_pPlayers[m_ActiveSceneIndex].empty())
			for (auto i = 0; i < m_pPlayers[m_ActiveSceneIndex].size(); i++)
			{

				m_pPlayers[m_ActiveSceneIndex][i]->Reset();
			}

	if (!m_pTileComponents.empty())
		if (!m_pTileComponents[m_ActiveSceneIndex].empty())
			if(!m_pTileComponents[m_ActiveSceneIndex].empty())
			{
				for (auto x = 0; x < 14; ++x)
				{
					for (auto y = 0; y < 17; ++y)
					{
						auto tile = GetTile(x, y);
						tile->Reset();
						tile->SetTileState(TileState::EMPITY);
						if (y <= 1)
							tile->SetTileState(TileState::EMPITY);
						else
							tile->SetTileState(TileState::FREE);
						
					}
				}
			}

	m_Reset = true;
}

void dae::LevelManager::Respawn()
{
	if (!m_pEntities.empty())
		if (!m_pEntities[m_ActiveSceneIndex].empty())
			for (auto i = 0; i < m_pEntities[m_ActiveSceneIndex].size(); i++)
			{
				if(m_pEntities[m_ActiveSceneIndex][i]->IsDead())
					continue;

				m_pEntities[m_ActiveSceneIndex][i]->GetGameObject()->Enable(true);
				m_pEntities[m_ActiveSceneIndex][i]->Reset();
			}

	if (!m_pPlayers.empty())
		if (!m_pPlayers[m_ActiveSceneIndex].empty())
			for (auto i = 0; i < m_pPlayers[m_ActiveSceneIndex].size(); i++)
			{

				m_pPlayers[m_ActiveSceneIndex][i]->Respawn();
			}

	m_Reset = true;
}

void dae::LevelManager::Initialize()
{
	m_Reset = true;
	SetActiveScene(ServiceLocator::GetSceneManager()->GetActiveSceneIndex());
}

void dae::LevelManager::Update(float deltaTime)
{
	//TODO: CLEAN UP AND REFRACTOR
	//TODO: MOVE DIGGING TO PLAYER
	SetActiveScene(ServiceLocator::GetSceneManager()->GetActiveSceneIndex());
	PlayerTracking();
		

	EnityTracking();

	LevelWin(deltaTime);
}

void dae::LevelManager::PlayerTracking()
{
	if (!m_pPlayers.empty())
		if (!m_pPlayers[m_ActiveSceneIndex].empty())
		{
			int GameOvers = 0;
			for (auto i = 0; i < m_pPlayers[m_ActiveSceneIndex].size(); i++)
			{
				if (m_Reset || m_pPlayers[m_ActiveSceneIndex][i]->IsDead())
				{
					m_StartTile[m_ActiveSceneIndex][i] = GetTile(m_pPlayers[m_ActiveSceneIndex][i]->GetGameObject()->GetTransform()->GetPositionIndex().x, m_pPlayers[m_ActiveSceneIndex][i]->GetGameObject()->GetTransform()->GetPositionIndex().y);
					m_StartTile[m_ActiveSceneIndex][i]->SetTileState(TileState::USED);
					m_StartTile[m_ActiveSceneIndex][i]->SetOccupied(true);

					if (i >= m_pPlayers[m_ActiveSceneIndex].size() - 1 && m_StartTile[m_ActiveSceneIndex][i]->GetTileState() == TileState::USED)
						m_Reset = false;

				}


				if (IsSwitchingTile(m_pPlayers[m_ActiveSceneIndex][i]->GetGameObject()->GetTransform()->GetPosition().x, m_pPlayers[m_ActiveSceneIndex][i]->GetGameObject()->GetTransform()->GetPosition().y))
				{
					int x = static_cast<int>(round(m_pPlayers[m_ActiveSceneIndex][i]->GetGameObject()->GetTransform()->GetPosition().x / 32.0f));
					int y = static_cast<int>(round(m_pPlayers[m_ActiveSceneIndex][i]->GetGameObject()->GetTransform()->GetPosition().y / 32.0f));
					const auto nextTile = GetTile(x, y);

					if (nextTile != nullptr && nextTile != m_StartTile[m_ActiveSceneIndex][i])
					{
						const auto dir = m_pPlayers[m_ActiveSceneIndex][i]->GetGameObject()->GetComponent<MoveComponent>()->GetCurrentDirection();
						if (dir != Direction::NONE)
						{
							m_pPlayers[m_ActiveSceneIndex][i]->GetGameObject()->GetComponent<TransformComponent>()->SetPositionIndex({ x, y });
							if (!m_pPlayers[m_ActiveSceneIndex][i]->IsCrushed() && !m_pPlayers[m_ActiveSceneIndex][i]->IsDead())
								if (m_pPlayers[m_ActiveSceneIndex][i]->GetType() == PlayerType::PLAYER_DIGDUG)
								{
									DigConnection(m_StartTile[m_ActiveSceneIndex][i], nextTile, dir);
									if (GetTile(x, y)->GetTileState() != TileState::EMPITY)
										GetTile(x, y)->SetTileState(TileState::USED, m_pPlayers[m_ActiveSceneIndex][i]);
									m_StartTile[m_ActiveSceneIndex][i] = nextTile;
								}

						}
					}
				}

				if (m_pPlayers[m_ActiveSceneIndex][i]->IsGameOver())
					GameOvers++;
			}

			if (GameOvers >= m_pPlayers[m_ActiveSceneIndex].size())
			{
				ServiceLocator::GetSceneManager()->SetActive("Main menu");
			}

		}
}

void dae::LevelManager::EnityTracking()
{

	if (!m_pEntities.empty())
		if (!m_pEntities[m_ActiveSceneIndex].empty())
		{
			int deadEnities = 0;
			int rockCount = 0;
			for (auto& entity : m_pEntities[m_ActiveSceneIndex])
			{
				if (entity->IsDead())
					deadEnities++;

				if (entity->GetType() == NPCType::ROCK)
					rockCount++;

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

			if (deadEnities >= m_pEntities[m_ActiveSceneIndex].size() - rockCount)
			{
				auto player = GetPlayer(PlayerType::PLAYER_FYGAR);
				if (player)
				{
					if (player->IsDead())
						m_Won = true;
				}
				else
				{
					m_Won = true;


				}
			}
		}
}

void dae::LevelManager::AddTile(TileComponent* tile)
{
	m_ActiveSceneIndex = ServiceLocator::GetSceneManager()->GetActiveSceneIndex();
	if (m_pTileComponents.empty() || m_pTileComponents.size() <= m_ActiveSceneIndex)
		for (auto i = m_pTileComponents.size(); i <= m_ActiveSceneIndex; ++i)
		{
			m_pTileComponents.push_back(std::vector<TileComponent*>());
		}

	for (auto& component : m_pTileComponents[m_ActiveSceneIndex])
	{
		if (component->GetPositionIndex().x == tile->GetPositionIndex().x && component->GetPositionIndex().y == tile->GetPositionIndex().y)
		{
			std::cout << "Tile Duplicate: " << "[" << component->GetPositionIndex().x << "," << component->GetPositionIndex().y << "] >> Already added!!\n";
			return;
		}
	}

	m_pTileComponents[m_ActiveSceneIndex].push_back(tile);
}

dae::TileComponent* dae::LevelManager::GetTile(int x, int y)
{
	m_ActiveSceneIndex = ServiceLocator::GetSceneManager()->GetActiveSceneIndex();
	if (m_pTileComponents[m_ActiveSceneIndex].empty())
		return new TileComponent(TileState::OCCUPIED, 0, 0);

	for (auto& component : m_pTileComponents[m_ActiveSceneIndex])
	{
		if (component->GetPositionIndex().x == x && component->GetPositionIndex().y == y)
		{
			return component;
		}
	}
	return nullptr;
}

std::vector<dae::TileComponent*> dae::LevelManager::GetTilesByState(const TileState& state)
{
	std::vector<dae::TileComponent*> tiles;
	auto i = m_pTileComponents[m_ActiveSceneIndex].begin(), end = m_pTileComponents[m_ActiveSceneIndex].end();
	for (auto& component : m_pTileComponents[m_ActiveSceneIndex])
	{
		if (component->GetTileState() == state)
		{
			tiles.push_back(component);
		}
	}

	return tiles;
}

void dae::LevelManager::AddPlayer(PlayerComponent* pPlayer)
{
	m_ActiveSceneIndex = ServiceLocator::GetSceneManager()->GetActiveSceneIndex();
	if (m_pPlayers.empty() || m_pPlayers.size() <= m_ActiveSceneIndex)
		for(auto i = m_pPlayers.size(); i <= m_ActiveSceneIndex; ++i)
		{
			m_pPlayers.push_back(std::vector<PlayerComponent*>());
			m_StartTile.push_back(std::vector<TileComponent*>());
		}

	for (auto& player : m_pPlayers[m_ActiveSceneIndex])
	{
		if (player == pPlayer)
		{
			std::cout << "LevelManager::Player Duplicate: " << typeid(*pPlayer).name() << " >> Already added!!";
			return;
		}
	}
	m_pPlayers[m_ActiveSceneIndex].push_back(pPlayer);
	m_StartTile[m_ActiveSceneIndex].push_back(nullptr);
}

void dae::LevelManager::RemovePlayer(PlayerComponent* pPlayer)
{
	const auto ent = std::find(m_pPlayers[m_ActiveSceneIndex].begin(), m_pPlayers[m_ActiveSceneIndex].end(), pPlayer);
	if (ent == m_pPlayers[m_ActiveSceneIndex].end())
	{
		std::wcout << L"LevelManager::RemovePlayer > Player is not attached to this GameObject!" << std::endl;
		return;
	}
	m_pPlayers[m_ActiveSceneIndex].erase(ent);
}

bool dae::LevelManager::PlayerDied()
{
	bool died = false;
	if (!m_pPlayers.empty())
		if (!m_pPlayers[m_ActiveSceneIndex].empty())
			for (auto i = 0; i < m_pPlayers[m_ActiveSceneIndex].size(); i++)
			{

				died = m_pPlayers[m_ActiveSceneIndex][i]->IsDead();
			}
	

	return died;
}

dae::PlayerComponent* dae::LevelManager::GetPlayer(const PlayerType& type)
{
	for (auto& player : m_pPlayers[m_ActiveSceneIndex])
	{
		if (player->GetType() == type)
			return player;
	}

	return nullptr;
}

void dae::LevelManager::AddEntity(NpcComponent* pEntity)
{
	m_ActiveSceneIndex = ServiceLocator::GetSceneManager()->GetActiveSceneIndex();
	if (m_pEntities.empty() || m_pEntities.size() <= m_ActiveSceneIndex)
		for (auto i = m_pEntities.size(); i <= m_ActiveSceneIndex; ++i)
		{
			m_pEntities.push_back(std::vector<NpcComponent*>());
		}

	for (auto& entity : m_pEntities[m_ActiveSceneIndex])
	{
		if (entity == pEntity)
		{
			std::cout << "LevelManager::Enemy Duplicate: " << typeid(*pEntity).name() << " >> Already added!!";
			return;
		}
	}
	m_pEntities[m_ActiveSceneIndex].push_back(pEntity);
	GetTile(pEntity->GetGameObject()->GetTransform()->GetPositionIndex().x, pEntity->GetGameObject()->GetTransform()->GetPositionIndex().y)->SetTileState(TileState::USED);
}

void dae::LevelManager::RemoveEntity(NpcComponent* pEntity)
{
	const auto entity = std::find(m_pEntities[m_ActiveSceneIndex].begin(), m_pEntities[m_ActiveSceneIndex].end(), pEntity);
	if (entity == m_pEntities[m_ActiveSceneIndex].end())
	{
		std::wcout << L"GameObject::RemoveComponent > Component is not attached to this GameObject!" << std::endl;
		return;
	}
	m_pEntities[m_ActiveSceneIndex].erase(entity);
}

void dae::LevelManager::DigConnection(TileComponent* start, TileComponent* end, Direction dir)
{
	start->SetOccupied(false);
	end->SetOccupied(true);
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
	auto tile = GetTile(xIndex, yIndex);
	if(tile == nullptr)
	{
		std::cout << "LevelManager::CreateTunnel() > Starting tile add [" << xIndex << "," << yIndex << "] is NULL\n";
		return;
	}

	tile->SetTileState(TileState::USED);
	for(auto i = 0; i < distance; i++)
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
		nextTile->SetTileState(TileState::USED);
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

void dae::LevelManager::LevelWin(float deltaTime)
{

	if(m_Won)
	{
		if(m_WinTimer >= m_WinDelayTime)
		{
			m_WinTimer = 0.f;
			m_Won = false;
			const auto scene = ServiceLocator::GetSceneManager();
			m_ActiveSceneIndex++;
			if (m_ActiveSceneIndex == 3 || m_ActiveSceneIndex == 5 || m_ActiveSceneIndex == 7)
			{
				scene->SetActive("Main menu");
			}
			else
			{
				scene->SetActive(static_cast<int>(m_ActiveSceneIndex));
			}
		}
		m_WinTimer += deltaTime;
	}
	
}