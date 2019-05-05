#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Initialize()
{
	for (const auto scene : m_spScenes)
	{
		scene->Initialize();
	}
}

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