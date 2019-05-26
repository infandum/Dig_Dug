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

		void AddTile(TileComponent* tile);
		TileComponent* GetTile(const iVector2& vec2) { return GetTile(vec2.x, vec2.y); }
		TileComponent* GetTile(int x, int y);
		std::vector<TileComponent*> GetTilesByState(const TileState& state);

		void AddPlayer(PlayerComponent* pPlayer);
		void RemovePlayer(PlayerComponent* pPlayer);
		bool PlayerDied();

		size_t GetPlayerCount() const { if (m_pPlayers.empty()) return 0; return  m_pPlayers[m_ActiveSceneIndex].size(); }
		std::vector<PlayerComponent*> GetPlayers() const { return m_pPlayers[m_ActiveSceneIndex]; }
		PlayerComponent* GetPlayer(int index) { if (index < static_cast<int>(m_pPlayers[m_ActiveSceneIndex].size())) { return m_pPlayers[m_ActiveSceneIndex][index]; } else return nullptr; }
		PlayerComponent* GetPlayer(const PlayerType& type);

		void AddEntity(NpcComponent* pEntity);
		void RemoveEntity(NpcComponent* pEntity);

		static void DigConnection(TileComponent* start, TileComponent* end, Direction dir);
		void CreateTunnel(int xIndex, int yIndex, Direction dir, int distance = {0});

		NpcComponent* GetNPC(int index) { if (index < static_cast<int>(m_pEntities[m_ActiveSceneIndex].size())) { return m_pEntities[m_ActiveSceneIndex][index]; } else return nullptr; }

		void SetActiveScene(size_t sceneIndex) { m_ActiveSceneIndex = sceneIndex; }
		size_t GetActiveScene() const { return m_ActiveSceneIndex; }

		void Reset();
		void Respawn();

		void Initialize();
		
		void Update(float deltaTime);

	private:
		void PlayerTracking();
		void EnityTracking();

		bool IsSwitchingTile(float posX, float posY) const;
		void LevelWin(float deltaTime);

		size_t m_ActiveSceneIndex = 0;

		std::vector<std::vector<TileComponent*>> m_pTileComponents{};
		std::vector<std::vector<PlayerComponent*>> m_pPlayers{};
		std::vector<std::vector<NpcComponent*>> m_pEntities {};

		float m_WinTimer = 0.f;
		float m_WinDelayTime = 2.f;

		bool m_Won = false;
		bool m_Reset = true;
		std::vector<std::vector<TileComponent*>> m_StartTile {};

	};
}
