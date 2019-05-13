#pragma once
#include "Service.h"


namespace dae {
	enum class Direction;
	class GameObject;
	class TileComponent;
	class InputComponent;
	class NpcComponent;
	class vec3;
	class LevelManager final : public Service
	{
	public:
		LevelManager() = default;

		void Reset() { m_pTileComponents.clear(); m_pPlayers.clear(); m_pEntities.clear(); m_StartTile = nullptr; }

		void Update(float deltaTime);

		void AddTile(TileComponent* tile);
		TileComponent* GetTile(int x, int y);

		void AddPlayer(InputComponent* pPlayer);
		void RemovePlayer(InputComponent* pPlayer);

		void AddEntity(NpcComponent* pEntity);
		void RemoveEntity(NpcComponent* pEntity);

		static void DigConnection(TileComponent* start, TileComponent* end, Direction dir);
		void CreateTunnel(int xIndex, int yIndex, Direction dir, int distance = {0});

	private:
		bool IsSwitchingTile(float posX, float posY) const;

		std::vector<TileComponent*> m_pTileComponents{};
		std::vector<InputComponent*> m_pPlayers{};
		std::vector<NpcComponent*> m_pEntities {};
		TileComponent* m_StartTile {};
	};
}
