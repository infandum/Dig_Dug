#include "MiniginPCH.h"
#include "Components.h"
#include "GameObject.h"
#include "ServiceLocator.h"

void dae::HealthDisplayComponent::onNotify(GameObject& gameObject, NotifyEvent& event)
{
	if (event == NotifyEvent::EVENT_LIFE_CHECK)
		m_Health = gameObject.GetComponent<PlayerComponent>()->GetHealth();
}

void dae::HealthDisplayComponent::Initialize()
{
	const auto resource = ServiceLocator::GetResourceManager();

	std::shared_ptr<Font> font;
	font = resource->LoadFont("emulogic.ttf", 16);
	auto text = std::make_shared<TextComponent>("HEALTH", font);
	text->SetColor({255, 255, 255});
	m_pTextComponent = text.get();
	GetGameObject()->AddComponent(text);
}

void dae::HealthDisplayComponent::Update(float  )
{

	std::string str = "HP:" + std::to_string(m_Health);
	m_pTextComponent->SetText(str.c_str());
}
