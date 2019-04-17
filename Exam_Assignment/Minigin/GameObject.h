#pragma once
#include "SceneObject.h"
#include "Components.h"
#include <typeinfo>

namespace dae
{
	class GameObject final : public SceneObject
	{
	public:
		GameObject();
		virtual ~GameObject() = default;

		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void Update(float deltaTime) override;
		void Render() const override;

		static unsigned int GetObjectCount() { return m_NumberOfGameObjects; }

		void SetName(std::string name);
		std::string GetName() const { return m_Name; }

		std::shared_ptr<TransformComponent> GetTransform() const { return m_pTransformComponent; }
		std::shared_ptr<TextureComponent> GetTexture() const { return m_pTextureComponent; }
		std::shared_ptr<CollisionComponent> GetCollision() const { return m_pCollisionComponent; }
		std::shared_ptr<TileComponent> GetTile() const { return m_pTileComponent; }
		std::shared_ptr<SpriteComponent> GetSprite() const { return m_pSpriteComponent; }

		void AddComponent(std::shared_ptr<BaseComponent> comp);
		void RemoveComponent(std::shared_ptr<BaseComponent> pComp);

		template <class T>
		std::shared_ptr<T> GetComponent()
		{
			for (auto& component : m_pComponents)
				if (component && typeid(*component.get()) == typeid(T))
				{
					return std::static_pointer_cast<T>(component);
				}
			return nullptr;
		}

	private:
		std::string m_Name = "GameObject" + std::to_string(m_NumberOfGameObjects);
		std::vector<std::shared_ptr<BaseComponent>> m_pComponents{};
		std::shared_ptr<TransformComponent> m_pTransformComponent{};
		std::shared_ptr<TextureComponent> m_pTextureComponent{};
		std::shared_ptr<CollisionComponent> m_pCollisionComponent{};
		std::shared_ptr<TileComponent> m_pTileComponent{};
		std::shared_ptr<SpriteComponent> m_pSpriteComponent{};
		static unsigned int m_NumberOfGameObjects;
	};
}
