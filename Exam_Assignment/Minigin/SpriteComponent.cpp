#include "MiniginPCH.h"
#include "Components.h"
#include "GameObject.h"
#include "ServiceLocator.h"

void dae::SpriteComponent::Swap()
{
	const auto state = m_DirState->Swap(*GetGameObject());

	if(GetAnimationForState(m_DirState))
		m_DirState->SetStateAnimClip(GetAnimationForState(m_DirState));
	if (state != nullptr && m_DirState != state)
	{
		m_DirState = state;		
		std::cout << typeid(*m_DirState).name() << '\n';
	}
}

void dae::SpriteComponent::SetAnimationToState(UINT clipID, std::shared_ptr<BaseState> state)
{
	//TODO: Check if ID is valid saved texture ID;
	for (std::pair<UINT, std::shared_ptr<BaseState>> entry : m_StateClips)
	{
		if (entry.first == clipID)
		{
			std::cout << "ResourceManager::LoadTexture() > id %i is already used! " << clipID << '\n';
			return;
		}

		if (entry.second == state)
		{
			std::cout << "ResourceManager::LoadTexture() > Texture is already added to the manager (ID %i)! " << clipID << '\n';
			return;
		}
	}
	m_StateClips[clipID] = state;
}

void dae::SpriteComponent::Update(float& deltaTime)
{
	SetActiveAnimationFrame(deltaTime);
	Swap();
	m_DirState->Update(deltaTime, *GetGameObject());
	m_DirState->Animated(*GetGameObject());
}

void dae::SpriteComponent::SetActiveAnimationFrame(float& deltaTime)
{
	auto anim = ServiceLocator::GetAnimationManager();
	const auto clip = GetAnimationForState(m_DirState);
	if (GetGameObject() && GetGameObject()->GetTransform() && clip != 0)
		if (GetGameObject()->GetTransform()->GetVelocity().y != 0 || GetGameObject()->GetTransform()->GetVelocity().x != 0)
		{
			m_FrameTime += deltaTime;
			if (m_FrameTime >= double(1.0f / anim->GetAnimationSpeed()))
			{
				// the number of frames to increment is the integral result of frameTime / (1 / animationFPS), thus frameTime * animationFPS
				m_ActiveFrame += static_cast<UINT>(m_FrameTime *  anim->GetAnimationSpeed());
				// use modulo computation to make sure to not jump past the last frame
				if (m_ActiveFrame >= 2)
					m_ActiveFrame = m_ActiveFrame % anim->GetAnimationClips(clip).at(static_cast<UINT>(GetGameObject()->GetTransform()->GetCurrentDirection())).size();
			}
			m_FrameTime = std::fmod(m_FrameTime, 1.0f / static_cast<double>(anim->GetAnimationSpeed()));
		}
		else
		{
			m_ActiveFrame = 0;
			m_FrameTime = 0;
		}

	//TODO:: REDO ANIM?
}

UINT dae::SpriteComponent::GetAnimationForState(std::shared_ptr<BaseState> state)
{
	for (const std::pair<UINT, std::shared_ptr<BaseState>> entry : m_StateClips)
	{
		if (typeid(*entry.second) == typeid(*state))
		{
			return entry.first;
		}
	}
	return {};
}
