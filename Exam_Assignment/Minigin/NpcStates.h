#pragma once
#include "States.h"

namespace dae
{
	//POOKA STATES
	//************
	class PookaIdleState : public DirectionState
	{
	public:
		virtual ~PookaIdleState() = default;
		std::shared_ptr<BaseState> Swap(NotifyEvent event, GameObject& gameObject) override;
		//void Update(float& deltaTime, GameObject& gameObject) override;
	};

	class PookaMoveState : public DirectionState
	{
	public:
		virtual ~PookaMoveState() = default;
		std::shared_ptr<BaseState> Swap(NotifyEvent event, GameObject& gameObject) override;
		//void Update(float& deltaTime, GameObject& gameObject) override;
	};

	class PookaChaseState : public DirectionState
	{
	public:
		virtual ~PookaChaseState() = default;
		std::shared_ptr<BaseState> Swap(NotifyEvent event, GameObject& gameObject) override;
		//void Update(float& deltaTime, GameObject& gameObject) override;
	};

	class PookaGhostState : public DirectionState
	{
	public:
		virtual ~PookaGhostState() = default;
		std::shared_ptr<BaseState> Swap(NotifyEvent event, GameObject& gameObject) override;
		//void Update(float& deltaTime, GameObject& gameObject) override;
	};

	class PookaInflateState : public DirectionState
	{
	public:
		virtual ~PookaInflateState() = default;
		std::shared_ptr<BaseState> Swap(NotifyEvent event, GameObject& gameObject) override;
		//void Update(float& deltaTime, GameObject& gameObject) override;
	};

	class PookaDeflateState : public DirectionState
	{
	public:
		virtual ~PookaDeflateState() = default;
		std::shared_ptr<BaseState> Swap(NotifyEvent event, GameObject& gameObject) override;
		//void Update(float& deltaTime, GameObject& gameObject) override;
	};

	class PookaCrushState : public DirectionState
	{
	public:
		virtual ~PookaCrushState() = default;
		std::shared_ptr<BaseState> Swap(NotifyEvent event, GameObject& gameObject) override;
		void Update(float& deltaTime, GameObject& gameObject) override;
	private:
		bool m_IsCrushed = false;
		float m_DelayTimer = 0.f;
		float m_DelayMaxTime = 0.5f;
	};

	class PookaDeadState : public DirectionState
	{
	public:
		virtual ~PookaDeadState() = default;
		std::shared_ptr<BaseState> Swap(NotifyEvent event, GameObject& gameObject) override;
		//void Update(float& deltaTime, GameObject& gameObject) override;
	};

	//FYGAR STATES
	//************
	class FygarIdleState : public DirectionState
	{
	public:
		virtual ~FygarIdleState() = default;
		std::shared_ptr<BaseState> Swap(NotifyEvent event, GameObject& gameObject) override;
		//void Update(float& deltaTime, GameObject& gameObject) override;
	};

	class FygarMoveState : public DirectionState
	{
	public:
		virtual ~FygarMoveState() = default;
		std::shared_ptr<BaseState> Swap(NotifyEvent event, GameObject& gameObject) override;
		//void Update(float& deltaTime, GameObject& gameObject) override;
	};

	class FygarChaseState : public DirectionState
	{
	public:
		virtual ~FygarChaseState() = default;
		std::shared_ptr<BaseState> Swap(NotifyEvent event, GameObject& gameObject) override;
		//void Update(float& deltaTime, GameObject& gameObject) override;
	};

	class FygarGhostState : public DirectionState
	{
	public:
		virtual ~FygarGhostState() = default;
		std::shared_ptr<BaseState> Swap(NotifyEvent event, GameObject& gameObject) override;
		//void Update(float& deltaTime, GameObject& gameObject) override;
	};

	class FygarChargingState : public DirectionState
	{
	public:
		virtual ~FygarChargingState() = default;
		std::shared_ptr<BaseState> Swap(NotifyEvent event, GameObject& gameObject) override;
		//void Update(float& deltaTime, GameObject& gameObject) override;
	};

	class FygarAttackState : public DirectionState
	{
	public:
		virtual ~FygarAttackState() = default;
		std::shared_ptr<BaseState> Swap(NotifyEvent event, GameObject& gameObject) override;
		//void Update(float& deltaTime, GameObject& gameObject) override;
	};

	class FygarInflateState : public DirectionState
	{
	public:
		virtual ~FygarInflateState() = default;
		std::shared_ptr<BaseState> Swap(NotifyEvent event, GameObject& gameObject) override;
		//void Update(float& deltaTime, GameObject& gameObject) override;
	};

	class FygarDeflateState : public DirectionState
	{
	public:
		virtual ~FygarDeflateState() = default;
		std::shared_ptr<BaseState> Swap(NotifyEvent event, GameObject& gameObject) override;
		//void Update(float& deltaTime, GameObject& gameObject) override;
	};

	class FygarCrushState : public DirectionState
	{
	public:
		virtual ~FygarCrushState() = default;
		std::shared_ptr<BaseState> Swap(NotifyEvent event, GameObject& gameObject) override;
		void Update(float& deltaTime, GameObject& gameObject) override;
	private:
		bool m_IsCrushed = false;
		float m_DelayTimer = 0.f;
		float m_DelayMaxTime = 0.5f;
	};

	class FygarDeadState : public DirectionState
	{
	public:
		virtual ~FygarDeadState() = default;
		std::shared_ptr<BaseState> Swap(NotifyEvent event, GameObject& gameObject) override;
		//void Update(float& deltaTime, GameObject& gameObject) override;
	};

	//ROCK STATES
	//***********
	class RockIdleState : public DirectionState
	{
	public:
		virtual ~RockIdleState() = default;
		std::shared_ptr<BaseState> Swap(NotifyEvent event, GameObject& gameObject) override;
		//void Update(float& deltaTime, GameObject& gameObject) override;
	};

	class RockFallingState : public DirectionState
	{
	public:
		virtual ~RockFallingState() = default;
		std::shared_ptr<BaseState> Swap(NotifyEvent event, GameObject& gameObject) override;
		void Update(float& deltaTime, GameObject& gameObject) override;		
	};

	class RockLoseState : public DirectionState
	{
	public:
		virtual ~RockLoseState() = default;
		std::shared_ptr<BaseState> Swap(NotifyEvent event, GameObject& gameObject) override;
		void Update(float& deltaTime, GameObject& gameObject) override;
	private:
		bool m_IsFree = false;
		float m_DelayTimer = 0.f;
		float m_DelayMaxTime = 0.25f;
	};

	class RockDeadState : public DirectionState
	{
	public:
		virtual ~RockDeadState() = default;
		std::shared_ptr<BaseState> Swap(NotifyEvent event, GameObject& gameObject) override;
		//void Update(float& deltaTime, GameObject& gameObject) override;
	};
}