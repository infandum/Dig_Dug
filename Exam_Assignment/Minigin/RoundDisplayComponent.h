#pragma once
#include "BaseComponent.h"

namespace  dae
{
	class TextComponent;
	class ResourceManager;
	class RoundDisplayComponent : public BaseComponent
	{
	public:

		RoundDisplayComponent(const RoundDisplayComponent& other) = delete;
		RoundDisplayComponent(RoundDisplayComponent&& other) noexcept = delete;
		RoundDisplayComponent& operator=(const RoundDisplayComponent& other) = delete;
		RoundDisplayComponent& operator=(RoundDisplayComponent&& other) noexcept = delete;
		RoundDisplayComponent() = default;
		virtual ~RoundDisplayComponent() = default;


		void onNotify(GameObject& gameObject, NotifyEvent& event) override;
		void AddDisplay();

	protected:
		void Initialize() override;
		void Update(float deltaTime) override;



	private:
		TextComponent* m_pTextComponent;
		int m_Rounds;
		bool m_NeedUpdate = false;

		ResourceManager* m_Resource = nullptr;
	};
}