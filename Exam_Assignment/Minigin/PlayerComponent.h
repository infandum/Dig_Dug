#pragma once
#include "InputComponent.h"

namespace dae
{
	class PlayerComponent final : public InputComponent
	{
	public:

		PlayerComponent(const PlayerComponent& other) = delete;
		PlayerComponent(PlayerComponent&& other) noexcept = delete;
		PlayerComponent& operator=(const PlayerComponent& other) = delete;
		PlayerComponent& operator=(PlayerComponent&& other) noexcept = delete;

		PlayerComponent();
		virtual ~PlayerComponent() = default;

	protected:
		void Initialize() override;
		void Update(float deltaTime) override;
		//void Render() override;
	};

}