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


#include "NpcStates.h"
#include "PlayerStates.h"
#include "RoundDisplayComponent.h"

//TODO: FILE READING LEVEL LOADING
void dae::SceneLoader::Initialize()
{
	auto resource = ServiceLocator::GetResourceManager();
	resource->LoadTexture("images/DigDug_BackGround.png", 01);
	resource->LoadTexture("images/SpriteSheet.png", 02);

	resource->LoadTexture("images/DugDirt.png", 03);
	resource->LoadTexture("images/DugDirtFloor.png", 04);
	resource->LoadTexture("images/DugDirtWall.png", 05);

	resource->LoadTexture("images/Collision.png", 10000);


	auto animations = ServiceLocator::GetAnimationManager();
	animations->SetAnimationSpeed(10.0f);

	//DIG DUG
	animations->LoadSpriteClip(SpriteClip{ "Idle", {0, 0}, { 32 , 32 }, 1, 2, true, false }, 1);					//Idle
	animations->LoadSpriteClip(SpriteClip{ "Walk", {0, 0}, { 32 , 32 }, 1, 2, true, true }, 2);						//Walk
	animations->LoadSpriteClip(SpriteClip{ "Dig", {0, 32}, { 32 , 32 }, 1, 2, true, true }, 3);						//Dig
	animations->LoadSpriteClip(SpriteClip{ "Attack", {0, 64}, { 32 , 32 }, 0, 1, true, false }, 4);					//Attack
	animations->LoadSpriteClip(SpriteClip{ "Dead", {0, 224}, { 32 , 32 }, 0, 4, true, false }, 5);					//Dead
	animations->LoadSpriteClip(SpriteClip{ "Pump", {0, 160}, { 32 , 32 }, 0, 2, true, true }, 6);					//Pump
	animations->LoadSpriteClip(SpriteClip{ "Crushed", {0, 192}, { 32, 32 }, 0, 2, true, false }, 7);				//Crushed

	animations->LoadSpriteClip(SpriteClip{ "Spear", {0, 96}, { 64 , 64 }, 0, 1, true, false }, 9);					//Spear

	//POOKA
	animations->LoadSpriteClip(SpriteClip{ "Idle", {0, 256}, { 32 , 32 }, 1, 2, false, false }, 11);				//Idle
	animations->LoadSpriteClip(SpriteClip{ "Walk", {0, 256}, { 32 , 32 }, 0, 2, false, true }, 12);					//Walk
	animations->LoadSpriteClip(SpriteClip{ "Ghost", {192, 256}, { 32 , 32 }, 0, 2, false, true, 1.f, true }, 13);	//Ghost
										   
	animations->LoadSpriteClip(SpriteClip{ "Inflate", {0, 288}, { 64 , 64 }, 0, 4, false, false, 0.5f }, 15);		//Inflate
	animations->LoadSpriteClip(SpriteClip{ "Deflate", {0, 288}, { 64 , 64 }, 0, 4, false, false, -0.5f }, 16);		//Deflate
	animations->LoadSpriteClip(SpriteClip{ "Crushed", {128, 256}, { 32 , 32 }, 0, 2, false, false }, 17);			//Crushed
	animations->LoadSpriteClip(SpriteClip{ "DEAD", {0, 288}, { 64 , 64 }, 3, 4, false, false, 0.5f }, 18);			//DEAD
	animations->LoadSpriteClip(SpriteClip{ "Chase", {0, 256}, { 32 , 32 }, 0, 2, false, true }, 19);				//Chase

	//Fygar																							
	animations->LoadSpriteClip(SpriteClip{ "Idle", {0, 352}, { 32 , 32 }, 1, 2, false, false }, 21);				//Idle
	animations->LoadSpriteClip(SpriteClip{ "Walk", {0, 352}, { 32 , 32 }, 0, 2, false, true }, 22);					//Walk
	animations->LoadSpriteClip(SpriteClip{ "Ghost", {192, 352}, { 32 , 32 }, 0, 2, false, true, 1.f, true }, 23);	//Ghost
	animations->LoadSpriteClip(SpriteClip{ "Attack", {0, 384}, { 32 , 32 }, 0, 2, false, true }, 24);				//Charging
	animations->LoadSpriteClip(SpriteClip{ "Inflate", {0, 448}, { 64 , 64 }, 0, 4, false, false, 0.5f }, 25);		//Inflate
	animations->LoadSpriteClip(SpriteClip{ "Deflate", {0, 448}, { 64 , 64 }, 0, 4, false, false, -0.5f }, 26);		//Deflate									   
	animations->LoadSpriteClip(SpriteClip{ "Crushed", {128, 352}, { 32 , 32 }, 0, 1, false, false }, 27);			//Crushed
	animations->LoadSpriteClip(SpriteClip{ "DEAD", {0, 448}, { 64 , 64 }, 3, 4, false, false, 0.5f }, 28);			//DEAD				
	animations->LoadSpriteClip(SpriteClip{ "Chase", {0, 352}, { 32 , 32 }, 0, 2, false, true }, 29);				//Chase
	animations->LoadSpriteClip(SpriteClip{ "Attack", {0, 352}, { 32 , 32 }, 1, 2, false, false }, 30);				//Attack

	animations->LoadSpriteClip(SpriteClip{ "Fire", {0, 416}, { 96 , 32 }, 0, 3, false, false }, 31);				//Fire

	//Rock																							
	animations->LoadSpriteClip(SpriteClip{ "Idle", {288, 352}, { 32 , 32 }, 0, 1, false, false, 1.f, true }, 41);	//Idle
	animations->LoadSpriteClip(SpriteClip{ "Lose", {256, 352}, { 32 , 32 }, 1, 3, false, true, 0.5f, true }, 42);	//Lose
	animations->LoadSpriteClip(SpriteClip{ "Fall", {288, 352}, { 32 , 32 }, 0, 1, false, false, 1.f, true }, 43);	//Falling
	animations->LoadSpriteClip(SpriteClip{ "Dead", {352, 352}, { 32 , 32 }, 0, 4, false, false, 1.f, true }, 44);	//Dead
}

