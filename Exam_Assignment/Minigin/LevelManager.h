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
		void AddTile(std::shared_ptr<TileComponent> tile);
		std::shared_ptr<TileComponent> GetTile(int x, int y);

		static void DigConnection(std::shared_ptr<TileComponent> start, std::shared_ptr<TileComponent> end, Direction dir);
		void CreateTunnel(int xIndex, int yIndex, Direction dir, int distance = {0});

	private:
		
		std::vector<std::shared_ptr<TileComponent>> m_pTileComponents{};
		std::shared_ptr<GameObject> m_pPlayer {};
		std::shared_ptr<TileComponent> m_StartTile {};
	};
}
