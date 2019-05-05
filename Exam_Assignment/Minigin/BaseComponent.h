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

		GameObject* GetGameObject() const { return m_pGameObject; }

	protected:
		//TODO: GO OVERALL COMPONENT AND DECOUPLE AND CLEAN UP
		//TODO: INIT 
		//TODO: REMOVE RENDER
		virtual void Initialize() = 0;
		virtual void Update(float deltaTime) = 0;
		//virtual void Render() = 0;

		GameObject*  m_pGameObject{};
	};
}
