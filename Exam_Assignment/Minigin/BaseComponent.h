#pragma once
#include "DataStructs.h"

namespace dae
{
	class GameObject;

	class BaseComponent
	{
		friend class GameObject;
	public:
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) noexcept = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) noexcept = delete;
		BaseComponent() = default;
		virtual ~BaseComponent() = default;

		std::shared_ptr<GameObject> GetGameObject() const { return m_pGameObject; }
		CompType GetType() const { return m_Type; }

	protected:
		virtual void Initialize();
		virtual void Update(float& deltaTime);
		virtual void Draw(float& deltaTime);

		std::shared_ptr<GameObject> m_pGameObject{};
	private:
		CompType m_Type = CompType::BASECOMPONENT;
	};
}
