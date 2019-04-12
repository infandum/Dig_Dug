#pragma once
#include "Singleton.h"

namespace dae {
	class TileComponent;
	class TileManager final : public Singleton<TileManager>
	{
	public:
		TileManager() = default;
		virtual ~TileManager() = default;

	private:
		std::vector<TileComponent*> m_pTileObjects{};
	};
}
