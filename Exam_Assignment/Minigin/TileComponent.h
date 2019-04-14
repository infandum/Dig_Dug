#pragma once
#include "BaseComponent.h"

namespace dae
{
	enum class TileState;
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

		iVector2 GetPositionIndex() const { return m_TileIndex; }

		void SetBorder(Direction dir, bool isCrossed);
		bool GetBorder(Direction dir) { return m_IsBorderCrossed[static_cast<int>(dir)]; }
		
	protected:
		/*void Initialize() override;*/
		void Update(float& deltaTime) override;
		/*void Draw(float& deltaTime) override;*/
		
	private:
		TileState m_TileState = TileState::EMPITY;
		bool m_NeedsUpdate = false;
		bool m_IsBorderCrossed[4]{};
		iVector2 m_TileIndex{};
	};
}
