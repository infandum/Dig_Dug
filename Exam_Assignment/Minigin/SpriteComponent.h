#pragma once
#include "BaseComponent.h"
#include "States.h"

namespace dae
{
	class SpriteComponent : public BaseComponent
	{
	public:
		SpriteComponent(const SpriteComponent& other) = delete;
		SpriteComponent(SpriteComponent&& other) noexcept = delete;
		SpriteComponent& operator=(const SpriteComponent& other) = delete;
		SpriteComponent& operator=(SpriteComponent&& other) noexcept = delete;

		SpriteComponent() = default;
		virtual ~SpriteComponent() = default;

		void Swap();

		std::shared_ptr<BaseState> GetCurrentDirectionState() const { return m_DirState; }

		void SetFlipSprite(const SDL_RendererFlip flip) { m_FlipDirection = flip; }
		SDL_RendererFlip GetFlipSprite() const { return m_FlipDirection; }

		UINT GetActiveAnimationFrame() const { return m_ActiveFrame; }

		void SetAnimationToState(UINT clipID, std::shared_ptr<BaseState> state);

		void onNotify(NotifyEvent event) { m_Event = event; }
	protected:
		/*void Initialize() override;*/
		void Update(float& deltaTime) override;
		/*void Draw(float& deltaTime) override;*/

		void SetActiveAnimationFrame(float& deltaTime);
		UINT GetAnimationIDForState(std::shared_ptr<BaseState> state);
	private:
		std::shared_ptr<BaseState> m_DirState = std::make_shared<IdleState>();

		NotifyEvent m_Event = NotifyEvent::EVENT_IDLE;
		SDL_RendererFlip m_FlipDirection = SDL_FLIP_NONE;

		double m_FrameTime = 0;
		UINT m_ActiveFrame = 0;

		std::map<UINT, std::shared_ptr<BaseState>> m_StateClips;
	};
}
