#pragma once
#include "BaseComponent.h"

namespace dae
{
	class NpcComponent : public BaseComponent
	{
	public:
		NpcComponent(const BaseComponent& other) = delete;
		NpcComponent(BaseComponent&& other) noexcept = delete;
		NpcComponent& operator=(const BaseComponent& other) = delete;
		NpcComponent& operator=(BaseComponent&& other) noexcept = delete;
		NpcComponent();
		virtual ~NpcComponent() = default;

	protected:
		void Initialize() override;
		void Update(float deltaTime) override;
		//void Render() override;
	};
}
