#include "MiniginPCH.h"
#include "FPSComponent.h"
#include "GameObject.h"
#include "TextObject.h"


dae::FPSComponent::FPSComponent()
= default;

void dae::FPSComponent::Update(float& deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	m_Frames++;
	m_TotalTime += deltaTime;

	m_FpsCounter++;

	if (m_TotalTime >= 1000.0f)
	{
		m_Fps = m_FpsCounter;
		m_FpsCounter = 0;
		m_TotalTime = 0;
	}

#if _DEBUG
	std::cout << "frames: " << m_Frames << "  // deltaTime: " << deltaTime << "  // fps: " << m_Fps << std::endl;
#endif
	if (GetGameObject())
	{
		const auto txt = std::to_string(static_cast<int>(m_Fps)) + "FPS";
		if (GetGameObject()->GetComponent<TextComponent>())
			GetGameObject()->GetComponent<TextComponent>()->SetText(txt);
		else
#if _DEBUG
			std::cout << "FPSComponent> No TextComponent found; Please add new TextComponent!0" << m_Fps << std::endl;
#endif
	}
}