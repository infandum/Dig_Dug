#pragma once
#include "Components.h"

namespace dae
{
	class RenderComponent : public BaseComponent
	{
		friend class GameObject;
	public:
		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) noexcept = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) noexcept = delete;
		RenderComponent() = default;
		virtual ~RenderComponent() = default;

		void EnableRender(const bool& enable = true) { m_Render = enable; }

	protected:
		void Initialize() override;
		void Update(float deltaTime) override;
		void Render() const;

	private:
		TextureComponent* m_pTextureComponent = nullptr;
		TransformComponent* m_pTransformComponent = nullptr;
		CollisionComponent* m_pCollisionComponent = nullptr;
		TileComponent* m_pTileComponent = nullptr;
		SpriteComponent* m_pSpriteComponent = nullptr;

		bool m_Render = true;
	};


}