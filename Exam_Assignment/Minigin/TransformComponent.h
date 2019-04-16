#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)
#include "BaseComponent.h"

namespace dae
{


	class TransformComponent final : public BaseComponent
	{
	public:
		TransformComponent(const TransformComponent& other) = delete;
		TransformComponent(TransformComponent&& other) noexcept = delete;
		TransformComponent& operator=(const TransformComponent& other) = delete;
		TransformComponent& operator=(TransformComponent&& other) noexcept = delete;

		TransformComponent();
		explicit TransformComponent(float x , float y , float z = 0);
		virtual ~TransformComponent() = default;

		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(float x = 0, float y = 0, float z = 0);
	
		const iVector2& GetPositionIndex() const { return m_CurrentTileIndex; }
		void SetPositionIndex(iVector2 index) { std::cout << index.x << "," << index.y << '\n'; m_CurrentTileIndex = index; }

		glm::vec3 GetVelocity() const { return m_Velocity; }
		void SetVelocity(glm::vec3 direction) { m_Velocity = direction; if(GetDirectionFromVelocity() != Direction::NONE) m_CurrentDirection = GetDirectionFromVelocity(); }

		Direction GetDirectionFromVelocity() const;
		iVector2 GetNextTileDirectionFromVelocity() const;
		Direction GetCurrentDirection() const { return m_CurrentDirection; }

		bool GetIsStatic() const { return m_IsStatic; }
		void SetIsStatic(const bool isStatic) { m_IsStatic = isStatic; }

		bool IsCentered() const;

		glm::vec3 MoveToTile(unsigned int x = 0, unsigned int y = 0, bool canDig = false);
		
	protected:
		/*void Initialize() override;*/
		void Update(float& deltaTime) override;
		/*void Draw(float& deltaTime) override;*/
		glm::vec3 MoveDirection();

	private:
		bool m_IsMoving = false;
		bool m_IsStatic = false;

		iVector2 m_CurrentTileIndex{};
		Direction m_CurrentDirection = Direction::NONE;

		glm::vec3 m_Position {};
		glm::vec3 m_OffSet {};
		glm::vec3 m_Velocity {};



		

		bool isXonTileCenter = true;
		bool isYonTileCenter = true;
	};
}
