#include "MiniginPCH.h"
#include "SceneLoader.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "Components.h"
#include <SDL.h>
#include "Scene.h"
#include "LevelManager.h"
#include "InputManager.h"
#include "Commands.h"
#include "ServiceLocator.h"

void dae::SceneLoader::InitScene(dae::SceneList scene)
{
	auto resource = ServiceLocator::GetResourceManager();
	auto input = ServiceLocator::GetInputManager();
	input->AddCommand(std::make_shared<UpCommand>(), ControllerButton::ButtonUp, SDLK_UP);
	input->AddCommand(std::make_shared<DownCommand>(), ControllerButton::ButtonDown, SDLK_DOWN);
	input->AddCommand(std::make_shared<LeftCommand>(), ControllerButton::ButtonLeft, SDLK_LEFT);
	input->AddCommand(std::make_shared<RightCommand>(), ControllerButton::ButtonRight, SDLK_RIGHT);
	input->AddCommand(std::make_shared<AttackCommand>(), ControllerButton::ButtonX, SDLK_x);
	auto animations = ServiceLocator::GetAnimationManager();
	auto tiles = ServiceLocator::GetLevelManager();
	
	std::shared_ptr<Font> font;
	SDL_Color color;
	std::shared_ptr<GameObject> go;
	switch (scene)
	{
	case SceneList::DEMO:
		m_Scene = ServiceLocator::GetSceneManager()->CreateScene("Demo");

			resource->LoadTexture("background.jpg", 999);
			resource->LoadTexture("logo.png", 998);

			go = std::make_shared<GameObject>();
			go->AddComponent(std::make_shared<TransformComponent>());
			go->AddComponent(std::make_shared<TextureComponent>());
			go->GetComponent<TextureComponent>()->SetTexture(resource->GetTexture(999));
			m_Scene->Add(go);

			go = std::make_shared<GameObject>();
			go->AddComponent(std::make_shared<TransformComponent>());
			go->AddComponent(std::make_shared<TextureComponent>());
			go->GetComponent<TextureComponent>()->SetTexture(resource->GetTexture(998));
			go->GetComponent<TransformComponent>()->SetPosition(216, 180);
			m_Scene->Add(go);

			font = resource->LoadFont("Lingua.otf", 36);
			go = std::make_shared<GameObject>();
			go->AddComponent(std::make_shared<TransformComponent>());
			go->AddComponent(std::make_shared<TextureComponent>());
			go->AddComponent(std::make_shared<TextComponent>("Programming 4 Assignment", font));
			go->GetComponent<TransformComponent>()->SetPosition(80, 20);
			m_Scene->Add(go);

			font = resource->LoadFont("Lingua.otf", 30);
			go = std::make_shared<GameObject>();
			go->AddComponent(std::make_shared<TransformComponent>());
			go->AddComponent(std::make_shared<TextureComponent>());
			go->AddComponent(std::make_shared<TextComponent>("00FPS", font));
			go->AddComponent(std::make_shared<FPSComponent>());
			color = { 255, 255, 0 };
			go->GetComponent<TextComponent>()->SetColor(color);
			m_Scene->Add(go);

		break;
	case SceneList::LEVEL_1:
		m_Scene = ServiceLocator::GetSceneManager()->CreateScene("Level 1");
		resource->LoadTexture("images/DigDug_BackGround.png", 01);
		resource->LoadTexture("images/SpriteSheet.png", 02);

		resource->LoadTexture("images/Dirt.png", 10);
		resource->LoadTexture("images/Free.png", 11);
		resource->LoadTexture("images/Rock.png", 12);
		resource->LoadTexture("images/Occupied.png", 13);
			
		resource->LoadTexture("images/Collision.png", 10000);
		resource->LoadTexture("images/ClossWallNZ.png", 10001);
		resource->LoadTexture("images/OpenWallNZ.png", 10002);
		resource->LoadTexture("images/ClossWallEW.png", 10003);
		resource->LoadTexture("images/OpenWallEW.png", 10004);


		go = std::make_shared<GameObject>();
		go->AddComponent(std::make_shared<TransformComponent>());
		go->AddComponent(std::make_shared<TextureComponent>());	
		go->GetComponent<TextureComponent>()->SetTexture(resource->GetTexture(01));
		m_Scene->Add(go);

		for (auto x = 0; x < 14; ++x)
		{
			for (auto y = 0; y < 17; ++y)
			{
				auto tile = std::make_shared<GameObject>();
				tile->AddComponent(std::make_shared<TransformComponent>());
				tile->AddComponent(std::make_shared<TextureComponent>());
				tile->AddComponent(std::make_shared<TileComponent>(TileState::EMPITY, x, y));
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
		m_pPlayer->AddComponent(std::make_shared<CollisionComponent>());
		m_pPlayer->AddComponent(std::make_shared<TransformComponent>());
		m_pPlayer->AddComponent(std::make_shared<InputComponent>());
		m_pPlayer->AddComponent(std::make_shared<TextureComponent>());
		m_pPlayer->AddComponent(std::make_shared<SpriteComponent>());
		m_pPlayer->GetComponent<TextureComponent>()->SetTexture(resource->GetTexture(02));
		m_pPlayer->GetComponent<TransformComponent>()->SetPosition(0, 96);
		m_pPlayer->GetComponent<TransformComponent>()->SetIsStatic(false);

		animations->LoadSpriteClip(SpriteClip{ 0,iVector2{0,0}, 1, 2, true, true }, 1);
		m_pPlayer->GetComponent<SpriteComponent>()->SetAnimationToState(1, std::make_shared<IdleState>());
		animations->LoadSpriteClip(SpriteClip{ 0,iVector2{0,0}, 1, 2, true, true }, 2);
		m_pPlayer->GetComponent<SpriteComponent>()->SetAnimationToState(2, std::make_shared<MoveState>());
		animations->LoadSpriteClip(SpriteClip{ 0,iVector2{0,32}, 1, 2, true, true }, 3);
		m_pPlayer->GetComponent<SpriteComponent>()->SetAnimationToState(3, std::make_shared<DigState>());
		animations->LoadSpriteClip(SpriteClip{ 0,iVector2{0,64}, 0, 1, true, false }, 4);
		m_pPlayer->GetComponent<SpriteComponent>()->SetAnimationToState(4, std::make_shared<AttackState>());

		m_Scene->Add(m_pPlayer);

		go = std::make_shared<GameObject>();
		go->SetName("Pooka");
		go->AddComponent(std::make_shared<CollisionComponent>());
		go->AddComponent(std::make_shared<TransformComponent>());
		go->AddComponent(std::make_shared<TextureComponent>());
		go->AddComponent(std::make_shared<SpriteComponent>());
		go->GetComponent<TextureComponent>()->SetTexture(resource->GetTexture(02));
		go->GetComponent<TransformComponent>()->SetPosition(32 * 8, 32 * 8);
		animations->LoadSpriteClip(SpriteClip{ 0,iVector2{0,288}, 0, 2, false, true }, 5);
		go->GetComponent<SpriteComponent>()->SetAnimationToState(5, std::make_shared<IdleState>());
		m_Scene->Add(go);

		go = std::make_shared<GameObject>();
		go->SetName("Rock");
		go->AddComponent(std::make_shared <CollisionComponent>());
		go->AddComponent(std::make_shared<TransformComponent>());
		go->AddComponent(std::make_shared<TextureComponent>());
		go->GetComponent<TextureComponent>()->SetTexture(resource->GetTexture(12));
		go->GetComponent<TransformComponent>()->SetPosition(32*4, 32*6);
		//go->GetComponent<TransformComponent>()->SetIsStatic(true);
		m_Scene->Add(go);
		
		tiles->SetPlayer(m_pPlayer);
		tiles->CreateTunnel(12, 12, Direction::UP, 2);
		tiles->CreateTunnel(12, 12, Direction::LEFT, 2);

		font = resource->LoadFont("Lingua.otf", 25);
		go = std::make_shared<GameObject>();
		go->AddComponent(std::make_shared<TransformComponent>());
		go->AddComponent(std::make_shared<TextureComponent>());
		go->AddComponent(std::make_shared<TextComponent>("00FPS", font));
		go->AddComponent(std::make_shared<FPSComponent>());
		color = { 255, 255, 0 };
		go->GetComponent<TextComponent>()->SetColor(color);
		m_Scene->Add(go);
		break;
	default: ;
	}
}
