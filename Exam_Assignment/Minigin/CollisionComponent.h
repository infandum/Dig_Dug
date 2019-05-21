#pragma once
#include "BaseComponent.h"

namespace  dae
{ 
	class TransformComponent;
	class SpriteComponent;
	class TextureComponent;
	class CollisionComponent : public BaseComponent
	{
	public:
		CollisionComponent(const CollisionComponent& other) = delete;
		CollisionComponent(CollisionComponent&& other) noexcept = delete;
		CollisionComponent& operator=(const CollisionComponent& other) = delete;
		CollisionComponent& operator=(CollisionComponent&& other) noexcept = delete;
		
		CollisionComponent() = default;
		CollisionComponent(const bool& isTrigger) { m_Trigger = isTrigger; }
		explicit CollisionComponent(int x, int y, const bool& isTrigger = false);
		virtual ~CollisionComponent() = default;

		void SetSize(const iVector2& size) { m_CustomSize = true; m_Size = size; }
		iVector2 GetSize() const { return m_Size; }


		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(float x = 0, float y = 0, float z = 0);
		void SetPosition(const glm::vec3& pos = { 0, 0, 0 }) { SetPosition(pos.x, pos.y, pos.y); }

		bool ShowCollisionBox(bool show) { return m_ShowCollisionBox = show; }
		bool ShowCollisionBox() const { return m_ShowCollisionBox; }

		bool GetHasCollision() const { return m_HasCollision; }
		void SetHasCollision(bool hasCollision) { m_HasCollision = hasCollision; }

		CollisionComponent* GetCollision() const { return m_pOtherCollider; }
		void SetCollision(CollisionComponent* pOtherCollider) { m_pOtherCollider = pOtherCollider; }

		void EnableCollision(const bool& enable = true) { m_Collide = enable; }
		bool CanCollide() const { return m_Collide; }
		void EnableTrigger(const bool& enable = true) { m_Trigger = enable; }
		bool IsTrigger() const { return m_Trigger; }
		void EnablePushOut(const bool& enable) { m_PushOut = enable; }
		void Reset();

	protected:
		void Initialize() override;
		void Collision();
		void CollisionPosition();
		void Update(float deltaTime) override;
		//void Render() override;

	private:
		iVector2 m_offSet = { 0,0 };
		iVector2 m_Size = { 0,0 };
		glm::vec3 m_Position {0};

		TransformComponent* m_pTransformComponent = nullptr;
		SpriteComponent* m_pSpriteComponent = nullptr;
		TextureComponent* m_pTextureComponent = nullptr;

		bool m_ShowCollisionBox = false;
		bool m_Collide = true;
		bool m_PushOut = false;
		bool m_Trigger = false;
		std::shared_ptr<Texture2D> m_pCollisionBox = nullptr;

		CollisionComponent* m_pOtherCollider = nullptr;

		bool m_HasCollision = false;
		bool m_CustomSize = false;
	};
}
