#pragma once

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

	protected:
		//virtual void Initialize() = 0;
		virtual void Update(float& deltaTime) = 0;
		//virtual void Draw(float& deltaTime) = 0;

		std::shared_ptr<GameObject> m_pGameObject{};
	};
}
