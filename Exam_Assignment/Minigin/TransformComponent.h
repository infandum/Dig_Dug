#pragma once
#include "Components.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)

namespace dae
{
	enum class Direction
	{
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

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

		glm::vec3 GetDirection() const { return m_Direction; }
		void SetDirection(glm::vec3 & direction) { m_Direction = direction; }

		bool MoveToTile(unsigned int x = 0, unsigned int y = 0);
		bool isMoving = false;

		/*void Initialize() override;*/
		void Update(float& deltaTime) override;
		/*void Draw(float& deltaTime) override;*/

	private:
		glm::vec3 m_Position;
		glm::vec3 m_OffSet;
		glm::vec3 m_Direction;

		float m_Speed = 0.05f;
	};
}
