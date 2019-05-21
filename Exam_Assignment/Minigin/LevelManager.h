#pragma once
#include "Subject.h"


namespace dae {
	class PlayerComponent;
	enum class Direction;
	class GameObject;
	class TileComponent;
	class InputComponent;
	class NpcComponent;
	class vec3;
	class LevelManager final : public Subject
	{
	public:
		LevelManager(const LevelManager& other) = delete;
		LevelManager(LevelManager&& other) noexcept = delete;
		LevelManager& operator=(const LevelManager& other) = delete;
		LevelManager& operator=(LevelManager&& other) noexcept = delete;

		LevelManager() = default;

		void Reset(); //{ m_pTileComponents.clear(); m_pPlayers.clear(); m_pEntities.clear(); m_StartTile.clear(); }

		void AddTile(TileComponent* tile);
		TileComponent* GetTile(int x, int y);

		void AddPlayer(PlayerComponent* pPlayer);
		void RemovePlayer(PlayerComponent* pPlayer);

		void AddEntity(NpcComponent* pEntity);
		void RemoveEntity(NpcComponent* pEntity);

		void DigConnection(TileComponent* start, TileComponent* end, Direction dir);
		void CreateTunnel(int xIndex, int yIndex, Direction dir, int distance = {0});

		size_t GetPlayerCount() const { return m_pPlayers[m_ActiveSceneIndex].size(); }
		std::vector<PlayerComponent*> GetPlayers() const { return m_pPlayers[m_ActiveSceneIndex]; }
		PlayerComponent* GetPlayer(int index) { if (index < m_pPlayers[m_ActiveSceneIndex].size()) { return m_pPlayers[m_ActiveSceneIndex][index]; } else return nullptr; }

		NpcComponent* GetNPC(int index) { if (index < m_pEntities[m_ActiveSceneIndex].size()) { return m_pEntities[m_ActiveSceneIndex][index]; } else return nullptr; }

		void SetActiveScene(size_t sceneIndex) { m_ActiveSceneIndex = sceneIndex; }
		size_t GetActiveScene() const { return m_ActiveSceneIndex; }

		void Initialize();
		void Update(float deltaTime);

	private:
		bool IsSwitchingTile(float posX, float posY) const;

		size_t m_ActiveSceneIndex = 0;
		std::vector<std::vector<TileComponent*>> m_pTileComponents{};
		std::vector<std::vector<PlayerComponent*>> m_pPlayers{};
		std::vector<std::vector<NpcComponent*>> m_pEntities {};
		bool m_Reset = true;
		std::vector<std::vector<TileComponent*>> m_StartTile {};

	};
}
