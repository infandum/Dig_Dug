#include "MiniginPCH.h"
#include "Components.h"
#include "GameObject.h"
#include "ServiceLocator.h"

void dae::SpriteComponent::Initialize()
{
	m_AnimManager = ServiceLocator::GetAnimationManager();
	if(!m_State)
	{
		if (GetGameObject()->GetInput() || GetGameObject()->GetComponent<PlayerComponent>())
			m_State = GetState<IdlePlayerState>();
		if (GetGameObject()->GetComponent<NpcComponent>())
			m_State = GetState<IdleEnemyState>();
	}
	else
	{
		if (GetGameObject()->GetInput() || GetGameObject()->GetComponent<PlayerComponent>())
			m_State = GetState<IdlePlayerState>();
		if (GetGameObject()->GetComponent<NpcComponent>())
			m_State = GetState<IdleEnemyState>();
		if(typeid(*m_State.get()) == typeid(WeaponState))
			m_State = GetState<WeaponState>();
	}
		
	m_Event = NotifyEvent::EVENT_IDLE;
}

void dae::SpriteComponent::Update(float deltaTime)
{
	Swap();
	SetActiveAnimationFrame(deltaTime);
	m_State->Update(deltaTime, *GetGameObject());
	m_State->Animated(*GetGameObject());
}


void dae::SpriteComponent::Swap()
{
	const auto state = m_State->Swap(m_Event, *GetGameObject());
	
	if (state != nullptr)
	{
		m_ActiveFrame = m_AnimManager->GetSpriteClip(GetAnimationIDForState(state)).StartFrame;
		m_IsAnimationEnd = false;
		m_FrameTime = 0;
		m_State = state;
	}
	
	
}

void dae::SpriteComponent::SetAnimationToState(UINT clipID, std::shared_ptr<BaseState> state)
{
	auto anim = ServiceLocator::GetAnimationManager();
	if(anim->GetSpriteClip(clipID).id == 0)
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
	state->SetStateAnimClip(anim->GetSpriteClip(clipID));
	m_StateClips[clipID] = state;
}

void dae::SpriteComponent::onNotify(NotifyEvent event)
{
		m_Event = event;
}

void dae::SpriteComponent::ResetCurrentAnimation()
{
	m_ActiveFrame = m_AnimManager->GetSpriteClip(GetAnimationIDForState(m_State)).StartFrame;
	m_IsAnimationEnd = false;
	m_FrameTime = 0;
}

void dae::SpriteComponent::Reset()
{
	Initialize();
}


void dae::SpriteComponent::AnimationTime(float deltaTime, const SpriteClip& clip)
{
	if(m_IsPaused)
		return;

	const auto speed = m_AnimManager->GetAnimationSpeed()*clip.Speed;
	m_FrameTime += deltaTime;
	if (m_FrameTime >= double(1.0f / speed))
	{
		// the number of Frames to increment is the integral result of frameTime / (1 / animationFPS), thus frameTime * animationFPS
		m_ActiveFrame += static_cast<UINT>(m_FrameTime *  speed);
		// use modulo computation to make sure to not jump past the last frame
		if (m_ActiveFrame >= 2)
			m_ActiveFrame = m_ActiveFrame % clip.Frames;
	}
	m_FrameTime = std::fmod(m_FrameTime, 1.0f / static_cast<double>(speed));
}

void dae::SpriteComponent::SetActiveAnimationFrame(float deltaTime)
{

	const auto clip = m_AnimManager->GetSpriteClip(GetAnimationIDForState(m_State));

	if (clip.id != 0 || !m_IsAnimationEnd)
	{
		
			if(!clip.IsLooping)
			{
				if (m_ActiveFrame == clip.Frames - 1)
					m_IsAnimationEnd = true;

				if(m_IsAnimationEnd)
				{
					m_FrameTime = 0;
				}
				else
				{
					AnimationTime(deltaTime, clip);
				}
			}
			else
			{
				AnimationTime(deltaTime, clip);
			}

			
		
	}
}

void dae::SpriteComponent::onNotify(GameObject& , NotifyEvent& )
{
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
	std::cout << "SpriteComponent::GetAnimationIDForState() > State is not found in manager! " << typeid(state).name() << "Owner: " << GetGameObject()->GetName() << '\n';
	return 0;
}
