#include "MiniginPCH.h"
#include "Components.h"
#include "GameObject.h"

void dae::FPSComponent::Update(float& deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	
	m_TotalTime += deltaTime;
	m_Frames++;
	m_FpsCounter++;

	if (m_TotalTime >= 1000.0f)
	{
		m_Fps = m_FpsCounter;
		m_FpsCounter = 0;
		m_TotalTime = 0;
	}
	if (GetGameObject())
	{
		const auto txt = std::to_string(static_cast<int>(m_Fps)) + "FPS";
		if (GetGameObject()->GetComponent<TextComponent>())
			GetGameObject()->GetComponent<TextComponent>()->SetText(txt);
	}
}