#pragma once
#include "BaseComponent.h"

namespace  dae
{
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

protected:
	void Initialize() override;
	void Update(float deltaTime) override;

	TextComponent* m_pTextComponent = nullptr;

	private:
		int m_Health = 0;
};
}


