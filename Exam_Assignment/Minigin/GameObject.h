#pragma once
#include "SceneObject.h"
#include "Components.h"
#include <typeinfo>

namespace dae
{
	static unsigned int m_NumberOfGameObjects{0};
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

		void SetName(std::string& name);
		std::string GetName() const { return m_Name; }

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
		std::string m_Name = "GameObject" + std::to_string(m_NumberOfGameObjects);
		std::vector<BaseComponent*> m_pComponents{};
		TransformComponent* m_pTransformComponent;
		TextureComponent* m_pTextureComponent;
	};
}
