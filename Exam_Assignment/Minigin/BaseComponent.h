#pragma once
#include "Observer.h"
#include "Subject.h"

namespace dae
{
	class GameObject;
	class BaseComponent : public Subject, public Observer
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

		void onNotify(GameObject& gameObject, NotifyEvent& event) override = 0;

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
