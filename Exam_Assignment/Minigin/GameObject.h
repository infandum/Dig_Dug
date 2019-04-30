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

		static UINT GetObjectCount() { return m_NumberOfGameObjects; }

		void SetName(std::string name);
		std::string GetName() const { return m_Name; }

		std::shared_ptr<TransformComponent> GetTransform() const { return m_pTransformComponent; }
		std::shared_ptr<TextureComponent> GetTexture() const { return m_pTextureComponent; }
		std::shared_ptr<CollisionComponent> GetCollision() const { return m_pCollisionComponent; }
		std::shared_ptr<TileComponent> GetTile() const { return m_pTileComponent; }
		std::shared_ptr<SpriteComponent> GetSprite() const { return m_pSpriteComponent; }
		std::shared_ptr<InputComponent> GetInput() const { return m_pInputComponent; }
		std::shared_ptr<NpcComponent> GetNPC() const { return m_pNpcComponent; }

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

		void AddChild(std::shared_ptr<GameObject> pChild, bool isActive = true, bool isAttached = true);
		void RemoveChild(std::shared_ptr<GameObject> pChild);
		bool IsChild(GameObject* pChild);
		std::shared_ptr<GameObject> GetChild(UINT index);
		UINT GetChildCount() const { return static_cast<UINT>(m_pChilds.size()); }
		void DetachChild(GameObject* pChild);
		void AttachChild(GameObject* pChild);
		bool IsChildAttached(GameObject* pChild);
		void ActivateChild(GameObject* pChild);
		void DeactivateChild(GameObject* pChild);
		bool IsChildActive(GameObject* pChild);
		//TODO: RELEASE CHILD OBJECT HIERACHY

		GameObject* GetParent() const { return m_pParent; }
		void SetParent(GameObject* parent) { m_pParent = parent; }

	private:
		std::string m_Name = "GameObject" + std::to_string(m_NumberOfGameObjects);
		std::vector<std::shared_ptr<BaseComponent>> m_pComponents{};
		std::vector<std::shared_ptr<GameObject>> m_pChilds{};
		std::vector<bool> m_IsChildAttached {};
		std::vector<bool> m_IsChildActive{};
		GameObject* m_pParent {};
		std::shared_ptr<TransformComponent> m_pTransformComponent{};
		std::shared_ptr<TextureComponent> m_pTextureComponent{};
		std::shared_ptr<CollisionComponent> m_pCollisionComponent{};
		std::shared_ptr<TileComponent> m_pTileComponent{};
		std::shared_ptr<SpriteComponent> m_pSpriteComponent{};
		std::shared_ptr<InputComponent> m_pInputComponent{};
		std::shared_ptr<NpcComponent> m_pNpcComponent{};
		static UINT m_NumberOfGameObjects;
	};
}
