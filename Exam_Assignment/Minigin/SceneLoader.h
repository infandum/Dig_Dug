#pragma once
#include "InputManager.h"
#include "Font.h"
#include <memory>
#include "ResourceManager.h"
#include "LevelManager.h"
#include "PhysicsManager.h"

namespace dae
{
	enum class SceneList
	{
		MAIN_MENU = 0,
		LEVEL_SINGLE = 1,
		LEVEL_COOP = 2,
		LEVEL_VS = 3
	};

	class SceneManager;
	class GameObject;
	class Scene;
	class SceneLoader final
	{
		friend SceneManager;
	public:

		/*void AddLevelManager() const;
		void AddPhysicsManager(bool showCollision = false) const;*/
		void InitScene(SceneList scene);
		void PostInitScene(SceneList scene) const;

		void ResetScene(SceneList scene) const;

		void Initialize();
		void Update(float deltaTime);

		std::shared_ptr<Scene> m_Scene = nullptr;

	private:
		void AddMenu() const;
		void AddGUI(float x = 0.f, float y = 0.f) const;
		void AddPlayer(PlayerType type, float x = 0.f, float y = 0.f) const;
		void AddNpc(NPCType type, float x = 0.f, float y = 0.f) const;
		void GenerateTile() const;
		void AddBackground(UINT textureID) const;
		void AddText(std::shared_ptr<Font> font, const SDL_Color& color = { 255, 255, 255 }, std::string text = "", float x = 0.f, float y = 0.f) const;
		void AddFPS(std::shared_ptr<Font> font, const SDL_Color& color = {255, 255, 255}) const;
		
	};
}
