#include "MiniginPCH.h"
#include "AnimationManager.h"

std::vector<std::vector<UINT>> dae::AnimationManager::BuildAnimationStateClip(UINT textureIdStart, UINT frames,	bool hasUpDown)
{
	auto TextureId = textureIdStart;
	std::vector<std::vector<UINT>> Stateclip;
	for(UINT dir = 0; dir < static_cast<UINT>(Direction::NONE); dir++)
	{
		std::vector<UINT> animationClip;
		if (dir < 2 && hasUpDown == false)
			break;
		for (UINT frame = 1; frame <= frames; frame++)
		{
			TextureId = textureIdStart + (dir * 10) + frame;
			animationClip.push_back(TextureId);
		}
		Stateclip.push_back(animationClip);
	}
	return Stateclip;
}

void dae::AnimationManager::LoadAnimationClips(std::vector<std::vector<UINT>> TextureList, UINT id)
{
	for (std::pair<UINT, std::vector<std::vector<UINT>>> Entry : m_pLoadedAnimations)
	{
		if (Entry.first == id)
		{
			std::cout << "ResourceManager::LoadTexture() > id %i is already used! " << id << '\n';
			return;
		}

		if (Entry.second == TextureList)
		{
			std::cout << "ResourceManager::LoadTexture() > Texture is already added to the manager (ID %i)! " << id << '\n';
			return;
		}
	}
	m_pLoadedAnimations[id] = TextureList;
}

std::vector<std::vector<UINT>> dae::AnimationManager::GetAnimationClips(UINT id)
{
	const auto it = m_pLoadedAnimations.find(id);
	if (it == m_pLoadedAnimations.end())
	{
		std::cout << "ResourceManager::LoadTexture() > Material with ID %i not found! " << id << '\n';
		return {};
	}
	return it->second;
}
