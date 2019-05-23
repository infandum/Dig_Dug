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
		void SetTileState(TileState state, PlayerComponent* owner);
		TileState GetTileState() const { return m_TileState; }

		iVector2 GetPositionIndex() const { return m_TileIndex; }

		void SetBorder(Direction dir, bool isCrossed);
		bool GetIsConnectedBorder(Direction dir) { return m_IsBorderConnected[static_cast<int>(dir)]; }

		void SetOccupied(const bool& occupied) { m_Occupied = occupied; }
		bool IsOccupied() const { return m_Occupied; }
		bool HasBeenUsed() const { return m_Used; }
		PlayerComponent* GetTileOwner() const { return m_TileOwner; }

		void Reset() { for(auto& border : m_IsBorderConnected) { border = false; }  m_Occupied = false; m_Used = false; m_TileOwner = nullptr;}
		
		void onNotify(GameObject& gameObject, NotifyEvent& event) override;

		
	protected:
		void Initialize() override;
		void Update(float deltaTime) override;
		//void Render() override;

	private:
		TileState m_TileState = TileState::EMPITY;
		std::shared_ptr<BaseState> m_pState{};

		bool m_NeedsUpdate = false;

		bool m_IsBorderConnected[4]{};

		bool m_Occupied = false;
		bool m_Used = false;
		PlayerComponent* m_TileOwner = nullptr;

		iVector2 m_TileIndex{};
	};
}
