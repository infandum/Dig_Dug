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

		//TransformComponent() = default;
		TransformComponent(float x = 0.0f, float y = 0.0f, float z = 0.0f);
		virtual ~TransformComponent() = default;

		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(float x = 0, float y = 0, float z = 0);
		void SetPosition(const glm::vec3& pos = {0, 0, 0}) { SetLocalPosition(pos.x, pos.y, pos.y); }

		const glm::vec3& GetLocalPosition() const { return m_localPosition; }
		void SetLocalPosition(float x = 0, float y = 0, float z = 0) { m_localPosition = { x,y,z }; }
		void SetLocalPosition(const glm::vec3& offset = { 0, 0, 0 }) { SetLocalPosition(offset.x, offset.y, offset.y); }
	
		const iVector2& GetPositionIndex() const { return m_CurrentTileIndex; }
		void SetPositionIndex(iVector2 index) {/* std::cout << "SET TILE: " << m_CurrentTileIndex.x << " , " << m_CurrentTileIndex.y << "\n";*/ m_CurrentTileIndex = index; }
		
	protected:
		void Initialize() override;
		void Update(float deltaTime) override;

	private:
		iVector2 m_CurrentTileIndex{};

		glm::vec3 m_InitPosition = { 0,0,0 };
		glm::vec3 m_Position = { 0,0,0 };
		glm::vec3 m_localPosition = { 0,0,0 };
		

		

		
	};
}
