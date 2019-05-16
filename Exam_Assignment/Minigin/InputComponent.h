#pragma once
#include "BaseComponent.h"
//#include "Commands.h"

namespace dae
{
	class command;
	class InputComponent  : public BaseComponent
	{

	public:
		InputComponent(const InputComponent& other) = delete;
		InputComponent(InputComponent&& other) noexcept = delete;
		InputComponent& operator=(const InputComponent& other) = delete;
		InputComponent& operator=(InputComponent&& other) noexcept = delete;
		InputComponent() = default;
		virtual ~InputComponent() = default;

		void ExecuteCommand();
	protected:
		void Initialize() override;
		void Update(float deltaTime) override;
		//void Render() override;
		//std::vector<std::shared_ptr<Command>> m_pCommands;
	};

}
