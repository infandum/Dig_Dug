#include "MiniginPCH.h"
#include "Components.h"
#include "GameObject.h"
#include <iomanip>

void dae::FPSComponent::Initialize()
{
}

void dae::FPSComponent::Update(float deltaTime)
{
	m_Frames++;
	m_Fps = (1.0f / deltaTime);
	m_AccuTime += deltaTime;
	if (GetGameObject() && m_AccuTime >= 1.0f)
	{
		std::stringstream stream;
		stream << std::fixed << std::setprecision(1) << m_Fps << " FPS";
		const auto txt = stream.str();
		if (GetGameObject()->GetComponent<TextComponent>())
			GetGameObject()->GetComponent<TextComponent>()->SetText(txt);
		m_AccuTime -= 1.0f;
	}
}