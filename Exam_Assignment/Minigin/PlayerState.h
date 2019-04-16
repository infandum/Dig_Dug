#pragma once
#include "State.h"

namespace dae
{
	class PlayerState : public BaseState
	{
		std::shared_ptr<BaseState> Swap(GameObject& gameObject) override;
		void Update(float& deltaTime) override;
	};

	inline std::shared_ptr<BaseState> PlayerState::Swap(GameObject& gameObject)
	{
		return {};
	}

	inline void PlayerState::Update(float& deltaTime)
	{
	}
}
