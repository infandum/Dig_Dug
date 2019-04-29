#pragma once
#include "Texture2D.h"
#include "DataStructs.h"

namespace dae
{
	class TextureComponent : public BaseComponent
	{
	public:
		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) noexcept = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) noexcept = delete;

		explicit TextureComponent() = default;
		explicit TextureComponent(std::shared_ptr<Texture2D> texture);
		virtual ~TextureComponent() = default;

		void SetTexture(std::shared_ptr<Texture2D> texture);
		std::shared_ptr<Texture2D>& GetTexture() { return m_spTexture; }
		iVector2 GetSize() const { return m_Size; }

	protected:
		/*void Initialize() override;*/
		void Update(float& deltaTime) override;
		/*void Draw(float& deltaTime) override;*/

	private:
		std::shared_ptr<Texture2D> m_spTexture{};

		iVector2 m_Size {};
	};
}