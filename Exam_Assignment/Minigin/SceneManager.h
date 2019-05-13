#pragma once
#include "Service.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Service
	{
	public:
		std::shared_ptr<Scene> CreateScene(const std::string& name);

		void NextScene();
		void PreviousScene();
		void SetActive(const std::string& sceneName);
		void SetActive(int index);

		std::shared_ptr<Scene> GetActiveScene() const { return m_spScenes[ActiveSceneIndex]; }
		std::shared_ptr<Scene> GetScene(std::string name);

		void Initialize();
		void Update(float deltaTime);
		void Render();

	private:
		std::vector<std::shared_ptr<Scene>> m_spScenes;
		int ActiveSceneIndex = 0;
	};

}
