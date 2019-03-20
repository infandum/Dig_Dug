#pragma once
#include "SceneObject.h"
#include "Transform.h"

namespace dae
{
	class Font;
	class Texture2D;
	class BaseComponent;

	class TextObject final : public SceneObject
	{
	public:
		void Update(float deltaTime) override;
		void Render() const override;

		void SetText(const std::string& text);
		void SetPosition(float x, float y);

		/*void AddComponent(BaseComponent* pComp);
		void RemoveComponent(BaseComponent* pComp);
*/
		template <class T>
		T* GetComponent()
		{
			const auto& ti = typeid(T);
			for (auto* component : m_pComponents)
			{
				if (component && typeid(*component) == ti)
					return static_cast<T*>(component);
			}
			return nullptr;
		}

		explicit TextObject(const std::string& text, std::shared_ptr<Font> font);
		virtual ~TextObject() = default;
		TextObject(const TextObject& other) = delete;
		TextObject(TextObject&& other) = delete;
		TextObject& operator=(const TextObject& other) = delete;
		TextObject& operator=(TextObject&& other) = delete;
	private:


		bool mNeedsUpdate;
		std::string mText;
		Transform mTransform;
		std::shared_ptr<Font> mFont;
		std::shared_ptr<Texture2D> mTexture;

		std::string mName = "GameObject";
		std::vector<BaseComponent*> m_pComponents;
	};

}
