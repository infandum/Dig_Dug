#include "MiniginPCH.h"
#include "FPSComponent.h"
//#include "GameObject.h"
#include "TextObject.h"


void dae::FPSComponent::Update(float& deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	m_Frames++;
	m_fps = (m_Frames / deltaTime);

#if _DEBUG
	std::cout << "  frames: " << m_Frames << "  // deltaTime: " << deltaTime << "  // fps: " << m_fps << std::endl;
#endif
	if (GetTextObject())
	{
		const auto txt = std::to_string(static_cast<int>(m_fps)) + "FPS";
		GetTextObject()->SetText(txt);
	}
}

void dae::FPSComponent::Draw(float& deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}


