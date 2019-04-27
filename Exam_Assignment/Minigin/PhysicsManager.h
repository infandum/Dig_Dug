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

		void AddCollision(CollisionComponent* collision);
		CollisionComponent* GetCollision(GameObject* owner);

		bool ShowCollisionBox(bool show) { return m_ShowCollisionBox = show; }
		bool ShowCollisionBox() const { return m_ShowCollisionBox; }

		void SetCollisionPadding(const float padding) { m_CollisionPadding = padding; }
		float GetCollisionPadding() const { return m_CollisionPadding; }


	protected:
		bool IsOverlapping(CollisionComponent* firstComp, CollisionComponent* secondComp) const;
		bool CheckBoxesIntersect(CollisionBox firstCollision, CollisionBox SecondCollision) const { return (abs((firstCollision.x ) - SecondCollision.x) * 2 < (firstCollision.RadiusX + SecondCollision.RadiusX)) && (abs(firstCollision.y - SecondCollision.y) * 2 < (firstCollision.RadiusY + SecondCollision.RadiusY));}
	private:
		std::vector<CollisionComponent*> m_pCollisionComponents{};
		bool m_ShowCollisionBox = false;
		float m_CollisionPadding = 1.0f;

		//BOX: x & y center pos W & H radius
		
	};
}
