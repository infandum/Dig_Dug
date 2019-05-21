#pragma once

namespace dae
{
	class CollisionComponent;
	class GameObject;
	class PhysicsManager final
	{
	public:
		PhysicsManager(const PhysicsManager& other) = delete;
		PhysicsManager(PhysicsManager&& other) noexcept = delete;
		PhysicsManager& operator=(const PhysicsManager& other) = delete;
		PhysicsManager& operator=(PhysicsManager&& other) noexcept = delete;

		PhysicsManager() = default;
		virtual ~PhysicsManager() = default;

		void AddCollision(CollisionComponent* collision);
		CollisionComponent* GetCollision(GameObject* owner);

		bool ShowCollisionBox(bool show) { return m_ShowCollisionBox = show; }
		bool ShowCollisionBox() const { return m_ShowCollisionBox; }

		void SetCollisionPadding(const float padding = 2.0f) { m_CollisionPadding = padding; }
		float GetCollisionPadding() const { return m_CollisionPadding; }

		void Reset();

		void Initialize();
		void Update(float deltaTime);

		bool CheckBoxesIntersect(CollisionBox firstCollision, CollisionBox SecondCollision) const { return (abs((firstCollision.x ) - SecondCollision.x) * 2 < (firstCollision.RadiusX + SecondCollision.RadiusX)) && (abs(firstCollision.y - SecondCollision.y) * 2 < (firstCollision.RadiusY + SecondCollision.RadiusY));}
	
		void SetActiveScene(size_t sceneIndex) { m_ActiveSceneIndex = sceneIndex; }



	private:
		size_t m_ActiveSceneIndex = 0;

		std::vector<std::vector<CollisionComponent*>> m_pCollisionComponents{};
		bool m_ShowCollisionBox = false;
		bool m_Collision = false;
		float m_CollisionPadding = 2.0f;	
	};
}
