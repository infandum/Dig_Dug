#pragma once
#include "Command.h"
namespace dae
{
	class AttackCommand : public Command
	{
	public:
		void Execute(GameObject& gameObject) override;
	};
}