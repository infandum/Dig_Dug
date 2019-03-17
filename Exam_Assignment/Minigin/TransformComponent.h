#pragma once
#include "Components.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)

namespace dae
{
	class TransformComponent final : public BaseComponent
	{
	public:
		TransformComponent(const TransformComponent& other) = delete;
		TransformComponent(TransformComponent&& other) noexcept = delete;
		TransformComponent& operator=(const TransformComponent& other) = delete;
		TransformComponent& operator=(TransformComponent&& other) noexcept = delete;
		TransformComponent(float x = 0, float y = 0, float z = 0) : mPosition(x, y, z) {};
		virtual ~TransformComponent() = default;

		void Update(float deltaTime) override;
		void Draw(float deltaTime) override;

		const glm::vec3& GetPosition() const { return mPosition; }
		void SetPosition(float x = 0, float y = 0, float z = 0);

	private:
		glm::vec3 mPosition;
	};
}
