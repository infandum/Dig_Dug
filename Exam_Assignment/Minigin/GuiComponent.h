#pragma once
#include "BaseComponent.h"

namespace  dae
{
	class GuiComponent : public BaseComponent
{
public:

	GuiComponent(const GuiComponent& other) = delete;
	GuiComponent(GuiComponent&& other) noexcept = delete;
	GuiComponent& operator=(const GuiComponent& other) = delete;
	GuiComponent& operator=(GuiComponent&& other) noexcept = delete;
	GuiComponent() = default;
	virtual ~GuiComponent() = default;


	void onNotify(GameObject& gameObject, NotifyEvent& event) override;

protected:
	void Initialize() override;
	void Update(float deltaTime) override;
};
}


