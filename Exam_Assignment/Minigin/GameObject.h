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

		void Initialize() override;
		void Update(float deltaTime) override;
		void Render() const override;

		static UINT GetObjectCount() { return m_NumberOfGameObjects; }

		void SetName(std::string name);
		std::string GetName() const { return m_Name; }

		TransformComponent*  GetTransform() { return GetComponent<TransformComponent>().get(); }
		TextureComponent* GetTexture() { return GetComponent<TextureComponent>().get(); }
		CollisionComponent* GetCollision() { return GetComponent<CollisionComponent>().get(); }
		RenderComponent* GetRenderer() { return GetComponent<RenderComponent>().get(); }
		SpriteComponent* GetSprite() { return GetComponent<SpriteComponent>().get(); }
		InputComponent* GetInput() { return GetComponent<InputComponent>().get(); }


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

		void SetScene(int index) { m_SceneIndex = index; }
		size_t GetScene() const { return  m_SceneIndex; }

		//TODO: RELEASE CHILD OBJECT HIERACHY

		GameObject* GetParent() const { return m_pParent; }
		void SetParent(GameObject* parent) { m_pParent = parent; }

		//TODO: ACTIVE LAST FRAME FIX? MAYBE JUST REMOVE THE ACTIVE PART
		bool IsEnabled() const { return m_IsActive; }
		void Enable(bool isActive) { m_IsActive = isActive; }
		void SetIsFollowParent(bool isFollow);
		bool GetIsFollowingParent() const { return m_IsFollowing; }

	private:
		std::string m_Name = "GameObject" + std::to_string(m_NumberOfGameObjects);
		std::vector<std::shared_ptr<BaseComponent>> m_pComponents{};
		std::vector<std::shared_ptr<GameObject>> m_pChilds{};

		GameObject* m_pParent {};

		std::shared_ptr<RenderComponent> m_pRenderComponent{};

		static UINT m_NumberOfGameObjects;
		bool m_IsActive = true;
		bool m_IsActiveLastFrame = true;
		bool m_IsFollowing = true;
		size_t m_SceneIndex = 0;
	};
}
