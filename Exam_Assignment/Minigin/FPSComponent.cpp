#include "MiniginPCH.h"
#include "FPSComponent.h"

dae::FPSComponent::FPSComponent()
{

}

void dae::FPSComponent::Update(float& deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	m_Frames++;
	m_fps = (m_Frames / deltaTime);
	std::cout << "  frames: " << m_Frames << "  // deltaTime: " << deltaTime << "  // fps: " << m_fps << std::endl;
}

void dae::FPSComponent::Draw(float& deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}


