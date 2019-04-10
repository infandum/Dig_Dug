#include "MiniginPCH.h"
#include "SceneLoader.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "Components.h"
#include <SDL.h>
#include "ResourceManager.h"
#include "Scene.h"

void dae::SceneLoader::InitScene(dae::SceneList scene)
{
	std::shared_ptr<GameObject> go{};
	std::shared_ptr<Font> font {};
	SDL_Color color{};
	switch (scene)
	{
	case SceneList::DEMO:
		m_Scene = SceneManager::GetInstance().CreateScene("Demo");

			go = std::make_shared<GameObject>();
			go->AddComponent(new TransformComponent());
			go->AddComponent(new TextureComponent());
			go->AddComponent(new TextureComponent());
			go->GetComponent<TextureComponent>()->SetTexture("background.jpg");
			m_Scene->Add(go);

			go = std::make_shared<GameObject>();
			go->AddComponent(new TransformComponent());
			go->AddComponent(new TextureComponent());
			go->GetComponent<TextureComponent>()->SetTexture("logo.png");
			go->GetComponent<TransformComponent>()->SetPosition(216, 180);
			m_Scene->Add(go);

			font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
			go = std::make_shared<GameObject>();
			go->AddComponent(new TransformComponent());
			go->AddComponent(new TextureComponent());
			go->AddComponent(new TextComponent("Programming 4 Assignment", font));
			go->GetComponent<TransformComponent>()->SetPosition(80, 20);
			m_Scene->Add(go);

			font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 30);
			go = std::make_shared<GameObject>();
			go->AddComponent(new TransformComponent());
			go->AddComponent(new TextureComponent());
			go->AddComponent(new TextComponent("00FPS", font));
			go->AddComponent(new FPSComponent());
			color = { 255, 255, 0 };
			go->GetComponent<TextComponent>()->SetColor(color);
			m_Scene->Add(go);
		break;
	case SceneList::LEVEL_1:
		m_Scene = SceneManager::GetInstance().CreateScene("Level 1");

		go = std::make_shared<GameObject>();
		go->AddComponent(new TransformComponent());
		go->AddComponent(new TextureComponent());
		go->GetComponent<TextureComponent>()->SetTexture("images/background@2x.png");
		m_Scene->Add(go);

		for (int x = 0; x < 14; ++x)
		{
			for (int y = 0; y < 18; ++y)
			{
				auto tile = std::make_shared<GameObject>();
				tile->AddComponent(new TransformComponent());
				tile->AddComponent(new TextureComponent());
				if (y <= 1)
					tile->GetComponent<TextureComponent>()->SetTexture("images/Free.png");
				else if(y >=17)
					tile->GetComponent<TextureComponent>()->SetTexture("images/Occupied.png");
				else
					tile->GetComponent<TextureComponent>()->SetTexture("images/Dirt.png");
				tile->GetComponent<TransformComponent>()->SetPosition(static_cast<float>(x) * 32, static_cast<float>(y) * 32);
				m_Scene->Add(tile);
			}
		}

		m_pPlayer = std::make_shared<GameObject>();
		m_pPlayer->SetName("Player");
		m_pPlayer->AddComponent(new TransformComponent());
		m_pPlayer->AddComponent(new InputComponent());
		m_pPlayer->AddComponent(new TextureComponent());
		m_pPlayer->GetComponent<TextureComponent>()->SetTexture("images/Player/Player.png");
		m_pPlayer->GetComponent<TransformComponent>()->SetPosition(0, 96);
		m_pPlayer->GetComponent<TransformComponent>()->isMoving = true;
		m_Scene->Add(m_pPlayer);
		//map.SetPlayer(m_pPlayer);

		font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 25);
		go = std::make_shared<GameObject>();
		go->AddComponent(new TransformComponent());
		go->AddComponent(new TextureComponent());
		go->AddComponent(new TextComponent("00FPS", font));
		go->AddComponent(new FPSComponent());
		color = { 255, 255, 0 };
		go->GetComponent<TextComponent>()->SetColor(color);
		m_Scene->Add(go);
		break;
	}
}
