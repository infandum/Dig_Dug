#pragma once
#include "Components.h"

namespace dae
{
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

		int GetFramesPerSecond() const { return m_Fps; }

		static unsigned int GetTotalFrames() { return m_Frames; }

		void Update(float& deltaTime) override;	
	private:
		CompType m_Type = CompType::FPSCOMPONENT;
		int m_Fps = 0;
		int m_FpsCounter;
		float m_TotalTime;
	};
}