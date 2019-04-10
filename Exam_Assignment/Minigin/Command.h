#pragma once
namespace dae
{
	enum class ControllerButton
	{
		ButtonA = 0x1000,
		ButtonB = 0x2000,
		ButtonX = 0x4000,
		ButtonY = 0x8000
	};

	class Command
	{
	public:
		virtual void Execute() = 0;
		virtual ~Command() = default;

		virtual void SetButton(ControllerButton button) = 0;
		virtual ControllerButton GetButton() = 0;
	};
};