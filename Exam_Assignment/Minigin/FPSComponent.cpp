#include "MiniginPCH.h"
#include "Components.h"
#include "GameObject.h"

void dae::FPSComponent::Update(float& deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	m_Frames++;
	m_Fps = (1.0f / deltaTime);
	m_AccuTime += deltaTime;
	if (GetGameObject())
	{
		const auto txt = std::to_string(static_cast<int>(round(m_Fps))) + "FPS";
		//std::cout << std::to_string(static_cast<int>(m_Fps)) << "FPS\n";
		if (GetGameObject()->GetComponent<TextComponent>())
			GetGameObject()->GetComponent<TextComponent>()->SetText(txt);
	}
}