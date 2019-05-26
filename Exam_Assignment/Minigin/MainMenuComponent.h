#pragma once
#include "InputComponent.h"
#include <SDL.h>

namespace dae
{
	class TextComponent;
	class MainMenuComponent  final : public InputComponent
	{
	public:
		MainMenuComponent(const MainMenuComponent& other) = delete;
		MainMenuComponent(MainMenuComponent&& other) noexcept = delete;
		MainMenuComponent& operator=(const MainMenuComponent& other) = delete;
		MainMenuComponent& operator=(MainMenuComponent&& other) noexcept = delete;
		MainMenuComponent() = default;
		virtual ~MainMenuComponent() = default;

		int ActiveButton() const { return m_ActiveButton; }

		void NextButton();
		void PreviousButton();
		void SelectButton();

		void onNotify(GameObject& gameObject, NotifyEvent& event) override;

	protected:
		void Initialize() override;
		void Update(float deltaTime) override;

		void SetActiveButton(int index);

	private:
		int m_ActiveButton = 0;
		std::vector<TextComponent*> m_pButtons {};
		SDL_Color m_ActiveColor = { 255,255,255 };
		SDL_Color m_InActiveColor = { 0, 0, 0 };
		bool m_NeedUpdate = false;
	};

}
