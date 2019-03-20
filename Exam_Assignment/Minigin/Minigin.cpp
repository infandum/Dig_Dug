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
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<GameObject>();
	go->AddComponent(new TransformComponent());
	go->AddComponent(new TextureComponent());
	go->GetComponent<TextureComponent>()->SetTexture("background.jpg");
	scene.Add(go);

	go = std::make_shared<GameObject>();
	go->AddComponent(new TransformComponent());
	go->AddComponent(new TextureComponent());
	go->GetComponent<TextureComponent>()->SetTexture("logo.png");
	go->GetComponent<TransformComponent>()->SetPosition(216, 180);
	scene.Add(go);

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go = std::make_shared<GameObject>();
	go->AddComponent(new TransformComponent());
	go->AddComponent(new TextureComponent());
	go->AddComponent(new TextComponent("Programming 4 Assignment", font));
	go->GetComponent<TransformComponent>()->SetPosition(80, 20);
	scene.Add(go);

	font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 30);
	go = std::make_shared<GameObject>();
	go->AddComponent(new TransformComponent());
	go->AddComponent(new TextureComponent());
	go->AddComponent(new TextComponent("00FPS", font));
	go->AddComponent(new FPSComponent());
	const SDL_Color color{ 255, 255, 0 };
	go->GetComponent<TextComponent>()->SetColor(color);
	scene.Add(go);
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
