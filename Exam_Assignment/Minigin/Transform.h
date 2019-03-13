#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)

namespace dae
{
	class Transform final
	{
		glm::vec3 mPosition;
	public:
		const glm::vec3& GetPosition() const { return mPosition; }
		void SetPosition(float x, float y, float z);
	};
}
