#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "SceneLoader.h"
#include "Renderer.h"

#include "LevelManager.h"
#include "PhysicsManager.h"

#include <SDL.h>
#include "ServiceLocator.h"

extern const float g_MoveSpeed = 90.f;
extern const float g_TileCenterPadding = 1.0f;
extern const float g_CollisionPadding = 1.0f;

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
		448,
		576,
		SDL_WINDOW_OPENGL
	);
	if (window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}
	ServiceLocator::InitRenderer(new Renderer());
	
	ServiceLocator::InitResourceManager(new ResourceManager());

	ServiceLocator::InitPhysicsManager(new PhysicsManager());

	ServiceLocator::InitSceneManager(new SceneManager());

	ServiceLocator::InitSceneLoader(new SceneLoader());

	ServiceLocator::InitInputManager(new InputManager());

	ServiceLocator::InitLevelManager(new LevelManager());

	ServiceLocator::InitAnimationManager(new AnimationManager());

	ServiceLocator::GetRenderer()->Init(window);

}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	ServiceLocator::GetSceneLoader()->InitScene(SceneList::LEVEL_1);
}

void dae::Minigin::Cleanup()
{
	ServiceLocator::GetRenderer()->Destroy();
	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ServiceLocator::GetResourceManager()->Init("../Data/");
	LoadGame();
	{
		auto renderer = ServiceLocator::GetRenderer();
		auto sceneManager = ServiceLocator::GetSceneManager();
		auto input = ServiceLocator::GetInputManager();
		auto tileManager = ServiceLocator::GetLevelManager();
		auto physics = ServiceLocator::GetPhysicsManager();
		physics->ShowCollisionBox(true);
		

		auto t = std::chrono::high_resolution_clock::now();
		auto doContinue = true;
		auto lag{ 0.0f };
		auto previousTime = std::chrono::high_resolution_clock::now();
		//const auto perUpdateTime{ float(msPerFrame) };
		while (doContinue)
		{
			const auto currentTime = std::chrono::high_resolution_clock::now();
			const auto deltatime = std::chrono::duration<float>(currentTime - previousTime).count();
			previousTime = currentTime;
			lag += deltatime;
			doContinue = input->ProcessInput();

			physics->Update(float(deltatime));
			tileManager->Update(float(deltatime));
			sceneManager->Update(float(deltatime));		

			t += std::chrono::milliseconds(msPerFrame);
			std::this_thread::sleep_until(t);

			renderer->Render();
		}
	}
	Cleanup();
}
