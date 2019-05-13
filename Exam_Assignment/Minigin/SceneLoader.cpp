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

//TODO: FILE READING LEVEL LOADING
//TODO DECOUPLE MORE FUNCTION AWAY FROM PURE DIG USED FEATURES more


void dae::SceneLoader::Initialize()
{
	auto resource = ServiceLocator::GetResourceManager();
	resource->LoadTexture("images/DigDug_BackGround.png", 01);
	resource->LoadTexture("images/SpriteSheet.png", 02);

	resource->LoadTexture("images/Dirt.png", 10);
	resource->LoadTexture("images/Free.png", 11);
	resource->LoadTexture("images/Rock.png", 12);
	resource->LoadTexture("images/Occupied.png", 13);

	resource->LoadTexture("images/Collision.png", 10000);
	resource->LoadTexture("images/OpenWallNZ.png", 10002);
	resource->LoadTexture("images/OpenWallEW.png", 10004);

	auto animations = ServiceLocator::GetAnimationManager();
	animations->SetAnimationSpeed(10.0f);

	//DIG DUG
	animations->LoadSpriteClip(SpriteClip{ 0, {0, 0}, { 32 , 32 }, 1, 2, true, false }, 1);
	animations->LoadSpriteClip(SpriteClip{ 0, {0, 0}, { 32 , 32 }, 1, 2, true, true }, 2);
	animations->LoadSpriteClip(SpriteClip{ 0, {0, 32}, { 32 , 32 }, 1, 2, true, true }, 3);
	animations->LoadSpriteClip(SpriteClip{ 0, {0, 64}, { 32 , 32 }, 0, 1, true, false }, 4);
	animations->LoadSpriteClip(SpriteClip{ 0, {0, 224}, { 32 , 32 }, 0, 4, true, false }, 5);

	//POOKA
	animations->LoadSpriteClip(SpriteClip{ 0, {32, 256}, { 32 , 32 }, 0, 1, false, false }, 11);
	animations->LoadSpriteClip(SpriteClip{ 0, {0, 256}, { 32 , 32 }, 0, 2, false, true }, 12);
	animations->LoadSpriteClip(SpriteClip{ 0, {0, 288}, { 64 , 64 }, 0, 4, true, false }, 15);

}

void dae::SceneLoader::InitScene(dae::SceneList scene)
{
	auto resource = ServiceLocator::GetResourceManager();
	

	std::shared_ptr<Font> font;
	SDL_Color color;
	std::shared_ptr<GameObject> go;
	switch (scene)
	{
	case SceneList::MAIN_MENU:
			m_Scene = ServiceLocator::GetSceneManager()->CreateScene("Main menu");

			

			AddMenu();

			AddBackground(01);

			font = resource->LoadFont("Lingua.otf", 32);
			AddText(font, {0,0,0}, "Programming 4 Assignment", 16, 100);

			font = resource->LoadFont("emulogic.ttf", 32);
			AddText(font, { 0,0,0 }, "DigDug", 124, 64);

			font = resource->LoadFont("emulogic.ttf", 12);
			AddFPS(font, color);

		break;
	case SceneList::LEVEL_SINGLE:
		m_Scene = ServiceLocator::GetSceneManager()->CreateScene("Level 1");

		AddMenu();

		AddBackground(01);

		GenerateTile();
		//GenerateTile();

		AddPlayer(PlayerType::PLAYER_DIGDUG, 0.f, 96.f);

		AddPlayer(PlayerType::PLAYER_DIGDUG, 0.f, 32.f * 12);


		AddNpc(NPCType::POOKA, 32.f, 32 * 8.f);

		AddNpc(NPCType::ROCK, 32.f * 4.f, 32 * 6.f);

		/*tiles->CreateTunnel(12, 12, Direction::UP, 2);
		tiles->CreateTunnel(12, 12, Direction::LEFT, 2);*/

		font = resource->LoadFont("emulogic.ttf", 12);
		AddFPS(font, color);
		break;
	default: ;
	}
}

void dae::SceneLoader::PostInitScene(SceneList scene)
{
	auto tiles = ServiceLocator::GetLevelManager();

	switch (scene)
	{
	default: 
		break;
	case SceneList::MAIN_MENU:
		break;
	case SceneList::LEVEL_SINGLE:
		tiles->CreateTunnel(12, 12, Direction::UP, 2);
		tiles->CreateTunnel(12, 12, Direction::LEFT, 2);
		break;
	
	}

}

