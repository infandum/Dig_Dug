#pragma once
#include "BaseComponent.h"

namespace dae
{
	class FPSComponent : public BaseComponent
	{
	public:
		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) noexcept = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) noexcept = delete;
		FPSComponent();
		virtual ~FPSComponent() = default;

		float GetFramesPerSecond() const { return m_fps; }

		void Update(float deltaTime) override;
		void Draw(float deltaTime) override;
	protected:

	private:
		float m_fps = 0;
	};
}