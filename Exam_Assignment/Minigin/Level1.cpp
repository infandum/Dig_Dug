#include "MiniginPCH.h"
#include "Components.h"
#include "GameObject.h"
#include "Level1.h"

dae::Level1::Level1()
	:Scene("Level1")
{
}

void dae::Level1::Initialize()
{
	auto go = std::make_shared<GameObject>();
	go->AddComponent(new TransformComponent());
	go->AddComponent(new TextureComponent());
	go->GetComponent<TextureComponent>()->SetTexture("images/background.png");
	go->GetComponent<TransformComponent>()->SetPosition(200, 200);
	Add(go);
}