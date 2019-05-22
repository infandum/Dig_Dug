#include "MiniginPCH.h"
#include "PointDisplayComponent.h"
#include "TextComponent.h"
#include "GameObject.h"
#include "ServiceLocator.h"

void dae::PointDisplayComponent::onNotify(GameObject & gameObject, NotifyEvent & event)
{
	if (event == NotifyEvent::EVENT_RESET || event == NotifyEvent::EVENT_VALUE_CHECK)
	{
		m_Points = gameObject.GetComponent<PlayerComponent>()->GetPoints();
	}
}

void dae::PointDisplayComponent::AddDisplay()
{
	std::shared_ptr<Font> font;
	font = m_Resource->LoadFont("emulogic.ttf", 16);

	auto text = std::make_shared<TextComponent>("000000", font);
	m_pTextComponent = text.get();
	m_pTextComponent->SetColor({ 255, 255, 255 });
	GetGameObject()->AddComponent(text);
}

void dae::PointDisplayComponent::Initialize()
{
	m_Resource = ServiceLocator::GetResourceManager();
	AddDisplay();
}

void dae::PointDisplayComponent::Update(float)
{

	std::string str = std::to_string(m_Points);
	str = std::string(6 - std::to_string(m_Points).length(), '0') + std::to_string(m_Points);
	m_pTextComponent->SetText(str.c_str());
}
