#pragma once
#include "MiniginPCH.h"
#include "Observer.h"

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
	};

	class IdleState : public DirectionState
	{
	public:
		virtual ~IdleState() = default;
		std::shared_ptr<BaseState> Swap(NotifyEvent event, GameObject& gameObject) override;
		//void Update(float& deltaTime, GameObject& gameObject) override;
	};

	class MoveState : public DirectionState
	{
	public:
		virtual ~MoveState() = default;
		std::shared_ptr<BaseState> Swap(NotifyEvent event, GameObject& gameObject) override;
		//void Update(float& deltaTime, GameObject& gameObject) override;
	};

	class DigState : public DirectionState
	{
	public:
		virtual ~DigState() = default;
		std::shared_ptr<BaseState> Swap(NotifyEvent event, GameObject& gameObject) override;
		//void Update(float& deltaTime, GameObject& gameObject) override;
	};

	class AttackState : public DirectionState
	{
	public:
		virtual ~AttackState() = default;
		std::shared_ptr<BaseState> Swap(NotifyEvent event, GameObject& gameObject) override;
		//void Update(float& deltaTime, GameObject& gameObject) override;
	};


	/*

	class DugState : public BaseState
	{
	public:
		std::shared_ptr<BaseState> Swap(GameObject& gameObject) override;
		void Update(float& deltaTime, GameObject& gameObject) override;
	};

	class BlockedState : public BaseState
	{
	public:
		std::shared_ptr<BaseState> Swap(GameObject& gameObject) override;
		void Update(float& deltaTime, GameObject& gameObject) override;
	};

	class OccupiedState : public BaseState
	{
	public:
		std::shared_ptr<BaseState> Swap(GameObject& gameObject) override;
		void Update(float& deltaTime, GameObject& gameObject) override;
	};

	class EmpityState : public BaseState
	{
	public:
		std::shared_ptr<BaseState> Swap(GameObject& gameObject) override;
		void Update(float& deltaTime, GameObject& gameObject) override;
	};*/
}
