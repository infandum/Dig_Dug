#pragma once
#include "Service.h"
#include "Renderer.h"
#include "SceneManager.h"
#include "SceneLoader.h"
#include "PhysicsManager.h"
#include "InputManager.h"
#include "LevelManager.h"
#include "ResourceManager.h"
#include "AnimationManager.h"

namespace  dae 
{

	class ServiceLocator
	{
	public:

		//TODO: REFRACTOR SERVICE PROVIDE AND RETURN
		Service* GetService(UINT id);
		void Provide(Service* service, UINT id);


		static void InitRenderer(Renderer* renderer) { m_pRenderer.reset(renderer); }

		static void InitSceneManager(SceneManager* sceneManager) {	m_pSceneManager.reset(sceneManager); }
		static void InitSceneLoader(SceneLoader* sceneLoader) { m_pSceneLoader.reset(sceneLoader); }

		static void InitPhysicsManager(PhysicsManager * physicsManager){ m_pPhysicsManager.reset(physicsManager); }

		static void InitInputManager(InputManager* inputManager) { m_pInputManager.reset(inputManager); }

		static void InitLevelManager(LevelManager* levelManager) { m_pLevelManager.reset(levelManager); }

		static void InitResourceManager(ResourceManager* resourceManager) { m_pResourceManager.reset(resourceManager); }

		static void InitAnimationManager(AnimationManager* animationManager) { m_pAnimationManager.reset(animationManager); }

		static Renderer* GetRenderer() { return m_pRenderer.get(); }
		static SceneManager* GetSceneManager() { return m_pSceneManager.get(); }
		static SceneLoader* GetSceneLoader() { return m_pSceneLoader.get(); }
		static PhysicsManager* GetPhysicsManager() { return m_pPhysicsManager.get(); }
		static InputManager* GetInputManager() { return m_pInputManager.get(); }
		static LevelManager* GetLevelManager() { return m_pLevelManager.get(); }
		static ResourceManager* GetResourceManager() { return m_pResourceManager.get(); }
		static AnimationManager* GetAnimationManager() { return m_pAnimationManager.get(); }

	private:
		static std::map<UINT, std::unique_ptr<Service>> m_pServices;
		static std::unique_ptr<Renderer>  m_pRenderer;
		static std::unique_ptr<SceneManager> m_pSceneManager;
		static std::unique_ptr<SceneLoader> m_pSceneLoader;
		static std::unique_ptr<PhysicsManager > m_pPhysicsManager;
		static std::unique_ptr<InputManager > m_pInputManager;
		static std::unique_ptr<LevelManager> m_pLevelManager;
		static std::unique_ptr<ResourceManager> m_pResourceManager;
		static std::unique_ptr<AnimationManager> m_pAnimationManager;
	};
}
