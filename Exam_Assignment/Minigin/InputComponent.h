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

		void onNotify(NotifyEvent event);

	protected:
		/*void Initialize() override;*/
		void Update(float& deltaTime) override;
		/*void Draw(float& deltaTime) override;*/

	private:
		std::shared_ptr<TransformComponent> m_TransformComponent{};
		/*SDL_Event m_Event{};*/
	};

}
