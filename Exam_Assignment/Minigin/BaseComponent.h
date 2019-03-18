#pragma once
namespace dae
{
	class GameObject;
	class TextObject;

	class BaseComponent
	{
		friend class GameObject;
		friend class TextObject;
	public:
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) noexcept = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) noexcept = delete;
		BaseComponent();
		virtual ~BaseComponent() = default;

		GameObject* GetGameObject() const { return m_pGameObject; }
		TextObject* GetTextObject() const { return m_pTextObject; }

	protected:
		virtual void Initialize();
		virtual void Update(float& deltaTime);
		virtual void Draw(float& deltaTime);

		GameObject* m_pGameObject;
		TextObject* m_pTextObject;
	private:
	
	};
}