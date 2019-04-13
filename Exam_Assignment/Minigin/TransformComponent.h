#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)
#include "BaseComponent.h"

namespace dae
{
	enum class Direction
	{
		UP		= 0,
		DOWN	= 1,
		LEFT	= 2,
		RIGHT	= 3
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

		glm::vec3 GetVelocity() const { return m_Velocity; }
		void SetVelocity(glm::vec3 direction) { m_Velocity = direction; }

		bool GetIsStatic() const { return m_IsStatic; }
		void SetIsStatic(bool isStatic) { m_IsStatic = isStatic; }

		bool IsCentered() const { return isXonTileCenter && isYonTileCenter; }
		
		glm::vec3 MoveToTile(unsigned int x = 0, unsigned int y = 0, bool canDig = false);
		
		glm::vec3 MoveDirection();

		Direction DirectionFromVelocity() const;
		
	protected:
		/*void Initialize() override;*/
		void Update(float& deltaTime) override;
		/*void Draw(float& deltaTime) override;*/	

	private:
		bool m_IsMoving = false;
		bool m_IsStatic = true;
		glm::vec3 m_Position;
		glm::vec3 m_OffSet;
		glm::vec3 m_Velocity;

		bool isXonTileCenter = true;
		bool isYonTileCenter = true;

		float m_Speed = 0.05f;
	};
}
