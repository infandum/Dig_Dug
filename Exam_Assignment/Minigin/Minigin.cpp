#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "GameObject.h"
#include "Scene.h"
#include "Components.h"
#include "Scenes.h"


void dae::Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(window);
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	
	
	
	SceneManager::GetInstance().AddScene(std::shared_ptr<Scene>(new DemoScene()));
	SceneManager::GetInstance().AddScene(std::shared_ptr<Scene>(new Level1()));
	SceneManager::GetInstance().SetActive("Demo");
}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");
	LoadGame();
	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

		auto doContinue = true;
		auto lag{ 0.0f };
		auto previousTime = GetCurrentTime();
		const auto perUpdateTime{ float(msPerFrame) };
		while (doContinue)
		{
			const auto currentTime = GetCurrentTime();
			const auto elapsedTime = currentTime - previousTime;
			previousTime = currentTime;
			lag += elapsedTime;
			doContinue = input.ProcessInput();
			while (lag >= perUpdateTime)
			{
				sceneManager.Update(float(elapsedTime));
				lag -= perUpdateTime;
			}
			renderer.Render();
		}
	}
	Cleanup();
}
