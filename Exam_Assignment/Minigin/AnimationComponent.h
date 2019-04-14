#pragma once
#include "BaseComponent.h"

namespace dae
{
	class AnimationComponent : public BaseComponent
	{
	public:
		AnimationComponent(const AnimationComponent& other) = delete;
		AnimationComponent(AnimationComponent&& other) noexcept = delete;
		AnimationComponent& operator=(const AnimationComponent& other) = delete;
		AnimationComponent& operator=(AnimationComponent&& other) noexcept = delete;
		AnimationComponent() = default;
		virtual ~AnimationComponent() = default;

	protected:
		//virtual void Initialize() = 0;
		void Update(float& deltaTime) override;
		//virtual void Draw(float& deltaTime) = 0;
	};

}