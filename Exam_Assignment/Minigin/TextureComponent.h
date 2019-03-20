#pragma once
#include "Components.h"
#include "Texture2D.h"

namespace dae
{
	class TextureComponent :public BaseComponent
	{
	public:
		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) noexcept = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) noexcept = delete;

		explicit TextureComponent() = default;
		explicit TextureComponent(const std::string& filename);
		explicit TextureComponent(std::shared_ptr<Texture2D> texture);
		virtual ~TextureComponent() = default;

		void SetTexture(const std::string& filename);
		void SetTexture(std::shared_ptr<Texture2D> texture);
		std::shared_ptr<Texture2D>& GetTexture() { return m_spTexture; }

	private:
		CompType m_Type = CompType::TEXTURECOMPONENT;
		std::shared_ptr<Texture2D> m_spTexture{};
	};
}