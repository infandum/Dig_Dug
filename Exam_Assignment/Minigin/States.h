#pragma once
#include "MiniginPCH.h"
#include "Observer.h"
#include "ServiceLocator.h"

namespace dae
{
	class GameObject;
	class BaseState
	{
	public:
		virtual ~BaseState() = default;
		virtual std::shared_ptr<BaseState> Swap(NotifyEvent event, GameObject& gameObject) = 0;
		virtual void Update(float& deltaTime, GameObject& gameObject) = 0;

		
		virtual void Animated(GameObject& gameObject) = 0;
		virtual void SetStateAnimClip(SpriteClip clip) { m_Clip = clip; }

	protected:
		virtual void SpriteFlip(GameObject& gameObject) const = 0;
		SpriteClip m_Clip;
		Direction m_LastHorDir = Direction::RIGHT;
	};

	class DirectionState : public BaseState
	{
	public:
		virtual ~DirectionState() = default;
		std::shared_ptr<BaseState> Swap(NotifyEvent event, GameObject& gameObject) override;
		void Update(float& deltaTime, GameObject& gameObject) override;
		void Animated(GameObject& gameObject) override;

	protected:
		void SpriteFlip(GameObject& gameObject) const override;
		LevelManager* m_pLevelManager = ServiceLocator::GetLevelManager();
	};

	
}
