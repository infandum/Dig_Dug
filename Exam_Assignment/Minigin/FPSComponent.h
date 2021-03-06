#pragma once

namespace dae
{
	static unsigned int m_Frames;

	class FPSComponent : public BaseComponent
	{
		
	public:
		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) noexcept = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) noexcept = delete;
		FPSComponent() = default;
		virtual ~FPSComponent() = default;

		float GetFramesPerSecond() const { return m_Fps; }

		static unsigned int GetTotalFrames() { return m_Frames; }

		void onNotify(GameObject& gameObject, NotifyEvent& event) override;

	protected:
		void Initialize() override;
		void Update(float deltaTime) override;
		////void Render() override;

	private:
		float m_Fps = 0;
		float m_AccuTime{};
	};
}