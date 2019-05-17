#include "MiniginPCH.h"
#include "Components.h"
#include "GameObject.h"
#include "ServiceLocator.h"

void dae::SpriteComponent::Initialize()
{
	if(!m_State)
	{
		if (GetGameObject()->GetInput() || GetGameObject()->GetComponent<PlayerComponent>())
			m_State = std::make_shared<IdlePlayerState>();
		if (GetGameObject()->GetNPC())
			m_State = std::make_shared<IdleEnemyState>();

	}
		
	m_Event = NotifyEvent::EVENT_IDLE;
}

void dae::SpriteComponent::Update(float deltaTime)
{
	Swap();
	if (typeid(*m_State) != typeid(DirectionState))
	{
		SetActiveAnimationFrame(deltaTime);
		m_State->Update(deltaTime, *GetGameObject());
		m_State->Animated(*GetGameObject());
	}
}


void dae::SpriteComponent::Swap()
{
	//TODO:: INIT FUNCTION
	std::shared_ptr<BaseState> pBase2 = m_State;

	const auto state = m_State->Swap(m_Event, *GetGameObject());
	auto anim = ServiceLocator::GetAnimationManager();

	if (GetAnimationIDForState(m_State))
		m_State->SetStateAnimClip(anim->GetSpriteClip(GetAnimationIDForState(m_State)));

	if (state != nullptr && typeid(*m_State) != typeid(*state))
	{
		if (anim->GetSpriteClip(GetAnimationIDForState(state)).id == 0)
			return;
		m_ActiveFrame = anim->GetSpriteClip(GetAnimationIDForState(state)).StartFrame;
		m_State = state;
	}
	
	
}

void dae::SpriteComponent::SetAnimationToState(UINT clipID, std::shared_ptr<BaseState> state)
{
	//TODO: Check if ID is valid saved texture ID;
	if(ServiceLocator::GetAnimationManager()->GetSpriteClip(clipID).id == 0)
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

void dae::SpriteComponent::onNotify(NotifyEvent event)
{
		m_Event = event;
}

void dae::SpriteComponent::Reset()
{
	Initialize();
}


void dae::SpriteComponent::SetActiveAnimationFrame(float deltaTime)
{

	auto anim = ServiceLocator::GetAnimationManager();
	//const auto clip = anim->GetAnimationClips(GetAnimationIDForState(m_State));
	const auto clip = anim->GetSpriteClip(GetAnimationIDForState(m_State));
	if (clip.id != 0)
	{
		m_IsAnimationEnd = false;
		if (/*m_Event != NotifyEvent::EVENT_IDLE*/typeid(*m_State) != typeid(IdlePlayerState) && typeid(*m_State) != typeid(IdleEnemyState) && typeid(*m_State) != typeid(WeaponState))
		{
			if(!clip.isLooping && m_ActiveFrame == clip.frames - 1)
			{
				m_IsAnimationEnd = true;
				return;
			}

			auto speed = anim->GetAnimationSpeed()*clip.Speed;
			m_FrameTime += deltaTime;
			if (m_FrameTime >= double(1.0f / speed))
			{
				// the number of frames to increment is the integral result of frameTime / (1 / animationFPS), thus frameTime * animationFPS
				m_ActiveFrame += static_cast<UINT>(m_FrameTime *  speed);
				// use modulo computation to make sure to not jump past the last frame
				if (m_ActiveFrame >= 2)
					m_ActiveFrame = m_ActiveFrame % clip.frames;
			}
			m_FrameTime = std::fmod(m_FrameTime, 1.0f / static_cast<double>(speed));
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
	std::cout << "SpriteComponent::GetAnimationIDForState() > State is not found in manager! " << typeid(state).name() << "Owner: " << GetGameObject()->GetName() << '\n';
	return 0;
}