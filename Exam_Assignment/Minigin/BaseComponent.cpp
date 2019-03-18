//#pragma once
#include "MiniginPCH.h"
#include "BaseComponent.h"

dae::BaseComponent::BaseComponent()
	: m_pGameObject(nullptr)
	, m_pTextObject(nullptr)
{
}

void dae::BaseComponent::Initialize()
{
}

void dae::BaseComponent::Update(float& deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

void dae::BaseComponent::Draw(float& deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}
