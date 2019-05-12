#pragma once
#include "BaseComponent.h"

namespace dae
{
	class StateComponent : public BaseComponent
	{
	public:
		StateComponent(const StateComponent& other) = delete;
		StateComponent(StateComponent&& other) noexcept = delete;
		StateComponent& operator=(const StateComponent& other) = delete;
		StateComponent& operator=(StateComponent&& other) noexcept = delete;
		StateComponent() = default;
		virtual ~StateComponent() = default;

	protected:
		void Initialize() override;
		void Update(float deltaTime) override;
		//void Render() override;
	};
}