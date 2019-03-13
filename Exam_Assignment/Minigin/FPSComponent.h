#pragma once
#include "BaseComponent.h"
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

protected:
	void Initialize();
	void Update();
	void Draw();

private:
	float m_fps = 0;
};

