#pragma once
#include "BaseComponent.h"

namespace  dae
{
	class ResourceManager;
	class HealthDisplayComponent : public BaseComponent
	{		
	public:

		HealthDisplayComponent(const HealthDisplayComponent& other) = delete;
		HealthDisplayComponent(HealthDisplayComponent&& other) noexcept = delete;
		HealthDisplayComponent& operator=(const HealthDisplayComponent& other) = delete;
		HealthDisplayComponent& operator=(HealthDisplayComponent&& other) noexcept = delete;
		HealthDisplayComponent() = default;
		virtual ~HealthDisplayComponent() = default;


		void onNotify(GameObject& gameObject, NotifyEvent& event) override;
		void AddDisplay();

	protected:
		void Initialize() override;
		void Update(float deltaTime) override;

		

	private:
		TextComponent* m_pTextComponent;
		int m_Health;

		ResourceManager* m_Resource = nullptr;
	};
}


