#pragma once
#include "InputComponent.h"

namespace dae
{
	class LevelManager;
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

		bool IsGameOver() const { return m_Health <= 0; }
		void Dead();
		bool IsDead() const { return m_IsDead; }

		void SetHealth(int health);
		int GetHealth() const { return m_Health; }
		void ChangeHealth(int amount);

		void EnableCrushing(const bool& enable = true);
		bool IsCrushed() const { return m_IsCrushed; }

		int GetPoints() const{ return m_Points; }
		void AddPoints(const int& points)
		{
			m_Points += points;
			Notify(*GetGameObject(), NotifyEvent::EVENT_VALUE_CHECK);
		}

		PlayerType GetType() const { return m_Type; }

		void Reset();

		void onNotify(GameObject& gameObject, NotifyEvent& event) override;

	protected:
		void Initialize() override;
		void PlayerUpdate();
		void RespawnTime(float deltaTime);
		void Update(float deltaTime) override;

		void AllignAttack();
		void MoveAttack(float deltaTime);
		void CollisionEvents();
		
		void Respawn();

	private:
		PlayerType m_Type{};

		std::shared_ptr<GameObject> m_Attack{};
		std::shared_ptr<GameObject> m_AttackSprite{};

		float m_AttackRange = 32.f + 16;
		float m_AttackSpeed = 120.f;
		float m_AttackTimer = 0.0f;
		float m_AttackMaxTime = 0.25f;

		float m_RespawnTimer = 0.0f;
		float m_RespawnMaxTime = 1.0f;

		bool m_isAttacking = false;
		bool m_AttackAtMaxRange = false;
		bool m_IsCharging = false;
		bool m_IsAttackHit = false;

		bool m_IsCrushed = false;
		bool m_IsDead = false;
		bool m_IsReset = false;

		Direction m_LastHorDir = Direction::RIGHT;

		int m_Health = 3;
		int m_Points = 0;

		LevelManager* m_pLevelManager = nullptr;
	};

}