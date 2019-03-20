#pragma once
#include <memory>
#include <typeinfo>

#include "Transform.h"
#include "Texture2D.h"

#include "SceneObject.h"
#include "Components.h"

namespace dae
{
	class GameObject final : public SceneObject
	{
	public:
		GameObject() = default;
		virtual ~GameObject() = default;
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void Update(float deltaTime) override;
		void Render() const override;

		void SetTexture(const std::string& filename);
		void SetTexture(std::shared_ptr<Texture2D> texture);
		void SetPosition(float x, float y);

		void AddComponent(BaseComponent* comp);
		void RemoveComponent(BaseComponent* pComp);

		template <class T>
		T* GetComponent()
		{
			const auto& ti = typeid(T);
			for (auto &component : m_pComponents)
			{		
				if (component && typeid(*component) == ti)
					return static_cast<T*>(component);
			}
			return nullptr;
		}		
	private:
		Transform mTransform;
		std::shared_ptr<Texture2D> mTexture{};
		std::string mName = "GameObject";
		std::vector<BaseComponent*> m_pComponents{};
	};
}
