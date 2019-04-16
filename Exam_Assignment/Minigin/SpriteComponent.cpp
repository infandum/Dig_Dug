#include "MiniginPCH.h"
#include "Components.h"
#include "GameObject.h"
#include "ServiceLocator.h"

void dae::SpriteComponent::Swap()
{
	const auto state = m_DirState->Swap(*GetGameObject());
	if (state != nullptr && m_DirState != state)
	{
		m_DirState = state;
		std::cout << typeid(*m_DirState).name() << '\n';
	}
}

void dae::SpriteComponent::Update(float& deltaTime)
{
	Swap();
	m_DirState->Update(deltaTime, *GetGameObject());
	
	UNREFERENCED_PARAMETER(deltaTime);
	/*auto resource = ServiceLocator::GetResourceManager();
	if(GetGameObject()->GetTexture())
	{
		if(typeid(*m_DirState) == typeid(UpState))
		GetGameObject()->GetTexture()->SetTexture(resource->GetTexture(1101));
		if (typeid(*m_DirState) == typeid(DownState))
			GetGameObject()->GetTexture()->SetTexture(resource->GetTexture(1111));
		if (typeid(*m_DirState) == typeid(LeftState))
			GetGameObject()->GetTexture()->SetTexture(resource->GetTexture(1121));
		if (typeid(*m_DirState) == typeid(RightState))
			GetGameObject()->GetTexture()->SetTexture(resource->GetTexture(1131));
	}*/
}
