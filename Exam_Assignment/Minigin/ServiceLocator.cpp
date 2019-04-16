#include "MiniginPCH.h"
#include "ServiceLocator.h"

std::map<UINT, std::unique_ptr<dae::Service>> m_pServices;
std::unique_ptr<dae::Renderer> dae::ServiceLocator::m_pRenderer = nullptr;
std::unique_ptr<dae::SceneManager> dae::ServiceLocator::m_pSceneManager = nullptr;
std::unique_ptr<dae::PhysicsManager> dae::ServiceLocator::m_pPhysicsManager = nullptr;
std::unique_ptr<dae::InputManager>  dae::ServiceLocator::m_pInputManager = nullptr;
std::unique_ptr<dae::LevelManager>  dae::ServiceLocator::m_pLevelManager = nullptr;