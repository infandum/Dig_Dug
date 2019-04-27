#pragma once
#include "BaseComponent.h"
#include <SDL.h>


namespace dae {
	class TransformComponent;
	class InputComponent final : public BaseComponent
	{
	public:
		InputComponent(const InputComponent& other) = delete;
		InputComponent(InputComponent&& other) noexcept = delete;
		InputComponent& operator=(const InputComponent& other) = delete;
		InputComponent& operator=(InputComponent&& other) noexcept = delete;
		InputComponent() = default;
		virtual ~InputComponent() = default;

	protected:
		/*void Initialize() override;*/
		void Update(float& deltaTime) override;
		/*void Draw(float& deltaTime) override;*/
	};

}
