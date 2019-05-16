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

		bool CheckOccupiedTileMove() const;
		bool CheckTileSwapping();

		void Reset(float x, float y, Direction dir = Direction::RIGHT);
		void Reset(glm::vec3  pos, Direction dir = Direction::RIGHT);


		float GetMoveSpeed() const { return m_MoveSpeed; }
	protected:
		void Initialize() override;
		void Update(float deltaTime) override;
		//void Render() override;

		void BorderControl(double& posX, double& posY) const;
		glm::vec3 MoveDirectional();
		glm::vec3 MoveOmniDirectional();

	private:
		float m_MoveSpeed = 90.f;
		TransformComponent* m_pTransform;
		LevelManager* m_pLevelManager;
		bool m_IsStatic = false;
		bool m_IsMoving = false;
		bool isSwappingTile = false;
		bool m_IsOmniDirectional = false;

		glm::vec3 m_Velocity = { 0,0,0 };
		//glm::vec3 m_Position = { 0,0,0 };

		Direction m_CurrentDirection = Direction::RIGHT;
		Direction m_PreviousDirection = Direction::RIGHT;


		bool isXonTileCenter = true;
		bool isYonTileCenter = true;
	};
}
