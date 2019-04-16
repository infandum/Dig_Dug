#pragma once
#include "SceneManager.h"
#include "Renderer.h"
#include "PhysicsManager.h"
#include "InputManager.h"
#include "LevelManager.h"
#include <map>
#include "Service.h"

namespace  dae 
{

	class ServiceLocator
	{
	public:

		//TODO: SWAP SINGELTON WITH SERVICES
		static void InitRenderer(Renderer* renderer) { m_pRenderer.reset(renderer); }

		static void InitSceneManager(SceneManager* sceneManager) {	m_pSceneManager.reset(sceneManager); }

		static void InitPhysicsManager(PhysicsManager * physicsManager){ m_pPhysicsManager.reset(physicsManager); }

		static void InitInputManager(InputManager* inputManager) { m_pInputManager.reset(inputManager); }

		static void InitLevelManager(LevelManager* mapManager) { m_pLevelManager.reset(mapManager); }

		static Renderer* GetRenderer() { return m_pRenderer.get(); }
		static SceneManager* GetSceneManager() { return m_pSceneManager.get(); }
		static PhysicsManager* GetPhysicsManager() { return m_pPhysicsManager.get(); }
		static InputManager* GetInputManager() { return m_pInputManager.get(); }
		static LevelManager* GetLevelManager() { return m_pLevelManager.get(); }

	private:
		static std::map<UINT, std::unique_ptr<Service>> m_pServices;
		static std::unique_ptr<Renderer>  m_pRenderer;
		static std::unique_ptr<SceneManager> m_pSceneManager;
		static std::unique_ptr<PhysicsManager > m_pPhysicsManager;
		static std::unique_ptr<InputManager > m_pInputManager;
		static std::unique_ptr<LevelManager> m_pLevelManager;
	};
}
