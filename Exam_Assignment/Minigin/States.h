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
		Direction m_LastHorDir = Direction::NONE;
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

	class IdlePlayerState : public DirectionState
	{
	public:
		virtual ~IdlePlayerState() = default;
		std::shared_ptr<BaseState> Swap(NotifyEvent event, GameObject& gameObject) override;
		//void Update(float& deltaTime, GameObject& gameObject) override;
	};

	class MovePlayerState : public DirectionState
	{
	public:
		virtual ~MovePlayerState() = default;
		std::shared_ptr<BaseState> Swap(NotifyEvent event, GameObject& gameObject) override;
		//void Update(float& deltaTime, GameObject& gameObject) override;
	};

	class DigPlayerState : public DirectionState
	{
	public:
		virtual ~DigPlayerState() = default;
		std::shared_ptr<BaseState> Swap(NotifyEvent event, GameObject& gameObject) override;
		//void Update(float& deltaTime, GameObject& gameObject) override;
	};

	class AttackPlayerState : public DirectionState
	{
	public:
		virtual ~AttackPlayerState() = default;
		std::shared_ptr<BaseState> Swap(NotifyEvent event, GameObject& gameObject) override;
		//void Update(float& deltaTime, GameObject& gameObject) override;
	};

	class ActionPlayerState : public DirectionState
	{
	public:
		virtual ~ActionPlayerState() = default;
		std::shared_ptr<BaseState> Swap(NotifyEvent event, GameObject& gameObject) override;
		//void Update(float& deltaTime, GameObject& gameObject) override;
	};

	class DeadPlayerState : public DirectionState
	{
	public:
		virtual ~DeadPlayerState() = default;
		std::shared_ptr<BaseState> Swap(NotifyEvent event, GameObject& gameObject) override;
		//void Update(float& deltaTime, GameObject& gameObject) override;
	};

	class CrushedPlayerState : public DirectionState
	{
	public:
		virtual ~CrushedPlayerState() = default;
		std::shared_ptr<BaseState> Swap(NotifyEvent event, GameObject& gameObject) override;
		//void Update(float& deltaTime, GameObject& gameObject) override;
	};

	class WeaponState : public DirectionState
	{
	public:
		virtual ~WeaponState() = default;
		std::shared_ptr<BaseState> Swap(NotifyEvent event, GameObject& gameObject) override;
		//void Update(float& deltaTime, GameObject& gameObject) override;
	};

	class IdleEnemyState : public DirectionState
	{
	public:
		virtual ~IdleEnemyState() = default;
		std::shared_ptr<BaseState> Swap(NotifyEvent event, GameObject& gameObject) override;
		//void Update(float& deltaTime, GameObject& gameObject) override;
	};

	class MoveEnemyState : public DirectionState
	{
	public:
		virtual ~MoveEnemyState() = default;
		std::shared_ptr<BaseState> Swap(NotifyEvent event, GameObject& gameObject) override;
		//void Update(float& deltaTime, GameObject& gameObject) override;
	};

	class AttackEnemyState : public DirectionState
	{
	public:
		virtual ~AttackEnemyState() = default;
		std::shared_ptr<BaseState> Swap(NotifyEvent event, GameObject& gameObject) override;
		//void Update(float& deltaTime, GameObject& gameObject) override;
	};

	class ActionEnemyState : public DirectionState
	{
	public:
		virtual ~ActionEnemyState() = default;
		std::shared_ptr<BaseState> Swap(NotifyEvent event, GameObject& gameObject) override;
		//void Update(float& deltaTime, GameObject& gameObject) override;
	};

	class HitEnemyState : public DirectionState
	{
	public:
		virtual ~HitEnemyState() = default;
		std::shared_ptr<BaseState> Swap(NotifyEvent event, GameObject& gameObject) override;
		//void Update(float& deltaTime, GameObject& gameObject) override;
	};

	class GhostEnemyState : public DirectionState
	{
	public:
		virtual ~GhostEnemyState() = default;
		std::shared_ptr<BaseState> Swap(NotifyEvent event, GameObject& gameObject) override;
		//void Update(float& deltaTime, GameObject& gameObject) override;
	};

	class DeadEnemyState : public DirectionState
	{
	public:
		virtual ~DeadEnemyState() = default;
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
