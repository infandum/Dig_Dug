#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"
//#include <algorithm>


void dae::SceneManager::Update(const float deltaTime)
{
	for (auto scene : m_spScenes)
	{
		scene->Update(deltaTime);
	}
}

void dae::SceneManager::Render()
{
	for (const auto scene : m_spScenes)
	{
		scene->Render();
	}
}

std::shared_ptr<dae::Scene> dae::SceneManager::CreateScene(const std::string& name)
{
	const auto scene = std::make_shared<Scene>(name);
	m_spScenes.push_back(scene);
	return scene;
}
//void dae::SceneManager::Update(float deltaTime)
//{
//	for(auto scene : m_spScenes)
//	{
//		if (scene == m_spCurrentScene)
//		{
//			scene->Update(deltaTime);
//			scene->RootUpdate(deltaTime);
//		}
//	}
//
//	if (m_spNextScene != nullptr)
//	{
//		//Deactivate the current active scene
//		//if (m_spCurrentScene != nullptr)
//			//m_spCurrentScene->RootSceneDeactivated();
//		//Set New Scene
//		m_spCurrentScene = m_spNextScene;
//		m_spNextScene = nullptr;
//		//Active the new scene and reset SceneTimer
//		//m_spCurrentScene->RootSceneActivated();
//	}
//}
//
//void dae::SceneManager::Render()
//{
//	for (const auto scene : m_spScenes)
//	{
//		if (scene == m_spCurrentScene)
//		{
//			scene->Render();
//		}		
//	}
//}
//
//dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
//{
//	const auto scene = std::shared_ptr<Scene>(new Scene(name));
//	m_spScenes.push_back(scene);
//	return *scene;
//}
//
//void dae::SceneManager::AddScene(std::shared_ptr<Scene>pScene)
//{
//	m_spScenes.push_back(pScene);
//	pScene->Initialize();
//}
//
//void dae::SceneManager::NextScene()
//{
//	for (unsigned int i = 0; i < m_spScenes.size(); ++i)
//	{
//		if (m_spScenes[i] == m_spCurrentScene)
//		{
//			const auto nextScene = ++i % m_spScenes.size();
//			m_spNextScene = m_spScenes[nextScene];
//			break;
//		}
//	}
//}
//
//void dae::SceneManager::PreviousScene()
//{
//	for (unsigned int i = 0; i < m_spScenes.size(); ++i)
//	{
//		if (m_spScenes[i] == m_spCurrentScene)
//		{
//			if (i == 0) i = int(m_spScenes.size());
//			--i;
//			m_spNextScene = m_spScenes[i];
//			break;
//		}
//	}
//}
//
//void dae::SceneManager::SetActive(const std::string& sceneName)
//{
//	for (unsigned int i = 0; i < m_spScenes.size(); ++i)
//	{
//		if (m_spScenes[i]->GetName() == sceneName)
//		{
//			m_spNextScene = m_spScenes[i];
//			break;
//		}
//	}
//}