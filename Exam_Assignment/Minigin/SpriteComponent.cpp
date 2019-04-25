#include "MiniginPCH.h"
#include "Components.h"
#include "GameObject.h"
#include "ServiceLocator.h"

void dae::SpriteComponent::Swap()
{
	const auto state = m_DirState->Swap(m_Event, *GetGameObject());
	auto anim = ServiceLocator::GetAnimationManager();

	if(GetAnimationIDForState(m_DirState))
		m_DirState->SetStateAnimClip(anim->GetSpriteClip(GetAnimationIDForState(m_DirState)));
	if (state != nullptr && typeid(*m_DirState) != typeid(*state))
	{
		m_ActiveFrame = anim->GetSpriteClip(GetAnimationIDForState(state)).StartFrame;
		m_DirState = state;		
		//std::cout << typeid(*m_DirState).name() << '\n';
	}
}

void dae::SpriteComponent::SetAnimationToState(UINT clipID, std::shared_ptr<BaseState> state)
{
	//TODO: Check if ID is valid saved texture ID;
	if(/*ServiceLocator::GetAnimationManager()->GetAnimationClips(clipID).TextureList.size() == 0 && */ServiceLocator::GetAnimationManager()->GetSpriteClip(clipID).id == 0)
	{
		std::cout << "SpriteComponent::SetAnimationToState() > id Not found in loaded textures! " << clipID << '\n';
		return;
	}
	for (std::pair<UINT, std::shared_ptr<BaseState>> entry : m_StateClips)
	{
		if (entry.first == clipID)
		{
			std::cout << "SpriteComponent::SetAnimationToState() > id is already used! " << clipID << '\n';
			return;
		}

		if (entry.second == state)
		{
			std::cout << "SpriteComponent::SetAnimationToState() > State is already added to the manager (ID %i)! " << clipID << '\n';
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
	//const auto clip = anim->GetAnimationClips(GetAnimationIDForState(m_DirState));
	const auto clip = anim->GetSpriteClip(GetAnimationIDForState(m_DirState));
	if (GetGameObject() && GetGameObject()->GetTransform() && clip.id != 0)
	{
		
		if (m_Event != NotifyEvent::EVENT_IDLE)
		{
			if(!clip.isLooping && m_ActiveFrame == clip.frames - 1)
				return;

			m_FrameTime += deltaTime;
			if (m_FrameTime >= double(1.0f / anim->GetAnimationSpeed()))
			{
				// the number of frames to increment is the integral result of frameTime / (1 / animationFPS), thus frameTime * animationFPS
				m_ActiveFrame += static_cast<UINT>(m_FrameTime *  anim->GetAnimationSpeed());
				// use modulo computation to make sure to not jump past the last frame
				if (m_ActiveFrame >= 2)
					m_ActiveFrame = m_ActiveFrame % clip.frames;
			}
			m_FrameTime = std::fmod(m_FrameTime, 1.0f / static_cast<double>(anim->GetAnimationSpeed()));
		}
		else
		{
			m_ActiveFrame = clip.StartFrame;
			m_FrameTime = 0;
		}
	}
}

UINT dae::SpriteComponent::GetAnimationIDForState(std::shared_ptr<BaseState> state)
{
	for (const std::pair<UINT, std::shared_ptr<BaseState>> entry : m_StateClips)
	{
		if (typeid(*entry.second) == typeid(*state))
		{
			return entry.first;
		}
	}
	std::cout << "SpriteComponent::GetAnimationIDForState() > State is not found in manager! " << typeid(state).name() << '\n';
	return 0;
}