#pragma once
#include "BaseComponent.h"
#include "States.h"

namespace dae
{
	class SpriteComponent : public BaseComponent
	{
	public:
		SpriteComponent(const SpriteComponent& other) = delete;
		SpriteComponent(SpriteComponent&& other) noexcept = delete;
		SpriteComponent& operator=(const SpriteComponent& other) = delete;
		SpriteComponent& operator=(SpriteComponent&& other) noexcept = delete;

		SpriteComponent() = default;
		virtual ~SpriteComponent() = default;

		void Swap();

	protected:
		/*void Initialize() override;*/
		void Update(float& deltaTime) override;
		/*void Draw(float& deltaTime) override;*/
	private:
		std::shared_ptr<BaseState> m_DirState = std::make_shared<RightState>();
	};
}
