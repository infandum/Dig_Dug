#pragma once
#include "MiniginPCH.h"
#include "GameObject.h"

namespace dae
{
	class BaseState
	{
	public:
		virtual ~BaseState() = default;
		virtual std::shared_ptr<BaseState> Swap(GameObject& gameObject) = 0;
		virtual void Update(float& deltaTime) = 0;
	};

	class DirtState : public BaseState
	{
	public:
		std::shared_ptr<BaseState> Swap(GameObject& gameObject) override;
		void Update(float& deltaTime) override;
	};

	inline std::shared_ptr<BaseState> DirtState::Swap(GameObject& gameObject)
	{
		UNREFERENCED_PARAMETER(gameObject);
		return std::shared_ptr<DirtState>();
	}

	inline void DirtState::Update(float& deltaTime)
	{
		UNREFERENCED_PARAMETER(deltaTime);
	}

	//class DugState : public BaseState
	//{
	//public:
	//	std::shared_ptr<BaseState> Swap(GameObject& gameObject) override;
	//	void Update(float& deltaTime) override;
	//};

	//class BlockedState : public BaseState
	//{
	//public:
	//	std::shared_ptr<BaseState> Swap(GameObject& gameObject) override;
	//	void Update(float& deltaTime) override;
	//};

	//class OccupiedState : public BaseState
	//{
	//public:
	//	std::shared_ptr<BaseState> Swap(GameObject& gameObject) override;
	//	void Update(float& deltaTime) override;
	//};

	//class EmpityState : public BaseState
	//{
	//public:
	//	std::shared_ptr<BaseState> Swap(GameObject& gameObject) override;
	//	void Update(float& deltaTime) override;
	//};
}
