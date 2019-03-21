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

		explicit TransformComponent(float x = 0, float y = 0, float z = 0) : m_Position(x, y, z) {};
		virtual ~TransformComponent() = default;

		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(float x = 0, float y = 0, float z = 0);

	protected:
		void Update(float& deltaTime) override;
		void Draw(float& deltaTime) override;

	private:
		CompType m_Type = TRANSFROMCOMPONENT;
		glm::vec3 m_Position;
	};
}
