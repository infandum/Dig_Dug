#include "MiniginPCH.h"
#include "DemoScene.h"
#include "Components.h"
#include "GameObject.h"
#include "ResourceManager.h"

dae::DemoScene::DemoScene()
	:Scene("Demo")
{

}

void dae::DemoScene::Initialize()
{
	auto go = std::make_shared<GameObject>();
	go->AddComponent(new TransformComponent());
	go->AddComponent(new TextureComponent());
	go->GetComponent<TextureComponent>()->SetTexture("background.jpg");
	Add(go);

	go = std::make_shared<GameObject>();
	go->AddComponent(new TransformComponent());
	go->AddComponent(new TextureComponent());
	go->GetComponent<TextureComponent>()->SetTexture("logo.png");
	go->GetComponent<TransformComponent>()->SetPosition(216, 180);
	Add(go);

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go = std::make_shared<GameObject>();
	go->AddComponent(new TransformComponent());
	go->AddComponent(new TextureComponent());
	go->AddComponent(new TextComponent("Programming 4 Assignment", font));
	go->GetComponent<TransformComponent>()->SetPosition(80, 20);
	Add(go);

	font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 30);
	go = std::make_shared<GameObject>();
	go->AddComponent(new TransformComponent());
	go->AddComponent(new TextureComponent());
	go->AddComponent(new TextComponent("00FPS", font));
	go->AddComponent(new FPSComponent());
	const SDL_Color color{ 255, 255, 0 };
	go->GetComponent<TextComponent>()->SetColor(color);
	Add(go);
}