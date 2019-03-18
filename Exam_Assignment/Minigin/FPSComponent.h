#pragma once
#include "Components.h"

namespace dae
{
	class GameObject;
	class TextObject;

	static unsigned int m_Frames;

	class FPSComponent : public BaseComponent
	{
		
	public:
		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) noexcept = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) noexcept = delete;
		FPSComponent() = default;
		virtual ~FPSComponent() = default;

		float GetFramesPerSecond() const { return m_fps; }

		void Update(float& deltaTime) override;
		void Draw(float& deltaTime) override;
	protected:
		
	private:
		float m_fps = 0;
		
	};
}