void dae::SceneLoader::InitScene(dae::SceneList scene)
{
	const auto resource = ServiceLocator::GetResourceManager();

	std::shared_ptr<Font> font;
	SDL_Color color;
	std::shared_ptr<GameObject> go;
	switch (scene)
	{
	case SceneList::MAIN_MENU:
			m_Scene = ServiceLocator::GetSceneManager()->CreateScene("Main menu");

			AddBackground(01);

			GenerateTile();

			font = resource->LoadFont("Lingua.otf", 32);
			AddText(font, {0,0,0}, "Programming 4 Assignment", 16, 116);

			font = resource->LoadFont("Lingua.otf", 24);
			AddText(font, { 0,0,0 }, "2DAE07 - Plettinx Alexander", 32.f * 2.5f, 148);

			font = resource->LoadFont("emulogic.ttf", 32);
			AddText(font, { 0,0,0 }, "DigDug", 124, 70);

			font = resource->LoadFont("emulogic.ttf", 12);
			AddFPS(font, color);

			AddMenu();

		break;
	case SceneList::LEVEL_1_SINGLE:
		m_Scene = ServiceLocator::GetSceneManager()->CreateScene("Level Single");

		AddBackground(01);
		
		GenerateTile();
		
		AddPlayer(PlayerType::PLAYER_DIGDUG, 32.f * 6, 32.f * 9);
		
		AddNpc(NPCType::POOKA, 32.f, 32.f * 4);
		
		AddNpc(NPCType::POOKA, 32.f * 10, 32.f * 4);

		AddNpc(NPCType::POOKA, 32.f * 9, 32.f * 14);
		
		AddNpc(NPCType::FYGAR, 32.f * 3, 32.f * 12);
		
		AddNpc(NPCType::ROCK, 32.f * 3, 32.f * 13);
		
		AddNpc(NPCType::ROCK, 32.f * 4, 32.f * 5);

		AddNpc(NPCType::ROCK, 32.f * 10, 32.f * 11);
		
		font = resource->LoadFont("emulogic.ttf", 12);
		AddFPS(font, color);

		AddLevelExit();

		break;
	case SceneList::LEVEL_2_SINGLE:
		m_Scene = ServiceLocator::GetSceneManager()->CreateScene("Level Single");

		AddBackground(01);

		GenerateTile();

		AddPlayer(PlayerType::PLAYER_DIGDUG, 32.f * 6, 32.f * 9);

		AddNpc(NPCType::POOKA, 32.f, 32.f * 4);

		AddNpc(NPCType::POOKA, 32.f * 10, 32.f * 4);

		AddNpc(NPCType::POOKA, 32.f * 9, 32.f * 14);

		AddNpc(NPCType::FYGAR, 32.f * 3, 32.f * 12);

		AddNpc(NPCType::ROCK, 32.f * 3, 32.f * 13);

		AddNpc(NPCType::ROCK, 32.f * 4, 32.f * 5);

		AddNpc(NPCType::ROCK, 32.f * 10, 32.f * 11);

		font = resource->LoadFont("emulogic.ttf", 12);
		AddFPS(font, color);

		AddLevelExit();

		break;
	case SceneList::LEVEL_1_COOP:
		m_Scene = ServiceLocator::GetSceneManager()->CreateScene("Level Coop");

		
		AddBackground(01);

		GenerateTile();
		
		AddPlayer(PlayerType::PLAYER_DIGDUG, 32.f * 7, 32.f * 9);

		AddPlayer(PlayerType::PLAYER_DIGDUG, 32.f * 5, 32.f * 9, 32.f * 17.f, 64 * 5.5f);

		AddNpc(NPCType::POOKA, 32.f, 32.f * 4);

		AddNpc(NPCType::POOKA, 32.f * 10, 32.f * 4);

		AddNpc(NPCType::POOKA, 32.f * 9, 32.f * 14);

		AddNpc(NPCType::FYGAR, 32.f * 3, 32.f * 12);

		AddNpc(NPCType::ROCK, 32.f * 3, 32.f * 13);

		AddNpc(NPCType::ROCK, 32.f * 4, 32.f * 5);

		AddNpc(NPCType::ROCK, 32.f * 10, 32.f * 11);

		font = resource->LoadFont("emulogic.ttf", 12);
		AddFPS(font, color);

		AddLevelExit();

		break;
	case SceneList::LEVEL_2_COOP:
		m_Scene = ServiceLocator::GetSceneManager()->CreateScene("Level Coop");


		AddBackground(01);

		GenerateTile();

		AddPlayer(PlayerType::PLAYER_DIGDUG, 32.f * 7, 32.f * 9);

		AddPlayer(PlayerType::PLAYER_DIGDUG, 32.f * 5, 32.f * 9, 32.f * 17.f, 64 * 5.5f);

		AddNpc(NPCType::POOKA, 32.f, 32.f * 4);

		AddNpc(NPCType::POOKA, 32.f * 10, 32.f * 4);

		AddNpc(NPCType::POOKA, 32.f * 9, 32.f * 14);

		AddNpc(NPCType::FYGAR, 32.f * 3, 32.f * 12);

		AddNpc(NPCType::ROCK, 32.f * 3, 32.f * 13);

		AddNpc(NPCType::ROCK, 32.f * 4, 32.f * 5);

		AddNpc(NPCType::ROCK, 32.f * 10, 32.f * 11);

		font = resource->LoadFont("emulogic.ttf", 12);
		AddFPS(font, color);

		AddLevelExit();

		break;
	case SceneList::LEVEL_VS:
		m_Scene = ServiceLocator::GetSceneManager()->CreateScene("Level VS");

		AddBackground(01);

		GenerateTile();
		
		AddPlayer(PlayerType::PLAYER_DIGDUG, 32.f * 6, 32.f * 9);
		
		AddPlayer(PlayerType::PLAYER_FYGAR, 32.f * 3, 32.f * 12, 72.f, 32.f * 17.f, 64 * 5.5f);
		
		AddNpc(NPCType::POOKA, 32.f, 32.f * 4);

		AddNpc(NPCType::POOKA, 32.f * 10, 32.f * 4);

		AddNpc(NPCType::POOKA, 32.f * 9, 32.f * 14);

		AddNpc(NPCType::ROCK, 32.f * 3, 32.f * 13);

		AddNpc(NPCType::ROCK, 32.f * 4, 32.f * 5);

		AddNpc(NPCType::ROCK, 32.f * 10, 32.f * 11);

		font = resource->LoadFont("emulogic.ttf", 12);
		AddFPS(font, color);

		AddLevelExit();

		break;
	default: ;
	}
}

