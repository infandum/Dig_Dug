#pragma once
#include "Singleton.h"
#include "Renderer.h"

struct SDL_Window;
struct SDL_Renderer;

namespace dae
{
	class Texture2D;

	class RenderComponent : public Singleton<RenderComponent>, public BaseComponent
	{
		SDL_Renderer* mRenderer = nullptr;
	public:
		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) noexcept = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) noexcept = delete;
		RenderComponent() = default;
		virtual ~RenderComponent() = default;

		void Init(SDL_Window* window);
		void Render();
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;

		SDL_Renderer* GetSDLRenderer() const { return mRenderer; }
	private:
		CompType m_Type = CompType::RENDERCOMPONENT;
	};
}