void dae::SceneLoader::ResetScene(SceneList scene)
{
	switch (scene)
	{
	default:
		break;
	case SceneList::MAIN_MENU:
		break;
	case SceneList::LEVEL_SINGLE:

		break;

	}
}

void dae::SceneLoader::AddMenu() const
{
	std::shared_ptr<GameObject> menu;
	menu = std::make_shared<GameObject>();
	menu->AddComponent(std::make_shared<InputComponent>());
	ServiceLocator::GetInputManager()->AddCommand(std::make_shared<ExitCommand>(), ControllerButton::ButtonSelect, SDLK_ESCAPE, nullptr);
	m_Scene->Add(menu);
}

void dae::SceneLoader::AddPlayer(PlayerType type, float x, float y) const
{
	std::shared_ptr<GameObject> player = std::make_shared<GameObject>();
	player->SetName("Player");
	player->AddComponent(std::make_shared<RenderComponent>());
	player->AddComponent(std::make_shared<CollisionComponent>());
	player->AddComponent(std::make_shared<TransformComponent>(x, y));
	player->AddComponent(std::make_shared<MoveComponent>());
	player->AddComponent(std::make_shared<PlayerComponent>(type));
	player->AddComponent(std::make_shared<TextureComponent>());
	player->AddComponent(std::make_shared<SpriteComponent>());
	player->GetComponent<TextureComponent>()->SetTexture(ServiceLocator::GetResourceManager()->GetTexture(02));

	


	switch (type)
	{
	default:;

	case PlayerType::PLAYER_DIGDUG:
		player->GetComponent<SpriteComponent>()->SetAnimationToState(1, std::make_shared<IdlePlayerState>());
		player->GetComponent<SpriteComponent>()->SetAnimationToState(2, std::make_shared<MovePlayerState>());
		player->GetComponent<SpriteComponent>()->SetAnimationToState(3, std::make_shared<DigPlayerState>());
		player->GetComponent<SpriteComponent>()->SetAnimationToState(4, std::make_shared<AttackPlayerState>());
		player->GetComponent<SpriteComponent>()->SetAnimationToState(5, std::make_shared<DeadPlayerState>());

		ServiceLocator::GetInputManager()->AddCommand(std::make_shared<UpCommand>(), ControllerButton::ButtonUp, SDLK_UP, player.get());
		ServiceLocator::GetInputManager()->AddCommand(std::make_shared<DownCommand>(), ControllerButton::ButtonDown, SDLK_DOWN, player.get());
		ServiceLocator::GetInputManager()->AddCommand(std::make_shared<LeftCommand>(), ControllerButton::ButtonLeft, SDLK_LEFT, player.get());
		ServiceLocator::GetInputManager()->AddCommand(std::make_shared<RightCommand>(), ControllerButton::ButtonRight, SDLK_RIGHT, player.get());
		ServiceLocator::GetInputManager()->AddCommand(std::make_shared<AttackCommand>(), ControllerButton::ButtonX, SDLK_x, player.get());
		break;

	case PlayerType::PLAYER_FYGAR:


		player->GetComponent<SpriteComponent>()->SetAnimationToState(1, std::make_shared<IdlePlayerState>());
		player->GetComponent<SpriteComponent>()->SetAnimationToState(2, std::make_shared<MovePlayerState>());
		player->GetComponent<SpriteComponent>()->SetAnimationToState(3, std::make_shared<DigPlayerState>());
		player->GetComponent<SpriteComponent>()->SetAnimationToState(4, std::make_shared<AttackPlayerState>());
		player->GetComponent<SpriteComponent>()->SetAnimationToState(5, std::make_shared<DeadPlayerState>());

		ServiceLocator::GetInputManager()->AddCommand(std::make_shared<UpCommand>(), ControllerButton::ButtonUp, SDLK_w, player.get());
		ServiceLocator::GetInputManager()->AddCommand(std::make_shared<DownCommand>(), ControllerButton::ButtonDown, SDLK_z, player.get());
		ServiceLocator::GetInputManager()->AddCommand(std::make_shared<LeftCommand>(), ControllerButton::ButtonLeft, SDLK_a, player.get());
		ServiceLocator::GetInputManager()->AddCommand(std::make_shared<RightCommand>(), ControllerButton::ButtonRight, SDLK_d, player.get());
		ServiceLocator::GetInputManager()->AddCommand(std::make_shared<AttackCommand>(), ControllerButton::ButtonX, SDLK_LSHIFT, player.get());
		break;
	}
	

	m_Scene->Add(player);
}

