#pragma once
#include "Service.h"

namespace dae
{
	class CollisionComponent;
	class GameObject;
	class PhysicsManager final : public Service
	{
	public:
		PhysicsManager() = default;

		void Update(float deltaTime);

		void AddCollision(CollisionComponent* collision);
		CollisionComponent* GetCollision(GameObject* owner);

		bool ShowCollisionBox(bool show) { return m_ShowCollisionBox = show; }
		bool ShowCollisionBox() const { return m_ShowCollisionBox; }

		void SetCollisionPadding(const float padding = 2.0f) { m_CollisionPadding = padding; }
		float GetCollisionPadding() const { return m_CollisionPadding; }


	protected:
		bool CheckBoxesIntersect(CollisionBox firstCollision, CollisionBox SecondCollision) const { return (abs((firstCollision.x ) - SecondCollision.x) * 2 < (firstCollision.RadiusX + SecondCollision.RadiusX)) && (abs(firstCollision.y - SecondCollision.y) * 2 < (firstCollision.RadiusY + SecondCollision.RadiusY));}
	private:
		std::vector<CollisionComponent*> m_pCollisionComponents{};
		bool m_ShowCollisionBox = false;
		float m_CollisionPadding = 2.0f;	
	};
}
