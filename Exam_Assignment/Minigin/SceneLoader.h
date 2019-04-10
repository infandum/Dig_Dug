#pragma once
#include "Singleton.h"

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
	class SceneLoader : public Singleton<SceneLoader>
	{
	public:
		void InitScene(dae::SceneList scene);
		/*void AddGameObject(const std::string & tex, const Vec2 pos);
		void AddFPSObject(const Vec2 pos, const std::string & fontname);
		void AddTextGameObject(const std::string & text, const std::string & fontname, const int fontsize, const Vec2 pos);
		void AddControllableGameObject(const std::string & tex, const Vec2 pos);*/
		std::shared_ptr<GameObject> m_pPlayer{};
		std::shared_ptr<Scene> m_Scene;
	};
}
