#pragma once
#include "Service.h"
#include "InputManager.h"
#include "Font.h"
#include <memory>
#include "ResourceManager.h"

namespace dae
{
	enum class SceneList
	{
		MAIN_MENU,
		LEVEL_SINGLE,
		LEVEL_COOP,
		LEVEL_VS
	};
	class GameObject;
	class Scene;
	class SceneLoader : public Service
	{
	public:

		static void Initialize();
		void InitScene(SceneList scene);
		static void PostInitScene(SceneList scene);

		void ResetScene(SceneList scene);

		

	private:
		void AddMenu() const;
		void AddPlayer(PlayerType type, float x = 0.f, float y = 0.f) const;
		void AddNpc(NPCType type, float x = 0.f, float y = 0.f) const;
		void GenerateTile() const;
		void AddBackground(UINT textureID) const;
		void AddText(std::shared_ptr<Font> font, const SDL_Color& color = { 255, 255, 255 }, std::string text = "", float x = 0.f, float y = 0.f) const;
		void AddFPS(std::shared_ptr<Font> font, const SDL_Color& color = {255, 255, 255}) const;
		std::shared_ptr<Scene> m_Scene = nullptr;
	};
}
