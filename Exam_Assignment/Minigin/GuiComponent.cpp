#include "MiniginPCH.h"
#include "Components.h"
#include "GameObject.h"
#include "ServiceLocator.h"

void dae::GuiComponent::onNotify(GameObject& , NotifyEvent& event)
{
	if(event == NotifyEvent::EVENT_LIFE_CHECK)
		return;
}

void dae::GuiComponent::Initialize()
{
	const auto resource = ServiceLocator::GetResourceManager();

	std::shared_ptr<Font> font;
	font = resource->LoadFont("emulogic.ttf", 16);

	std::shared_ptr<GameObject> go;
	go = std::make_shared<GameObject>();
	go->AddComponent(std::make_shared<TransformComponent>(GetGameObject()->GetTransform()->GetInitPosition().x, GetGameObject()->GetTransform()->GetInitPosition().y));
	go->AddComponent(std::make_shared<RenderComponent>());
	go->AddComponent(std::make_shared<TextureComponent>());
	go->AddComponent(std::make_shared<TextComponent>("HEALTH", font));
	go->GetComponent<TextComponent>()->SetColor({255, 255, 255});
	GetGameObject()->AddChild(go);
}

void dae::GuiComponent::Update(float  )
{
}
