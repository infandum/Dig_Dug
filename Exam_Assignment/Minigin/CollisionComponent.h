#pragma once
#include "BaseComponent.h"
namespace  dae
{ 
	class CollisionComponent : public BaseComponent
	{
	public:
		CollisionComponent(const CollisionComponent& other) = delete;
		CollisionComponent(CollisionComponent&& other) noexcept = delete;
		CollisionComponent& operator=(const CollisionComponent& other) = delete;
		CollisionComponent& operator=(CollisionComponent&& other) noexcept = delete;
		
		CollisionComponent();
		explicit CollisionComponent(int x, int y);
		virtual ~CollisionComponent() = default;

		iVector2 GetSize() const { return m_Size; }

		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(float x = 0, float y = 0, float z = 0);

		bool ShowCollisionBox(bool show) { return m_ShowCollisionBox = show; }
		bool ShowCollisionBox() const { return m_ShowCollisionBox; }

		bool GetHasCollision() const { return m_HasCollision; }
		void SetHasCollision(bool hasCollision) { m_HasCollision = hasCollision; }

		std::shared_ptr<CollisionComponent> GetCollision() const { return m_pOtherCollider; }
		void SetCollision(std::shared_ptr<CollisionComponent> pOtherCollider) { m_pOtherCollider = pOtherCollider; }


	protected:
		//virtual void Initialize() = 0;
		void Update(float& deltaTime) override;
		//virtual void Draw(float& deltaTime) = 0;

	private:
		iVector2 m_offSet = { 0,0 };
		iVector2 m_Size = { 0,0 };
		glm::vec3 m_Position {0};
		std::shared_ptr<TransformComponent> m_pTransformComponent{};
		bool m_ShowCollisionBox = false;
		std::shared_ptr<Texture2D> m_pCollisionBox{};

		std::shared_ptr<CollisionComponent>m_pOtherCollider{};

		bool m_HasCollision = false;
	};
}
