#pragma once
#include "BaseComponent.h"

namespace dae
{
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

		void SetHit(const bool& isHit) { m_IsHit = isHit; }
		bool IsHit() const { return m_IsHit; }

		bool IsDead() const { return m_IsDead;}

		void Reset();
	protected:
		void Initialize() override;
		void Update(float deltaTime) override;
		//void Render() override;

		void Dead();

	private:
		NPCType m_Type{};
		bool m_isGhosting = false;
		bool m_IsHit = false;
		bool m_IsDead = false;
	};
}