void dae::SceneLoader::PostInitScene(SceneList scene)
{
	auto level = ServiceLocator::GetLevelManager();

	switch (scene)
	{
	default: 
		break;
	case SceneList::MAIN_MENU:
		break;
	case SceneList::LEVEL_1_SINGLE:
		level->CreateTunnel(6, 2, Direction::DOWN, 7);
		level->CreateTunnel(5, 9, Direction::RIGHT, 2);

		level->CreateTunnel(1, 4, Direction::DOWN, 4);

		level->CreateTunnel(2, 12, Direction::RIGHT, 3);

		level->CreateTunnel(9, 4, Direction::RIGHT, 3);

		level->CreateTunnel(9, 11, Direction::DOWN, 4);
		break;
	case SceneList::LEVEL_2_SINGLE:
		level->CreateTunnel(6, 2, Direction::DOWN, 7);
		level->CreateTunnel(5, 9, Direction::RIGHT, 2);

		level->CreateTunnel(1, 8, Direction::RIGHT, 2);

		level->CreateTunnel(8, 5, Direction::RIGHT, 2);

		level->CreateTunnel(6, 11, Direction::RIGHT, 2);

		level->CreateTunnel(8, 14, Direction::RIGHT, 2);

		level->CreateTunnel(1, 10, Direction::DOWN, 2);
		break;
	case SceneList::LEVEL_1_COOP:
		level->CreateTunnel(6, 2, Direction::DOWN, 7);
		level->CreateTunnel(5, 9, Direction::RIGHT, 2);

		level->CreateTunnel(1, 4, Direction::DOWN, 4);

		level->CreateTunnel(2, 12, Direction::RIGHT, 3);

		level->CreateTunnel(9, 4, Direction::RIGHT, 3);

		level->CreateTunnel(9, 11, Direction::DOWN, 4);
		break;
	case SceneList::LEVEL_2_COOP:
		level->CreateTunnel(6, 2, Direction::DOWN, 7);
		level->CreateTunnel(5, 9, Direction::RIGHT, 2);

		level->CreateTunnel(1, 8, Direction::RIGHT, 2);

		level->CreateTunnel(8, 5, Direction::RIGHT, 2);

		level->CreateTunnel(6, 11, Direction::RIGHT, 2);

		level->CreateTunnel(8, 14, Direction::RIGHT, 2);

		level->CreateTunnel(1, 10, Direction::DOWN, 2);

		break;
	case SceneList::LEVEL_VS:
		level->CreateTunnel(6, 2, Direction::DOWN, 7);
		level->CreateTunnel(5, 9, Direction::RIGHT, 2);

		level->CreateTunnel(6, 2, Direction::DOWN, 7);
		level->CreateTunnel(5, 9, Direction::RIGHT, 2);

		level->CreateTunnel(1, 4, Direction::DOWN, 4);

		level->CreateTunnel(2, 12, Direction::RIGHT, 3);

		level->CreateTunnel(9, 4, Direction::RIGHT, 3);

		level->CreateTunnel(9, 11, Direction::DOWN, 4);
		break;
	}

}

