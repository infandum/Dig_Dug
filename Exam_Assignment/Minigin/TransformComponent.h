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

		TransformComponent() = default;
		explicit TransformComponent(float x , float y , float z = 0);
		virtual ~TransformComponent() = default;

		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(float x = 0, float y = 0, float z = 0);

		const glm::vec3& GetLocalPosition() const { return m_localPosition; }
		void SetLocalPosition(float x = 0, float y = 0, float z = 0) { m_localPosition = { x,y,z }; }
	
		const iVector2& GetPositionIndex() const { return m_CurrentTileIndex; }
		void SetPositionIndex(iVector2 index) { /*std::cout << index.x << "," << index.y << '\n';*/ m_CurrentTileIndex = index; }

		glm::vec3 GetVelocity() const { return m_Velocity; }
		void SetVelocity(glm::vec3 direction);

		void MoveToTile(unsigned int xIndex = 0, unsigned int yIndex = 0);

		Direction GetDirectionFromVelocity() const;
		iVector2 GetNextTileDirectionFromVelocity() const;

		Direction GetCurrentDirection() const { return m_CurrentDirection; }
		Direction GetPreviousDirection() const { return m_PreviousDirection; }

		bool GetIsStatic() const { return m_IsStatic; }
		void SetIsStatic(const bool isStatic) { m_IsStatic = isStatic; }

		bool GetIsOmniDirectional() const { return m_IsOmniDirectional; }
		void SetIsOmniDirectional(const bool isOmniDirectional) { m_IsOmniDirectional = isOmniDirectional; }

		bool IsCentered() const;

		bool CheckOccupiedTileMove();
		bool CheckTileSwapping();
		
	protected:
		
		static void BorderControl(double& posX, double& posY);

		void Initialize() override;
		void Update(float deltaTime) override;
		//void Render() override;

		glm::vec3 MoveDirectional();
		glm::vec3 MoveOmniDirectional();

	private:
		bool m_IsStatic = false;
		bool m_IsMoving = false;
		bool isSwappingTile = false;
		bool m_IsMoveAble = false;
		bool m_IsOmniDirectional = false;
		

		iVector2 m_CurrentTileIndex{};
		Direction m_CurrentDirection = Direction::RIGHT;
		Direction m_PreviousDirection = Direction::RIGHT;

		glm::vec3 m_Position = { 0,0,0 };
		glm::vec3 m_localPosition = { 0,0,0 };
		glm::vec3 m_Velocity = { 0,0,0 };

		

		bool isXonTileCenter = true;
		bool isYonTileCenter = true;
	};
}
