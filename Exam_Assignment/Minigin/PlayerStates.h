#pragma once
#include "States.h"

namespace dae
{
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
}