#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"


void dae::SceneManager::Update()
{
	for(auto scene : mScenes)
	{
		scene->Update();
	}
}

void dae::SceneManager::Render()
{
	for (const auto scene : mScenes)
	{
		scene->Render();
	}
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto scene = std::shared_ptr<Scene>(new Scene(name));
	mScenes.push_back(scene);
	return *scene;
}
