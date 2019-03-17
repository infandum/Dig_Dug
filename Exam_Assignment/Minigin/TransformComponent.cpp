#include "MiniginPCH.h"
#include "TransformComponent.h"

void dae::TransformComponent::Update(float& deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

void dae::TransformComponent::Draw(float& deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

void dae::TransformComponent::SetPosition(float x, float y, float z)
{
	mPosition = glm::vec3(x, y, z);
}
