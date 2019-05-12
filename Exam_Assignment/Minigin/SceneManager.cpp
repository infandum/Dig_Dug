#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"
#include "SceneLoader.h"
#include "ServiceLocator.h"

std::shared_ptr<dae::Scene> dae::SceneManager::GetScene(std::string name)
{
	for (const auto scene : m_spScenes)
	{
		if (scene->GetName() == name)
			return scene;
	}

	return nullptr;
}

void dae::SceneManager::Initialize()
{
	for (const auto scene : m_spScenes)
	{
		scene->Initialize();
	}
}

void dae::SceneManager::Update(const float deltaTime)
{
	for (const auto scene : m_spScenes)
	{
		scene->Update(deltaTime);
	}
	//m_spScenes[ActiveSceneIndex]->Update(deltaTime);
}

void dae::SceneManager::Render()
{
	m_spScenes[ActiveSceneIndex]->Render();
}

std::shared_ptr<dae::Scene> dae::SceneManager::CreateScene(const std::string& name)
{
	const auto scene = std::make_shared<Scene>(name);
	m_spScenes.push_back(scene);
	return scene;
}

void dae::SceneManager::NextScene()
{
	++ActiveSceneIndex;
	if (ActiveSceneIndex >= m_spScenes.size())
		ActiveSceneIndex = 0;
}

void dae::SceneManager::PreviousScene()
{
	--ActiveSceneIndex;
	if (ActiveSceneIndex <0)
		ActiveSceneIndex = static_cast<int>(m_spScenes.size()) - 1;
}

void dae::SceneManager::SetActive(const std::string& sceneName)
{
	for(int i = 0; i < m_spScenes.size(); i++)
	{
		if (m_spScenes[i]->GetName() == sceneName)
			ActiveSceneIndex = i;
	}
}

void dae::SceneManager::SetActive(int index)
{
	ActiveSceneIndex = index;
	Initialize();
}
