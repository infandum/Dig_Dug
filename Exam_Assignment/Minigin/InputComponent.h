#pragma once
#include "BaseComponent.h"
#include <SDL.h>


namespace dae {
	enum class KeyBord
	{
		
	};
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
		void KeyDown(SDL_Keycode key) const;
		void KeyUp(SDL_Keycode key) const;

		/*void Initialize() override;*/
		void Update(float& deltaTime) override;
		/*void Draw(float& deltaTime) override;*/
	private:
		TransformComponent* m_TransformComponent{};
		SDL_Event m_Event;
	};

}
