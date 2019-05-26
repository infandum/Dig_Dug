#pragma once
#include "BaseComponent.h"

namespace dae
{
	class PlayerComponent;
	class SpriteComponent;
	class MoveComponent;
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

		NPCType GetType() const { return m_Type; }

		void EnableGhosting(const bool& enable = true) { m_isGhosting = enable; }
		bool IsGhosting() const { return m_isGhosting; }

		void EnableChasing(const bool& enable = true) { m_IsChasing = enable; }
		bool IsChasing() const { return m_IsChasing; }

		void EnableCrushing(const bool& enable = true);
		bool IsCrushed() const { return m_IsCrushed; }

		void EnableInflated(const bool& enable = true) { m_IsInflate = enable; }
		bool IsInflated() const { return m_IsInflate; }

		void SetHit(const bool& isHit);
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
		void StartAttacking();
		void NpcUpdate(float deltaTime);
		void StartTunneling();
		void StartIdleMove();
		void StartChasing();

		void Update(float deltaTime) override;
		//void Render() override;

		void SetChaseTarget(const int& index);
		void StopMovement();
		void IdleMove(float deltaTime);
		void StopChasing();
		void Chasing(float deltaTime);
		void StopTunneling();
		void Tunneling(float deltaTime);

		void AllignAttack() const;
		//void MoveAttack(float deltaTime);
		void Fire(float deltaTime);
		void CollisionEvents() const;

		void Attacking(float deltaTime);
		
	private:
		NPCType m_Type{};

		std::shared_ptr<GameObject> m_Attack{};
		std::shared_ptr<GameObject> m_AttackSprite{};

		bool m_isGhosting = false;
		bool m_IsHit = false;
		bool m_IsInflate = false;
		bool m_IsDead = false;
		bool m_IsFalling = false;

		bool m_IsIdle = true;
		bool m_IsMoving = false;
		bool m_IsChasing = false;
		bool m_IsChangeTunnel = false;

		float m_ActionTimer = 0.f;
		float m_MaxActionTimer = 0.f;
		float m_MaxActionMaxTime = 5.0f;
		float m_ActionMaxTime = 1.0f;
		float m_IdleMaxTime = 2.f;
		float m_MovingMaxTime = 1.5f;
		float m_ChaseMaxTime = 2.f;
		float m_AttackMaxTime = 2.0f;
		float m_FireMaxTime = 0.5f;
		//float m_IdleMaxTime = 0.f;
		PlayerComponent* m_pTarget = nullptr;
		iVector2 m_TargetLocation = { 0,0 };
		Direction m_NewDir = Direction::NONE;
		Direction m_LastHorDir = Direction::RIGHT;

		bool m_IsCrushed = false;
		bool m_IsReset = false;

		bool m_isAttacking = false;
		bool m_IsCharging = false;
		bool m_IsAttackHit = false;

		UINT m_Points = 0;

		LevelManager* m_pLevelManager = nullptr;

		PlayerComponent* m_player = nullptr;
		SpriteComponent* m_pSprite = nullptr;
		MoveComponent* m_pMove = nullptr;
		
		std::map<UINT, UINT> m_CrushedPoints{};
		UINT m_Hits = 0;
	};
}
