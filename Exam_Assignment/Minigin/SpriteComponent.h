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
		//TODO: CHECK IF PLAYER OR NPC ASSIGN CORRECT INIT STATE
		SpriteComponent() = default;
		virtual ~SpriteComponent() = default;

		void Swap();

		std::shared_ptr<BaseState> GetCurrentDirectionState() const { return m_State; }

		void SetFlipSprite(const SDL_RendererFlip flip) { m_FlipDirection = flip; }
		SDL_RendererFlip GetFlipSprite() const { return m_FlipDirection; }

		UINT GetActiveAnimationFrame() const { return m_ActiveFrame; }

		void SetCurrentUV(int x, int y, int w = 32, int h = 32) { m_SpriteUV.x = x; m_SpriteUV.y = y; m_SpriteUV.w = w; m_SpriteUV.h = h; }
		SDL_Rect GetCurrentUV() const { return m_SpriteUV; }

		void SetAnimationToState(UINT clipID, std::shared_ptr<BaseState> state);

		void onNotify(NotifyEvent event);
	protected:
		void Initialize() override;
		void Update(float deltaTime) override;
		//void Render() override;

		void SetActiveAnimationFrame(float deltaTime);
		UINT GetAnimationIDForState(std::shared_ptr<BaseState> state);
	private:
		std::shared_ptr<BaseState> m_State = std::make_shared<DirectionState>();
		std::shared_ptr<BaseState> m_NpcState = std::make_shared<IdlePlayerState>();

		NotifyEvent m_Event = NotifyEvent::EVENT_IDLE;
		SDL_RendererFlip m_FlipDirection = SDL_FLIP_NONE;

		double m_FrameTime = 0;
		UINT m_ActiveFrame = 0;
		SDL_Rect m_SpriteUV = { 0 , 0, 32, 32};

		std::map<UINT, std::shared_ptr<BaseState>> m_StateClips;
	};
}
