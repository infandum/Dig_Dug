#include "MiniginPCH.h"
#include "Components.h"
#include "GameObject.h"

void dae::FPSComponent::Update(float& deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	m_Frames++;
	m_Fps = (1.0f / deltaTime) * 1000.0f;

	if (GetGameObject())
	{
		const auto txt = std::to_string(m_Fps) + "FPS";
		if (GetGameObject()->GetComponent<TextComponent>())
			GetGameObject()->GetComponent<TextComponent>()->SetText(txt);
	}
}
