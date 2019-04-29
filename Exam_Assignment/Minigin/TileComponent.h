#pragma once
#include "BaseComponent.h"


namespace dae
{
	enum class TileState;
	class BaseState;
	class TileComponent : public BaseComponent
	{
	public:
		TileComponent(const TileComponent& other) = delete;
		TileComponent(TileComponent&& other) noexcept = delete;
		TileComponent& operator=(const TileComponent& other) = delete;
		TileComponent& operator=(TileComponent&& other) noexcept = delete;
		
		explicit TileComponent(TileState state, int xIndex, int yIndex);
		virtual ~TileComponent() = default;

		void SetTileState(TileState state);
		TileState GetTileState() const { return m_TileState; }

		iVector2 GetPositionIndex() const { return m_TileIndex; }

		void SetBorder(Direction dir, bool isCrossed);
		bool GetIsConnectedBorder(Direction dir) { return m_IsBorderConnected[static_cast<int>(dir)]; }
		
	protected:
		/*void Initialize() override;*/
		void Update(float& deltaTime) override;
		void Render() override;

	private:
		TileState m_TileState = TileState::EMPITY;
		std::shared_ptr<BaseState> m_pState{};

		bool m_NeedsUpdate = false;

		bool m_IsBorderConnected[4]{};
		bool m_IsBorderDug[4]{};

		iVector2 m_TileIndex{};
	};
}
