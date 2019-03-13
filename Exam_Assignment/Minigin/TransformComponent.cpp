#include "MiniginPCH.h"
#include "TransformComponent.h"

void TransformComponent::SetPosition(float x, float y, float z)
{
	mPosition = glm::vec3(x, y, z);
}
