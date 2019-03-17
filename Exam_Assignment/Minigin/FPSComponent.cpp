#include "MiniginPCH.h"
#include "FPSComponent.h"

dae::FPSComponent::FPSComponent()
{

}

void dae::FPSComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	m_fps = 1 / (deltaTime);
	std::cout << m_fps << std::endl;
}

void dae::FPSComponent::Draw(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}


