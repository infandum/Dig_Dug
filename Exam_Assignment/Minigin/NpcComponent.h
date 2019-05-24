#pragma once
#include "BaseComponent.h"
#include "PlayerComponent.h"

namespace dae
{
	class LevelManager;
	class NpcComponent : public BaseComponent
	{
	public:
		NpcComponent(const BaseComponent& other) = delete;
		NpcComponent(BaseComponent&& other) noexcept = delete;
		NpcComponent& operator=(const BaseComponent& other) = delete;
		NpcComponent& operator=(BaseComponent&& other) noexcept = delete;
		NpcComponent(NPCType type);
		virtual ~NpcComponent() = default;

		void EnableGhosting(const bool& enable = true) { m_isGhosting = enable; }
		bool IsGhosting() const { return m_isGhosting; }

		void EnableChasing(const bool& enable = true) { m_IsChasing = enable; }
		bool IsChasing() const { return m_IsChasing; }

		void EnableCrushing(const bool& enable = true);
		bool IsCrushed() const { return m_IsCrushed; }

		void EnableInflated(const bool& enable = true) { m_IsInflate = enable; }
		bool IsInflated() const { return m_IsInflate; }

		void SetHit(const bool& isHit) { m_IsHit = isHit; }
		void Hit(PlayerComponent* player);
		bool IsHit() const { return m_IsHit; }
		PlayerComponent* HitByPlayer() const { return m_player; }
		void HasHit() { m_Hits++; if (m_Hits >= static_cast<UINT>(m_CrushedPoints.size())) m_Hits = static_cast<UINT>(m_CrushedPoints.size()) - 1;}
		
		int PointCalculation() const;

		void Dead();
		bool IsDead() const { return m_IsDead;}

		bool IsAttacking() const { return m_isAttacking; }

		void Reset();

		void onNotify(GameObject& gameObject, NotifyEvent& event) override;

	protected:
		void Initialize() override;
		void Update(float deltaTime) override;
		//void Render() override;

	private:
		NPCType m_Type{};
		bool m_isGhosting = false;
		bool m_IsHit = false;
		bool m_IsInflate = false;
		bool m_IsDead = false;
		bool m_IsFalling = false;
		bool m_IsIdle = true;
		bool m_IsChasing = false;

		float m_ActionTimer = 0.f;

		float m_IdleMaxTime = 2.0f;
		float m_ChaseMaxTime = 2.0f;
		//float m_IdleMaxTime = 0.f;

		bool m_IsCrushed = false;
		bool m_IsReset = false;

		bool m_isAttacking = false;
		bool m_IsCharging = false;
		bool m_IsAttackHit = false;

		UINT m_Points = 0;

		LevelManager* m_pLevelManager;

		PlayerComponent* m_player = nullptr;
		
		std::map<UINT, UINT> m_CrushedPoints;
		UINT m_Hits = 0;
	};
}