void dae::SceneLoader::ResetScene(SceneList scene)
{
	auto level = ServiceLocator::GetLevelManager();
	level->SetActiveScene(ServiceLocator::GetSceneManager()->GetActiveSceneIndex());

	auto physics = ServiceLocator::GetPhysicsManager();
	physics->SetActiveScene(ServiceLocator::GetSceneManager()->GetActiveSceneIndex());

	level->Reset();
	physics->Reset();
	
	PostInitScene(scene);
}

void dae::SceneLoader::SetScene(const int& index)
{
	ServiceLocator::GetSceneManager()->SetActive(index);
}

void dae::SceneLoader::AddMenu() const
{
	std::shared_ptr<GameObject> menu = std::make_shared<GameObject>();
	menu->SetName("Menu");
	menu->AddComponent(std::make_shared<TransformComponent>(10.f, 32.f * 5.25f));
	menu->AddComponent(std::make_shared<RenderComponent>());
	menu->AddComponent(std::make_shared<MainMenuComponent>());
	ServiceLocator::GetInputManager()->AddCommand(std::make_shared<ExitCommand>(), ControllerButton::ButtonStart, SDLK_ESCAPE, menu.get());
	ServiceLocator::GetInputManager()->AddCommand(std::make_shared<EnterCommand>(), ControllerButton::ButtonA, SDLK_SPACE, menu.get());
	ServiceLocator::GetInputManager()->AddCommand(std::make_shared<UpCommand>(), ControllerButton::ButtonUp, SDLK_UP, menu.get());
	ServiceLocator::GetInputManager()->AddCommand(std::make_shared<DownCommand>(), ControllerButton::ButtonDown, SDLK_DOWN, menu.get());
	m_Scene->Add(menu);
}

