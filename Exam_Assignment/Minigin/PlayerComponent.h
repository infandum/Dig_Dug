#pragma once
#include "InputComponent.h"

namespace dae
{
	class PlayerComponent final : public InputComponent
	{
	public:

		PlayerComponent(const PlayerComponent& other) = delete;
		PlayerComponent(PlayerComponent&& other) noexcept = delete;
		PlayerComponent& operator=(const PlayerComponent& other) = delete;
		PlayerComponent& operator=(PlayerComponent&& other) noexcept = delete;

		PlayerComponent(PlayerType type);
		virtual ~PlayerComponent() = default;

		void Attack(bool& isAttacking);
		void SetAttackRange(float range) { m_AttackRange = range; }
		void SetAttackSpeed(float speed) { m_AttackSpeed = speed; }
		bool IsAttacking() const { return m_isAttacking; }


		bool IsDead() const { return m_IsDead; }
		void SetHealth(int health);
		void ChangeHealth(int amount);

		PlayerType GetType() const { return m_Type; }

		void Reset();
	protected:
		void Initialize() override;
		void AllignAttack();
		void MoveAttack(float deltaTime);
		void CollisionEvents();
		void Update(float deltaTime) override;
		//void Render() override;

	private:
		PlayerType m_Type{};

		std::shared_ptr<GameObject> m_Attack{};
		std::shared_ptr<GameObject> m_AttackSprite{};

		float m_AttackRange = 32.f + 16;
		float m_AttackSpeed = 120.f;
		float m_AttackTimer = 0.0f;
		float m_AttackTime = 0.25f;
		bool m_isAttacking = false;
		bool m_AttackAtMaxRange = false;
		bool m_IsCharging = false;
		bool m_IsDead = false;
		bool m_IsAttackHit = false;
		bool m_IsReset = false;

		Direction m_LastHorDir = Direction::RIGHT;

		int m_Health = 3;
	};

}