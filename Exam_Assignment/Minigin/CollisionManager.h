#pragma once
#include "Singleton.h"
#include "GameObject.h"

namespace dae
{
	class CollisionComponent;

	class CollisionManager final : public dae::Singleton<CollisionManager>
	{
	public:
		CollisionManager() = default;

		void Update(float deltaTime);

		void AddCollision(std::shared_ptr<CollisionComponent> collision);
		std::shared_ptr<CollisionComponent> GetCollision(std::shared_ptr<GameObject> owner);

		bool ShowCollisionBox(bool show) { return m_ShowCollisionBox = show; }
		bool ShowCollisionBox() const { return m_ShowCollisionBox; }

	protected:
		static bool IsOverlapping(std::shared_ptr<CollisionComponent> firstComp, std::shared_ptr<CollisionComponent>secondComp);

	private:
		std::vector<std::shared_ptr<CollisionComponent>> m_pCollisionComponents{};
		bool m_ShowCollisionBox = false;
	};
}