void dae::SceneLoader::AddLevelExit() const
{
	std::shared_ptr<GameObject> menu = std::make_shared<GameObject>();
	menu->AddComponent(std::make_shared<InputComponent>());
	menu->SetName("Menu");
	ServiceLocator::GetInputManager()->AddCommand(std::make_shared<ExitCommand>(), ControllerButton::ButtonStart, SDLK_ESCAPE, menu.get());
	m_Scene->Add(menu);
}

void dae::SceneLoader::AddPlayer(PlayerType type, float playerX, float playerY, float guiHPX, float guiHPY, float guiPointsX, float guiPointsY) const
{
	auto level = ServiceLocator::GetLevelManager();
	auto input = ServiceLocator::GetInputManager();
	std::shared_ptr<GameObject> player = std::make_shared<GameObject>();
	
	player->AddComponent(std::make_shared<RenderComponent>());
	player->AddComponent(std::make_shared<CollisionComponent>());
	player->AddComponent(std::make_shared<TransformComponent>(playerX, playerY));
	player->AddComponent(std::make_shared<TextureComponent>());
	player->AddComponent(std::make_shared<SpriteComponent>(IdlePlayerState()));
	player->AddComponent(std::make_shared<MoveComponent>());
	player->AddComponent(std::make_shared<PlayerComponent>(type));
	player->GetComponent<TextureComponent>()->SetTexture(ServiceLocator::GetResourceManager()->GetTexture(02));

	switch (type)
	{
	default:;

	case PlayerType::PLAYER_DIGDUG:
		player->SetName("PLAYER_DIGDUG: " + m_Scene->GetName());
		player->GetComponent<SpriteComponent>()->SetAnimationToState(1, std::make_shared<IdlePlayerState>());
		player->GetComponent<SpriteComponent>()->SetAnimationToState(2, std::make_shared<MovePlayerState>());
		player->GetComponent<SpriteComponent>()->SetAnimationToState(3, std::make_shared<DigPlayerState>());
		player->GetComponent<SpriteComponent>()->SetAnimationToState(4, std::make_shared<AttackPlayerState>());
		player->GetComponent<SpriteComponent>()->SetAnimationToState(5, std::make_shared<DeadPlayerState>());
		player->GetComponent<SpriteComponent>()->SetAnimationToState(6, std::make_shared<ActionPlayerState>());
		player->GetComponent<SpriteComponent>()->SetAnimationToState(7, std::make_shared<CrushedPlayerState>());
		
		break;

	case PlayerType::PLAYER_FYGAR:
		player->SetName("PLAYER_FYGAR: " + m_Scene->GetName());
		player->GetComponent<SpriteComponent>()->SetAnimationToState(21, std::make_shared<IdlePlayerState>());
		player->GetComponent<SpriteComponent>()->SetAnimationToState(22, std::make_shared<MovePlayerState>());
		player->GetComponent<SpriteComponent>()->SetAnimationToState(23, std::make_shared<DigPlayerState>());
		player->GetComponent<SpriteComponent>()->SetAnimationToState(24, std::make_shared<AttackPlayerState>());
		player->GetComponent<SpriteComponent>()->SetAnimationToState(25, std::make_shared<DeadPlayerState>());
		player->GetComponent<SpriteComponent>()->SetAnimationToState(27, std::make_shared<CrushedPlayerState>());
		
		break;
	}

	level->AddPlayer(player->GetComponent<PlayerComponent>().get());
	m_Scene->Add(player);
	
	if(level->GetPlayerCount() == 1)
	{
		input->AddCommand(std::make_shared<UpCommand>(), ControllerButton::ButtonUp, SDLK_w, player.get());
		input->AddCommand(std::make_shared<DownCommand>(), ControllerButton::ButtonDown, SDLK_s, player.get());
		input->AddCommand(std::make_shared<LeftCommand>(), ControllerButton::ButtonLeft, SDLK_a, player.get());
		input->AddCommand(std::make_shared<RightCommand>(), ControllerButton::ButtonRight, SDLK_d, player.get());
		input->AddCommand(std::make_shared<AttackCommand>(), ControllerButton::ButtonX, SDLK_LSHIFT, player.get());
	}
	else
	{
		input->AddCommand(std::make_shared<UpCommand>(), ControllerButton::ButtonNone, SDLK_UP, player.get());
		input->AddCommand(std::make_shared<DownCommand>(), ControllerButton::ButtonNone, SDLK_DOWN, player.get());
		input->AddCommand(std::make_shared<LeftCommand>(), ControllerButton::ButtonNone, SDLK_LEFT, player.get());
		input->AddCommand(std::make_shared<RightCommand>(), ControllerButton::ButtonNone, SDLK_RIGHT, player.get());
		input->AddCommand(std::make_shared<AttackCommand>(), ControllerButton::ButtonNone, SDLK_RSHIFT, player.get());
	}

	//HEALTH GUI
	std::shared_ptr<GameObject> gui;
	gui = std::make_shared<GameObject>();
	gui->SetName("GUI>>HP: " + player->GetName());
	gui->AddComponent(std::make_shared<TransformComponent>(guiHPX, guiHPY));
	gui->AddComponent(std::make_shared<RenderComponent>());
	gui->AddComponent(std::make_shared<TextureComponent>());
	gui->AddComponent(std::make_shared<HealthDisplayComponent>());

	player->GetComponent<PlayerComponent>()->AddObserver(gui->GetComponent<HealthDisplayComponent>());
	m_Scene->Add(gui);

	//POINTS GUI
	gui = std::make_shared<GameObject>();
	gui->SetName("GUI>>POINTS: " + player->GetName());
	gui->AddComponent(std::make_shared<TransformComponent>(guiPointsX, guiPointsY));
	gui->AddComponent(std::make_shared<RenderComponent>());
	gui->AddComponent(std::make_shared<TextureComponent>());
	gui->AddComponent(std::make_shared<PointDisplayComponent>());

	player->GetComponent<PlayerComponent>()->AddObserver(gui->GetComponent<PointDisplayComponent>());
	m_Scene->Add(gui);

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
	NPC->GetComponent<TextureComponent>()->SetTexture(ServiceLocator::GetResourceManager()->GetTexture(02));

	switch (type)
	{
	default:;

	case NPCType::ROCK:
		NPC->SetName("Rock");
		NPC->GetComponent<MoveComponent>()->SetIsStatic(true);
		NPC->AddComponent(std::make_shared<SpriteComponent>(RockIdleState()));
		NPC->GetComponent<SpriteComponent>()->SetAnimationToState(41, std::make_shared<RockIdleState>());
		NPC->GetComponent<SpriteComponent>()->SetAnimationToState(42, std::make_shared<RockLoseState>());
		NPC->GetComponent<SpriteComponent>()->SetAnimationToState(43, std::make_shared<RockFallingState>());
		NPC->GetComponent<SpriteComponent>()->SetAnimationToState(44, std::make_shared<RockDeadState>());

		break;
	case NPCType::POOKA:
		NPC->SetName("Pooka");

		NPC->AddComponent(std::make_shared<SpriteComponent>(PookaIdleState()));
		NPC->GetComponent<SpriteComponent>()->SetAnimationToState(11, std::make_shared<PookaIdleState>());
		NPC->GetComponent<SpriteComponent>()->SetAnimationToState(12, std::make_shared<PookaMoveState>());
		NPC->GetComponent<SpriteComponent>()->SetAnimationToState(13, std::make_shared<PookaGhostState>());
		NPC->GetComponent<SpriteComponent>()->SetAnimationToState(15, std::make_shared<PookaInflateState>());
		NPC->GetComponent<SpriteComponent>()->SetAnimationToState(16, std::make_shared<PookaDeflateState>());
		NPC->GetComponent<SpriteComponent>()->SetAnimationToState(17, std::make_shared<PookaCrushState>());
		NPC->GetComponent<SpriteComponent>()->SetAnimationToState(18, std::make_shared<PookaDeadState>());
		break;
	case NPCType::FYGAR:
		NPC->SetName("Fygar");
		NPC->AddComponent(std::make_shared<SpriteComponent>(FygarIdleState()));
		NPC->GetComponent<SpriteComponent>()->SetAnimationToState(21, std::make_shared<FygarIdleState>());
		NPC->GetComponent<SpriteComponent>()->SetAnimationToState(22, std::make_shared<FygarMoveState>());
		
		NPC->GetComponent<SpriteComponent>()->SetAnimationToState(23, std::make_shared<FygarGhostState>());
		NPC->GetComponent<SpriteComponent>()->SetAnimationToState(24, std::make_shared<FygarChargingState>());
		
		NPC->GetComponent<SpriteComponent>()->SetAnimationToState(25, std::make_shared<FygarInflateState>());
		NPC->GetComponent<SpriteComponent>()->SetAnimationToState(26, std::make_shared<FygarDeflateState>());
		NPC->GetComponent<SpriteComponent>()->SetAnimationToState(27, std::make_shared<FygarCrushState>());
		NPC->GetComponent<SpriteComponent>()->SetAnimationToState(28, std::make_shared<FygarDeadState>());

		NPC->GetComponent<SpriteComponent>()->SetAnimationToState(30, std::make_shared<FygarAttackState>());
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
	const auto resource = ServiceLocator::GetResourceManager();
	for (auto x = 0; x < 14; ++x)
	{
		for (auto y = 0; y < 17; ++y)
		{
			auto tile = std::make_shared<GameObject>();
			tile->AddComponent(std::make_shared<RenderComponent>());
			tile->AddComponent(std::make_shared<TransformComponent>(static_cast<float>(x) * 32, static_cast<float>(y) * 32));
			tile->AddComponent(std::make_shared<TextureComponent>(resource->GetTexture(03)));
			tile->AddComponent(std::make_shared<TileComponent>(TileState::EMPITY, x, y));
			tile->GetComponent<TileComponent>()->SetTileState(TileState::EMPITY);
			if (y <= 1)
				tile->GetComponent<TileComponent>()->SetTileState(TileState::EMPITY);
			else
				tile->GetComponent<TileComponent>()->SetTileState(TileState::FREE);
			m_Scene->Add(tile);
		}
	}

	//ROUNDS GUI
	std::shared_ptr<GameObject> gui;
	gui = std::make_shared<GameObject>();
	gui->SetName("GUI>>ROUNDS");
	gui->AddComponent(std::make_shared<TransformComponent>(32.f * 9.9f, 32.f * 17.1f));
	gui->AddComponent(std::make_shared<RenderComponent>());
	gui->AddComponent(std::make_shared<TextureComponent>());
	gui->AddComponent(std::make_shared<RoundDisplayComponent>());

	ServiceLocator::GetLevelManager()->AddObserver(gui->GetComponent<RoundDisplayComponent>());
	m_Scene->Add(gui);
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
