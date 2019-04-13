#include "MiniginPCH.h"
#include "SceneLoader.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "Components.h"
#include <SDL.h>
#include "ResourceManager.h"
#include "Scene.h"
#include "TileManager.h"

void dae::SceneLoader::InitScene(dae::SceneList scene)
{
	auto& tiles = TileManager::GetInstance();
	auto& resource = ResourceManager::GetInstance();
	
	std::shared_ptr<GameObject> go;
	std::shared_ptr<Font> font;
	SDL_Color color;
	switch (scene)
	{
	case SceneList::DEMO:
		m_Scene = SceneManager::GetInstance().CreateScene("Demo");

			resource.LoadTexture("background.jpg", 999);
			resource.LoadTexture("logo.png", 998);
			resource.LoadTexture("images/Player/Player.png", 02);

			go = std::make_shared<GameObject>();
			go->AddComponent(new TransformComponent());
			go->AddComponent(new TextureComponent());
			go->AddComponent(new TextureComponent());
			go->GetComponent<TextureComponent>()->SetTexture(resource.GetTexture(999));
			m_Scene->Add(go);

			go = std::make_shared<GameObject>();
			go->AddComponent(new TransformComponent());
			go->AddComponent(new TextureComponent());
			go->GetComponent<TextureComponent>()->SetTexture(resource.GetTexture(998));
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
		resource.LoadTexture("images/background@2x.png", 01);
		resource.LoadTexture("images/Player/Player.png", 02);

		resource.LoadTexture("images/Dirt.png", 10);
		resource.LoadTexture("images/Free.png", 11);
		resource.LoadTexture("images/Rock.png", 12);
		resource.LoadTexture("images/Occupied.png", 13);

		resource.LoadTexture("images/Collision.png", 10000);
		resource.LoadTexture("images/ClossWallNZ.png", 10001);
		resource.LoadTexture("images/OpenWallNZ.png", 10002);
		resource.LoadTexture("images/ClossWallEW.png", 10003);
		resource.LoadTexture("images/OpenWallEW.png", 10004);

		go = std::make_shared<GameObject>();
		go->AddComponent(new TransformComponent());
		go->AddComponent(new TextureComponent());
		go->GetComponent<TextureComponent>()->SetTexture(resource.GetTexture(01));
		m_Scene->Add(go);

		for (auto x = 0; x < 14; ++x)
		{
			for (auto y = 1; y < 17; ++y)
			{
				auto tile = std::make_shared<GameObject>();
				tile->AddComponent(new TransformComponent());
				tile->AddComponent(new TextureComponent());
				tile->AddComponent(new TileComponent(TileState::EMPITY, x, y));
				tile->GetComponent<TileComponent>()->SetTileState(TileState::EMPITY);
				if (y <= 1)
					tile->GetComponent<TileComponent>()->SetTileState(TileState::EMPITY);
				else
					tile->GetComponent<TileComponent>()->SetTileState(TileState::DIRT);
				tile->GetComponent<TransformComponent>()->SetPosition(static_cast<float>(x) * 32, static_cast<float>(y) * 32);
				m_Scene->Add(tile);
			}
		}

		m_pPlayer = std::make_shared<GameObject>();
		m_pPlayer->SetName("Player");
		m_pPlayer->AddComponent(new CollisionComponent());
		m_pPlayer->AddComponent(new TransformComponent());
		m_pPlayer->AddComponent(new InputComponent());
		m_pPlayer->AddComponent(new TextureComponent());		
		m_pPlayer->GetComponent<TextureComponent>()->SetTexture(resource.GetTexture(02));
		m_pPlayer->GetComponent<TransformComponent>()->SetPosition(0, 96);
		m_pPlayer->GetComponent<TransformComponent>()->SetIsStatic(false);
		//m_pPlayer->GetComponent<CollisionComponent>()->ShowCollisionBox(true);
		m_Scene->Add(m_pPlayer);

		go = std::make_shared<GameObject>();
		go->SetName("Rock");
		go->AddComponent(new CollisionComponent());
		go->AddComponent(new TransformComponent());
		go->AddComponent(new TextureComponent());	
		go->GetComponent<TextureComponent>()->SetTexture(resource.GetTexture(12));
		go->GetComponent<TransformComponent>()->SetPosition(32*4, 32*6);
		m_Scene->Add(go);
		
		tiles.SetPlayer(m_pPlayer);
		tiles.CreateTunnel(12, 12, Direction::UP, 2);
		tiles.CreateTunnel(12, 12, Direction::LEFT, 2);

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
	default: ;
	}
}
