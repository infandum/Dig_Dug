#include "MiniginPCH.h"
#include "Components.h"
#include "GameObject.h"
#include "ServiceLocator.h"

void dae::HealthDisplayComponent::onNotify(GameObject& gameObject, NotifyEvent& event)
{
	if (event == NotifyEvent::EVENT_RESET || event == NotifyEvent::EVENT_VALUE_CHECK)
	{
		m_Health = gameObject.GetComponent<PlayerComponent>()->GetHealth();
		m_NeedUpdate = true;
	}
}

void dae::HealthDisplayComponent::AddDisplay()
{
	std::shared_ptr<Font> font;
	font = m_Resource->LoadFont("emulogic.ttf", 16);

	auto text = std::make_shared<TextComponent>("HP:", font);
	m_pTextComponent = text.get();
	m_pTextComponent->SetColor({ 255, 255, 255 });
	GetGameObject()->AddComponent(text);
}

void dae::HealthDisplayComponent::Initialize()
{
	m_Resource = ServiceLocator::GetResourceManager();
	AddDisplay();
}

void dae::HealthDisplayComponent::Update(float  )
{
	if (m_NeedUpdate)
	{
		std::string str = "HP:" + std::to_string(m_Health);
		m_pTextComponent->SetText(str.c_str());
	
		m_NeedUpdate = false;
	}
}
