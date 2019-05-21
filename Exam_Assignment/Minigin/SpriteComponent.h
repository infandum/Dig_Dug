#pragma once
#include "BaseComponent.h"
#include "States.h"
#include <SDL.h>
#include "AnimationManager.h"

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

		template <class T>
		explicit SpriteComponent(T state)
		{
			m_State = std::make_shared<T>(state);
		}

		//SpriteComponent(const BaseState & state);
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
		NotifyEvent GetCurrentEvent() const { return m_Event; }

		void ResetCurrentAnimation();
		void Pause(const bool& pause = true) { m_IsPaused = pause; }
		bool IsPaused() const { return m_IsPaused;}

		bool IsAnimationEnded() const { return m_IsAnimationEnd; }

		BaseState* GetCurrentState() const { return m_State.get(); }

		template <class T>
		std::shared_ptr<T> GetState()
		{
			for (auto& state : m_StateClips)
				if(state.second && typeid(*state.second.get()) == typeid(T))
				{
					return std::static_pointer_cast<T>(state.second);
				}
			return nullptr;
		}

		void Reset();

		void onNotify(GameObject& gameObject, NotifyEvent& event) override;

	protected:
		void Initialize() override;
		void Update(float deltaTime) override;
		//void Render() override;

		void AnimationTime(float deltaTime, const SpriteClip& clip);
		void SetActiveAnimationFrame(float deltaTime);
		UINT GetAnimationIDForState(std::shared_ptr<BaseState> state);
	private:
		std::shared_ptr<BaseState> m_State = nullptr;

		NotifyEvent m_Event = NotifyEvent::EVENT_IDLE;

		SDL_RendererFlip m_FlipDirection = SDL_FLIP_NONE;

		bool m_IsAnimationEnd = false;
		bool m_IsPaused = false;
		double m_FrameTime = 0;
		UINT m_ActiveFrame = 0;
		SDL_Rect m_SpriteUV = { 0 , 0, 32, 32};

		AnimationManager* m_AnimManager;
		std::map<UINT, std::shared_ptr<BaseState>> m_StateClips;
	};
}
