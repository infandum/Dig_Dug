#pragma once
#include "BaseComponent.h"

class TransformComponent final : public BaseComponent
{
public:
	TransformComponent(const TransformComponent& other) = delete;
	TransformComponent(TransformComponent&& other) noexcept = delete;
	TransformComponent& operator=(const TransformComponent& other) = delete;
	TransformComponent& operator=(TransformComponent&& other) noexcept = delete;
	TransformComponent() = default;
	virtual ~TransformComponent() = default;

	glm::vec3 mPosition;
public:
	const glm::vec3& GetPosition() const { return mPosition; }
	void SetPosition(float x, float y, float z);
};