void dae::SceneLoader::AddNpc(NPCType type, float x, float y) const
{
	std::shared_ptr<GameObject> NPC = std::make_shared<GameObject>();
	NPC->AddComponent(std::make_shared<RenderComponent>());
	NPC->AddComponent(std::make_shared<CollisionComponent>());
	NPC->AddComponent(std::make_shared<TransformComponent>(x, y));
	NPC->AddComponent(std::make_shared<MoveComponent>());
	NPC->AddComponent(std::make_shared<NpcComponent>(type));
	NPC->AddComponent(std::make_shared<TextureComponent>());
	

	switch (type)
	{
	default:;

	case NPCType::ROCK:
		NPC->SetName("Rock");
		NPC->GetComponent<TextureComponent>()->SetTexture(ServiceLocator::GetResourceManager()->GetTexture(12));
		NPC->GetComponent<MoveComponent>()->SetIsStatic(true);
		break;
	case NPCType::POOKA:
		NPC->SetName("Pooka");

		NPC->AddComponent(std::make_shared<SpriteComponent>());
		NPC->GetComponent<TextureComponent>()->SetTexture(ServiceLocator::GetResourceManager()->GetTexture(02));
		NPC->GetComponent<SpriteComponent>()->SetAnimationToState(11, std::make_shared<IdlePlayerState>());
		NPC->GetComponent<SpriteComponent>()->SetAnimationToState(12, std::make_shared<MovePlayerState>());
		NPC->GetComponent<SpriteComponent>()->SetAnimationToState(15, std::make_shared<DeadPlayerState>());
		break;
	case NPCType::FYGAR:
		NPC->SetName("Fygar");
		break;
	}

	m_Scene->Add(NPC);
}

void dae::SceneLoader::AddFPS(std::shared_ptr<dae::Font> font, const SDL_Color& color) const
{
	std::shared_ptr<GameObject> go;
	go = std::make_shared<GameObject>();
	go->AddComponent(std::make_shared<TransformComponent>(0.f, 0.f));
	go->AddComponent(std::make_shared<RenderComponent>());
	go->AddComponent(std::make_shared<TextureComponent>());
	go->AddComponent(std::make_shared<TextComponent>("00FPS", font));
	go->AddComponent(std::make_shared<FPSComponent>());
	go->GetComponent<TextComponent>()->SetColor(color);
	m_Scene->Add(go);
}

void dae::SceneLoader::GenerateTile() const
{
	/*ServiceLocator::GetLevelManager()->Reset();*/
	for (auto x = 0; x < 14; ++x)
	{
		for (auto y = 0; y < 17; ++y)
		{
			auto tile = std::make_shared<GameObject>();
			tile->AddComponent(std::make_shared<RenderComponent>());
			tile->AddComponent(std::make_shared<TransformComponent>(static_cast<float>(x) * 32, static_cast<float>(y) * 32));
			tile->AddComponent(std::make_shared<TextureComponent>());
			tile->AddComponent(std::make_shared<TileComponent>(TileState::EMPITY, x, y));
			tile->GetComponent<TileComponent>()->SetTileState(TileState::EMPITY);
			if (y <= 1)
				tile->GetComponent<TileComponent>()->SetTileState(TileState::EMPITY);
			else
				tile->GetComponent<TileComponent>()->SetTileState(TileState::FREE);
			m_Scene->Add(tile);
		}
	}
}

void dae::SceneLoader::AddBackground(UINT textureID) const
{
	std::shared_ptr<GameObject> go;
	go = std::make_shared<GameObject>();
	go->AddComponent(std::make_shared<TransformComponent>(0.f, 0.f));
	go->AddComponent(std::make_shared<RenderComponent>());
	go->AddComponent(std::make_shared<TextureComponent>());
	go->GetComponent<TextureComponent>()->SetTexture(ServiceLocator::GetResourceManager()->GetTexture(textureID));
	m_Scene->Add(go);
}

void dae::SceneLoader::AddText(std::shared_ptr<Font> font, const SDL_Color& color, std::string text, float x, float y) const
{
	std::shared_ptr<GameObject> go;
	go = std::make_shared<GameObject>();
	go->AddComponent(std::make_shared<TransformComponent>(x, y));
	go->AddComponent(std::make_shared<RenderComponent>());
	go->AddComponent(std::make_shared<TextureComponent>());
	go->AddComponent(std::make_shared<TextComponent>(text, font));
	go->GetComponent<TextComponent>()->SetColor(color);
	m_Scene->Add(go);
}
