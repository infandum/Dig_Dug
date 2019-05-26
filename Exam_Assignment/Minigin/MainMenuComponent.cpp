#include "MiniginPCH.h"
#include "MainMenuComponent.h"
#include "GameObject.h"
#include "Components.h"
#include "InputManager.h"
#include "Commands.h"

void dae::MainMenuComponent::SetActiveButton(int index)
{
	if(!m_NeedUpdate)
	{
		m_ActiveButton = index;

		if (m_ActiveButton < 0)
			m_ActiveButton = static_cast<int>(m_pButtons.size()) - 1;

		if (m_ActiveButton >= m_pButtons.size())
			m_ActiveButton = 0;

		m_NeedUpdate = true;
	}
	
}

void dae::MainMenuComponent::NextButton()
{
	auto i = m_ActiveButton;
	i++;
	SetActiveButton(i);
}

void dae::MainMenuComponent::PreviousButton()
{
	auto i = m_ActiveButton;
	i--;
	SetActiveButton(i);
	
}

void dae::MainMenuComponent::SelectButton()
{
	const auto scene = ServiceLocator::GetSceneManager();
	const auto input = ServiceLocator::GetInputManager();

	switch(m_ActiveButton)
	{
	case 0:
		scene->SetActive("Level Single");
		break;
	case 1:
		scene->SetActive("Level Coop");
		break;
	case 2:
		scene->SetActive("Level VS");
		break;
	case 3:
		input->CloseWindow();
		break;
	}
}

void dae::MainMenuComponent::onNotify(GameObject& , NotifyEvent& )
{
}

void dae::MainMenuComponent::Initialize()
{
	const auto resource = ServiceLocator::GetResourceManager();

	std::shared_ptr<Font> font;
	SDL_Color color = {0,0,0};
	font = resource->LoadFont("emulogic.ttf", 32);
	auto go = std::make_shared<GameObject>();
	go->SetName("SinglePlayer");
	go->AddComponent(std::make_shared<TransformComponent>(32.f, 32.f));
	go->AddComponent(std::make_shared<RenderComponent>());
	go->AddComponent(std::make_shared<TextureComponent>());
	go->AddComponent(std::make_shared<TextComponent>("SINGLE MODE", font));
	go->GetComponent<TextComponent>()->SetColor(m_ActiveColor);

	GetGameObject()->AddChild(go);
	m_pButtons.push_back(go->GetComponent<TextComponent>().get());

	go = std::make_shared<GameObject>();
	go->SetName("Coop");
	go->AddComponent(std::make_shared<TransformComponent>(32.f * 2, 32.f  * 3));
	go->AddComponent(std::make_shared<RenderComponent>());
	go->AddComponent(std::make_shared<TextureComponent>());
	go->AddComponent(std::make_shared<TextComponent>("COOP MODE", font));
	go->GetComponent<TextComponent>()->SetColor(m_InActiveColor);

	GetGameObject()->AddChild(go);
	m_pButtons.push_back(go->GetComponent<TextComponent>().get());

	go = std::make_shared<GameObject>();
	go->SetName("Vs");
	go->AddComponent(std::make_shared<TransformComponent>(32.f * 3.25f, 32.f * 5));
	go->AddComponent(std::make_shared<RenderComponent>());
	go->AddComponent(std::make_shared<TextureComponent>());
	go->AddComponent(std::make_shared<TextComponent>("VS MODE", font));
	go->GetComponent<TextComponent>()->SetColor(m_InActiveColor);

	GetGameObject()->AddChild(go);
	m_pButtons.push_back(go->GetComponent<TextComponent>().get());


	go = std::make_shared<GameObject>();
	go->SetName("Exit");
	go->AddComponent(std::make_shared<TransformComponent>(32.f * 4.5f, 32.f * 7));
	go->AddComponent(std::make_shared<RenderComponent>());
	go->AddComponent(std::make_shared<TextureComponent>());
	go->AddComponent(std::make_shared<TextComponent>("EXIT", font));
	go->GetComponent<TextComponent>()->SetColor(m_InActiveColor);

	GetGameObject()->AddChild(go);
	m_pButtons.push_back(go->GetComponent<TextComponent>().get());
}

void dae::MainMenuComponent::Update(float )
{
	if (m_NeedUpdate)
	{
		for (auto i = 0; i < m_pButtons.size(); i++)
		{
			if (i == m_ActiveButton)
				m_pButtons[i]->SetColor(m_ActiveColor);
			else
				m_pButtons[i]->SetColor(m_InActiveColor);
		}
		m_NeedUpdate = false;
	}
	else 
		ExecuteCommand();
	
}
