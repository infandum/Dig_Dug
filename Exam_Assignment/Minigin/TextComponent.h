#pragma once
#include "Components.h"
#include "Transform.h"
#include <SDL.h>

namespace dae{
	class Font;
	class Texture2D;

	class TextComponent : public BaseComponent
	{
		friend class GameObject;
	public:
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) noexcept = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) noexcept = delete;

		explicit TextComponent(const std::string& text, std::shared_ptr<Font> font);
		virtual ~TextComponent() = default;

		void Initialize() override;
		void Update(float& deltaTime) override;
		void Draw(float& deltaTime) override;

		void SetText(const std::string& text);
		void SetColor(const SDL_Color& color);

	private:
		CompType m_Type = CompType::TEXTCOMPONENT;
		SDL_Color m_Color = { 255,255,255 };
		bool m_NeedsUpdate;
		std::string m_Text;
		Transform mTransform;
		std::shared_ptr<Font> mFont;
		//std::shared_ptr<Texture2D> mTexture;
};
}
