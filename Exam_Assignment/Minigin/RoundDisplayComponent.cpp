#include "MiniginPCH.h"
#include "RoundDisplayComponent.h"
#include "TextComponent.h"
#include "ServiceLocator.h"
#include "GameObject.h"

void dae::RoundDisplayComponent::onNotify(GameObject& , NotifyEvent& event)
{
	if (event == NotifyEvent::EVENT_RESET || event == NotifyEvent::EVENT_VALUE_CHECK)
	{
		auto scene = static_cast<int>(ServiceLocator::GetSceneManager()->GetActiveSceneIndex());
		if (scene != 0)
			m_Rounds = (scene - 1) % 2;
		else
			m_Rounds = 0;

		m_NeedUpdate = true;
	}
}

void dae::RoundDisplayComponent::AddDisplay()
{
	std::shared_ptr<Font> font;
	font = m_Resource->LoadFont("emulogic.ttf", 16);

	auto text = std::make_shared<TextComponent>("ROUNDS:0", font);
	m_pTextComponent = text.get();
	m_pTextComponent->SetColor({ 255, 255, 255 });
	GetGameObject()->AddComponent(text);
}

void dae::RoundDisplayComponent::Initialize()
{
	m_Resource = ServiceLocator::GetResourceManager();
	AddDisplay();
}

void dae::RoundDisplayComponent::Update(float )
{
	if(m_NeedUpdate)
	{
		std::string str = "ROUNDS:" + std::to_string(m_Rounds);
		m_pTextComponent->SetText(str.c_str());

		m_NeedUpdate = false;
	}
	
}
