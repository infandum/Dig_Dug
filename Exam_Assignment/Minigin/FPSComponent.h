#pragma once
#include "BaseComponent.h"
class FPSComponent : public BaseComponent
{
public:
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

