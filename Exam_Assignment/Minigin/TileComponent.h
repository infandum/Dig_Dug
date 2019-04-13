#pragma once
#include "BaseComponent.h"
#include "TransformComponent.h"

namespace dae
{
	enum class TileState
	{
		DIRT,
		DUG,
		BLOCKED,
		OCCUPIED,
		EMPITY,
		TILESTATE_MAX_COUNT
	};

	class TileComponent : public BaseComponent
	{
	public:
		TileComponent(const TileComponent& other) = delete;
		TileComponent(TileComponent&& other) noexcept = delete;
		TileComponent& operator=(const TileComponent& other) = delete;
		TileComponent& operator=(TileComponent&& other) noexcept = delete;
		TileComponent() = default;
		explicit TileComponent(TileState state, int xIndex, int yIndex);
		virtual ~TileComponent() = default;

		void SetTileState(TileState state);
		TileState GetTileState() const { return m_TileState; }

		int2 GetPositionIndex() const { return m_TileIndex; }

		void SetBorder(Direction dir, bool isCrossed);
		bool GetBorder(Direction dir) { return m_IsBorderCrossed[static_cast<int>(dir)]; }
		bool m_IsBorderCrossed[4];
	protected:
		/*void Initialize() override;*/
		void Update(float& deltaTime) override;
		/*void Draw(float& deltaTime) override;*/
		
	private:
		TileState m_TileState = TileState::EMPITY;
		bool m_NeedsUpdate = false;
		
		int2 m_TileIndex{0};
	};
}
