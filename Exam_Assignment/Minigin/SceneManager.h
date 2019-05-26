#pragma once

namespace dae
{
	class Scene;
	class SceneManager final
	{
	public:
		std::shared_ptr<Scene> CreateScene(const std::string& name);

		void NextScene();
		void PreviousScene();
		void SetActive(const std::string& sceneName);
		void SetActive(const int& index);

		std::shared_ptr<Scene> GetActiveScene() const { return m_spScenes[ActiveSceneIndex]; }
		std::shared_ptr<Scene> GetScene(std::string name);
		std::shared_ptr<Scene> GetScene(size_t index) { return m_spScenes[index]; }
		size_t GetSceneCount() const { return m_spScenes.size(); }
		size_t GetActiveSceneIndex() const { return ActiveSceneIndex; }

	
		void Initialize();
		void Update(float deltaTime);
		void Render();

	private:
		std::vector<std::shared_ptr<Scene>> m_spScenes;
		int ActiveSceneIndex = 0;
		int CurrentSceneIndex = 0;
		bool m_isSceneSwitch = false;
	};

}
