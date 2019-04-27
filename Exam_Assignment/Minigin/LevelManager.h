#pragma once
#include "Service.h"

namespace dae {
	enum class Direction;
	class GameObject;
	class TileComponent;
	class LevelManager final : public Service
	{
	public:
		LevelManager() = default;

		void Update(float deltaTime);

		void SetPlayer(std::shared_ptr<GameObject> player) { m_pPlayer = player; }
		void AddTile(TileComponent* tile);
		TileComponent* GetTile(int x, int y);

		static void DigConnection(TileComponent* start, TileComponent* end, Direction dir);
		void CreateTunnel(int xIndex, int yIndex, Direction dir, int distance = {0});

	private:
		std::vector<TileComponent*> m_pTileComponents{};
		std::shared_ptr<GameObject> m_pPlayer {};
		TileComponent* m_StartTile {};
	};
}
