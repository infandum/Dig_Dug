#pragma once
#include "BaseComponent.h"

namespace dae
{
	class TextComponent;
	class ResourceManager;
	class PointDisplayComponent final : public BaseComponent
	{
	public:

		PointDisplayComponent(const PointDisplayComponent& other) = delete;
		PointDisplayComponent(PointDisplayComponent&& other) noexcept = delete;
		PointDisplayComponent& operator=(const PointDisplayComponent& other) = delete;
		PointDisplayComponent& operator=(PointDisplayComponent&& other) noexcept = delete;
		PointDisplayComponent() = default;
		virtual ~PointDisplayComponent() = default;


		void onNotify(GameObject& gameObject, NotifyEvent& event) override;
		void AddDisplay();

	protected:
		void Initialize() override;
		void Update(float deltaTime) override;



	private:
		TextComponent* m_pTextComponent;
		int m_Points;
		bool m_NeedUpdate = false;

		ResourceManager* m_Resource = nullptr;
	};
}