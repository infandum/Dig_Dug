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
#include "DemoScene.h"

extern const float g_MoveSpeed = 90.f;
extern const float g_TileCenterPadding = 1.0f;

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

	ServiceLocator::InitSceneManager(new SceneManager());

	ServiceLocator::InitSceneLoader(new SceneLoader());

	ServiceLocator::InitInputManager(new InputManager());

	ServiceLocator::InitAnimationManager(new AnimationManager());

	ServiceLocator::InitLevelManager(new LevelManager());

	ServiceLocator::InitPhysicsManager(new PhysicsManager());

	ServiceLocator::GetRenderer()->Initialize(window);

	
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	//TODO: FIX LEVEL RELOADING GO OVER ALL COMP INIT WHILE IM AT IT.
	ServiceLocator::GetSceneLoader()->Initialize();
	ServiceLocator::GetSceneLoader()->InitScene(SceneList::MAIN_MENU);
	ServiceLocator::GetSceneLoader()->InitScene(SceneList::LEVEL_SINGLE);
	ServiceLocator::GetSceneLoader()->InitScene(SceneList::LEVEL_COOP);

	
	ServiceLocator::GetSceneManager()->Initialize();
	ServiceLocator::GetSceneManager()->SetActive("Level single");
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
		auto inputManager = ServiceLocator::GetInputManager();
		auto levelManager = ServiceLocator::GetLevelManager();
		auto physicsManager = ServiceLocator::GetPhysicsManager();
		physicsManager->ShowCollisionBox(true);
		
		auto t = std::chrono::high_resolution_clock::now();
		auto doContinue = true;
		auto lag{ 0.0f };
		auto previousTime = std::chrono::high_resolution_clock::now();
		
		while (doContinue)
		{		
			const auto currentTime = std::chrono::high_resolution_clock::now();
			const auto deltatime = std::chrono::duration<float>(currentTime - previousTime).count();
			previousTime = currentTime;
			lag += deltatime;
			doContinue = inputManager->ProcessInput();
				
			sceneManager->Update(static_cast<float>(deltatime));
			physicsManager->Update(static_cast<float>(deltatime));
			levelManager->Update(static_cast<float>(deltatime));
			

			t += std::chrono::milliseconds(msPerFrame);
			std::this_thread::sleep_until(t);

			renderer->Render();
		}
	}
	Cleanup();
}
