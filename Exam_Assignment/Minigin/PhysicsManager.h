#pragma once
#include "GameObject.h"
#include "Service.h"

namespace dae
{
	class CollisionComponent;

	class PhysicsManager final : public Service
	{
	public:
		PhysicsManager() = default;

		void Update(float deltaTime);

		void AddCollision(std::shared_ptr<CollisionComponent> collision);
		std::shared_ptr<CollisionComponent> GetCollision(std::shared_ptr<GameObject> owner);

		bool ShowCollisionBox(bool show) { return m_ShowCollisionBox = show; }
		bool ShowCollisionBox() const { return m_ShowCollisionBox; }

		void SetCollisionPadding(const float padding) { m_CollisionPadding = padding; }
		float GetCollisionPadding() const { return m_CollisionPadding; }


	protected:
		bool IsOverlapping(std::shared_ptr<CollisionComponent> firstComp, std::shared_ptr<CollisionComponent>secondComp) const;

	private:
		std::vector<std::shared_ptr<CollisionComponent>> m_pCollisionComponents{};
		bool m_ShowCollisionBox = false;
		float m_CollisionPadding = 1.0f;
	};
}
