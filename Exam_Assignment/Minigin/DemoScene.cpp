#include "MiniginPCH.h"
#include "DemoScene.h"
#include "GameObject.h"
#include "ServiceLocator.h"
#include "Commands.h"

dae::DemoScene::DemoScene() : Scene("Demo")
{
}


void dae::DemoScene::Initialize()
{
	auto resource = ServiceLocator::GetResourceManager();
	auto input = ServiceLocator::GetInputManager();

	auto animations = ServiceLocator::GetAnimationManager();
	animations->SetAnimationSpeed(10.0f);


	std::shared_ptr<Font> font;
	SDL_Color color;
	std::shared_ptr<GameObject> go;

	resource->LoadTexture("background.jpg", 999);
	resource->LoadTexture("logo.png", 998);

	go = std::make_shared<GameObject>();
	go->AddComponent(std::make_shared<InputComponent>());
	input->AddCommand(std::make_shared<ExitCommand>(), ControllerButton::ButtonSelect, SDLK_ESCAPE, nullptr);
	Add(go);

	go = std::make_shared<GameObject>();
	go->AddComponent(std::make_shared<TransformComponent>(0.f, 0.f));
	go->AddComponent(std::make_shared<RenderComponent>());
	go->AddComponent(std::make_shared<TextureComponent>());
	go->GetComponent<TextureComponent>()->SetTexture(resource->GetTexture(999));
	Add(go);

	go = std::make_shared<GameObject>();
	go->AddComponent(std::make_shared<TransformComponent>(216.f, 180.f));
	go->AddComponent(std::make_shared<RenderComponent>());
	go->AddComponent(std::make_shared<TextureComponent>());
	go->GetComponent<TextureComponent>()->SetTexture(resource->GetTexture(998));
	Add(go);

	font = resource->LoadFont("Lingua.otf", 36);
	go = std::make_shared<GameObject>();
	go->AddComponent(std::make_shared<TransformComponent>(80.f, 20.f));
	go->AddComponent(std::make_shared<RenderComponent>());
	go->AddComponent(std::make_shared<TextureComponent>());
	go->AddComponent(std::make_shared<TextComponent>("Programming 4 Assignment", font));
	Add(go);

	font = resource->LoadFont("Lingua.otf", 30);
	go = std::make_shared<GameObject>();
	go->AddComponent(std::make_shared<TransformComponent>(0.f, 0.f));
	go->AddComponent(std::make_shared<RenderComponent>());
	go->AddComponent(std::make_shared<TextureComponent>());
	go->AddComponent(std::make_shared<TextComponent>("00FPS", font));
	go->AddComponent(std::make_shared<FPSComponent>());
	color = { 255, 255, 0 };
	go->GetComponent<TextComponent>()->SetColor(color);
}