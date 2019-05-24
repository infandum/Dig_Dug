#pragma once
#include "BaseComponent.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#include "LevelManager.h"
#pragma warning(pop)

namespace dae
{
	class TransformComponent;
	class MoveComponent final : public BaseComponent
	{
	public:
		MoveComponent(const MoveComponent& other) = delete;
		MoveComponent(MoveComponent&& other) noexcept = delete;
		MoveComponent& operator=(const MoveComponent& other) = delete;
		MoveComponent& operator=(MoveComponent&& other) noexcept = delete;
		MoveComponent() = default;
		virtual ~MoveComponent() = default;

		void SetMovementInput(float x, float y, float z = 0);
		void SetMovementInput(glm::vec3 direction);

		glm::vec3 GetVelocity() const { return m_Velocity; }
		void SetVelocity(glm::vec3 direction);

		void MoveToTile(iVector2 vec2);
		void MoveToTile(unsigned int xIndex = 0, unsigned int yIndex = 0);

		Direction GetDirectionFromVelocity() const;

		void FlipDirection();
		void SetCurrentDirection(const Direction& dir) { m_PreviousDirection = m_CurrentDirection;  m_CurrentDirection = dir; }
		Direction GetCurrentDirection() const { return m_CurrentDirection; }
		Direction GetPreviousDirection() const { return m_PreviousDirection; }

		bool GetIsStatic() const { return m_IsStatic; }
		void SetIsStatic(const bool isStatic) { m_IsStatic = isStatic; }

		bool GetIsOmniDirectional() const { return m_IsOmniDirectional; }
		void SetIsOmniDirectional(const bool isOmniDirectional) { m_IsOmniDirectional = isOmniDirectional; }

		bool IsCentered() const;

		bool CheckOccupiedTileMove() const;
		bool CheckTileSwapping();

		void Reset(Direction dir = Direction::RIGHT);


		float GetMoveSpeed() const { return m_MoveSpeed; }
		void SetMoveCenteringPaddiding(const float& padding) { m_MovePadding = padding; }
		float GetMoveCenteringPadding() const { return m_MovePadding; }

		void onNotify(GameObject& gameObject, NotifyEvent& event) override;

	protected:
		void Initialize() override;
		void Update(float deltaTime) override;
		//void Render() override;

		void BorderControl(double& posX, double& posY) const;
		glm::vec3 MoveDirectional();
		glm::vec3 MoveOmniDirectional();

	private:
		float m_MoveSpeed = 90.f;
		float m_MovePadding = 1.0f;

		TransformComponent* m_pTransform;
		LevelManager* m_pLevelManager;

		bool m_IsStatic = false;
		bool m_IsMoving = false;
		bool isSwappingTile = false;
		bool m_IsOmniDirectional = false;

		glm::vec3 m_Velocity = { 0,0,0 };

		Direction m_CurrentDirection = Direction::RIGHT;
		Direction m_PreviousDirection = Direction::RIGHT;


		bool isXonTileCenter = true;
		bool isYonTileCenter = true;
	};
}
