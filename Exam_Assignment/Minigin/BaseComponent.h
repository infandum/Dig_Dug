#pragma once
#include "GameObject.h"

class BaseComponent
{
public:
	BaseComponent(const BaseComponent& other) = delete;
	BaseComponent(BaseComponent&& other) noexcept = delete;
	BaseComponent& operator=(const BaseComponent& other) = delete;
	BaseComponent& operator=(BaseComponent&& other) noexcept = delete;
	BaseComponent();
	virtual ~BaseComponent() = default;

	dae::GameObject* GetGameObject() const { return m_pGameObject; }

	dae::GameObject* m_pGameObject;
protected:
	void Initialize();
	void Update();
	void Draw();

private:
	
};

