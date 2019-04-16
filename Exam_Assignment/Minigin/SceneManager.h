#pragma once
#include "Service.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Service
	{
	public:
		std::shared_ptr<Scene> CreateScene(const std::string& name);

		/*void AddScene(std::shared_ptr<Scene> pScene);
		void NextScene();
		void PreviousScene();
		void SetActive(const std::string& sceneName);
		std::shared_ptr<Scene> GetActiveScene() const { return m_spCurrentScene; }*/

		void Update(float deltaTime);
		void Render();

	private:
		std::vector<std::shared_ptr<Scene>> m_spScenes;
		int ActiveSceneIndex = 0;
		/*std::shared_ptr<Scene> m_spCurrentScene, m_spNextScene;*/
	};

}
