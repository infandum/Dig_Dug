#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"
#include "SceneLoader.h"
#include "ServiceLocator.h"

std::shared_ptr<dae::Scene> dae::SceneManager::GetScene(std::string name)
{
	for (const auto& scene : m_spScenes)
	{
		if (scene->GetName() == name)
			return scene;
	}

	return nullptr;
}

void dae::SceneManager::Initialize()
{
	for(ActiveSceneIndex = 0; ActiveSceneIndex < m_spScenes.size(); ++ActiveSceneIndex)
	{
		m_spScenes[ActiveSceneIndex]->Initialize();
	}

	ActiveSceneIndex = 0;
}

void dae::SceneManager::Update(const float deltaTime)
{
	
	m_spScenes[CurrentSceneIndex]->Update(deltaTime);
	if(CurrentSceneIndex != ActiveSceneIndex)
	{
		CurrentSceneIndex = ActiveSceneIndex;
		ServiceLocator::GetSceneLoader()->ResetScene(static_cast<SceneList>(ActiveSceneIndex));
	}
}

void dae::SceneManager::Render()
{
	m_spScenes[ActiveSceneIndex]->Render();
}

std::shared_ptr<dae::Scene> dae::SceneManager::CreateScene(const std::string& name)
{
	for (int i = 0; i < m_spScenes.size(); i++)
	{
		if (m_spScenes[i]->GetName() == name)
		{
			m_spScenes[i].reset(new Scene(name));
			return m_spScenes[i];
		}		
	}

	const auto scene = std::make_shared<Scene>(name);
	ActiveSceneIndex = static_cast<int>(m_spScenes.size());
	m_spScenes.push_back(scene);
	return scene;
}

void dae::SceneManager::NextScene()
{
	//ServiceLocator::GetSceneLoader()->ResetScene(static_cast<SceneList>(ActiveSceneIndex));
	auto i = ActiveSceneIndex;
	i++;
	SetActive(i);
	//ServiceLocator::GetSceneLoader()->ResetScene(static_cast<SceneList>(ActiveSceneIndex));
}

void dae::SceneManager::PreviousScene()
{
	//ServiceLocator::GetSceneLoader()->ResetScene(static_cast<SceneList>(ActiveSceneIndex));
	auto i = ActiveSceneIndex;
	i--;
	SetActive(i);
	//ServiceLocator::GetSceneLoader()->ResetScene(static_cast<SceneList>(ActiveSceneIndex));
}

void dae::SceneManager::SetActive(const std::string& sceneName)
{
	for(auto i = 0; i < m_spScenes.size(); i++)
	{
		if (m_spScenes[i]->GetName() == sceneName)
		{
			SetActive(i);
			return;
		}	
	}

	
}

void dae::SceneManager::SetActive(int& index)
{
	ActiveSceneIndex = index;

	if (ActiveSceneIndex < 0)
		ActiveSceneIndex = static_cast<int>(m_spScenes.size()) - 1;

	if (ActiveSceneIndex >= m_spScenes.size())
		ActiveSceneIndex = 0;

	if (ServiceLocator::GetSceneLoader()->m_Scene != m_spScenes[ActiveSceneIndex])
		ServiceLocator::GetSceneLoader()->m_Scene = m_spScenes[ActiveSceneIndex];

	m_isSceneSwitch = true;
}
