#pragma once
#include "MiniginPCH.h"

namespace dae
{
	class GameObject;
	class BaseState
	{
	public:
		virtual ~BaseState() = default;
		virtual std::shared_ptr<BaseState> Swap(GameObject& gameObject) = 0;
		virtual void Update(float& deltaTime, GameObject& gameObject) = 0;
		
		virtual void Animated(GameObject& gameObject) = 0;
		virtual void SetStateAnimClip(UINT id) { m_StateAnimClipId = id; }
		virtual UINT GetStateAnimClip() const { return m_StateAnimClipId; }

	protected:
		virtual void SpriteFlip(GameObject& gameObject) const = 0;
		UINT m_StateAnimClipId = 0;
	};

	class DirectionState : public BaseState
	{
	public:
		virtual ~DirectionState() = default;
		std::shared_ptr<BaseState> Swap(GameObject& gameObject) override;
		void Update(float& deltaTime, GameObject& gameObject) override;
		void Animated(GameObject& gameObject) override;
	protected:
		void SpriteFlip(GameObject& gameObject) const override;
	};

	class IdleState : public DirectionState
	{
	public:
		virtual ~IdleState() = default;
		std::shared_ptr<BaseState> Swap(GameObject& gameObject) override;
		//void Update(float& deltaTime, GameObject& gameObject) override;
	};

	class DigState : public DirectionState
	{
	public:
		virtual ~DigState() = default;
		std::shared_ptr<BaseState> Swap(GameObject& gameObject) override;
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
