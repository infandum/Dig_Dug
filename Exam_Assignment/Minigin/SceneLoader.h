#pragma once
#include "Service.h"

namespace dae
{
	enum class SceneList
	{
		DEMO,
		LEVEL_1,
		LEVEL_2,
	};
	class GameObject;
	class Scene;
	class SceneLoader : public Service
	{
	public:
		void InitScene(SceneList scene);
		std::shared_ptr<GameObject> m_pPlayer{};
		std::shared_ptr<Scene> m_Scene{};
	};
}
