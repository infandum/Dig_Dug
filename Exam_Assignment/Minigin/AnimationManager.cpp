#include "MiniginPCH.h"
#include "AnimationManager.h"

dae::AnimationClip dae::AnimationManager::BuildAnimationStateClip(UINT textureIdStart, UINT frames,	bool hasUpDown , bool isLooping)
{
	auto TextureId = textureIdStart;
	std::vector<std::vector<UINT>> Stateclip;
	AnimationClip clip;
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
	clip.TextureList = Stateclip;
	clip.frames = frames;
	clip.hasUpDown = hasUpDown;
	clip.isLooping = isLooping;
	return clip;
}

void dae::AnimationManager::LoadAnimationClips(AnimationClip animClip, UINT id)
{
	for (const std::pair<UINT, AnimationClip> Entry : m_pLoadedAnimations)
	{
		if (Entry.first == id)
		{
			std::cout << "AnimationManager::LoadAnimationClips() > id %i is already used! " << id << '\n';
			return;
		}
	}
	animClip.id = id;
	m_pLoadedAnimations[id] = animClip;
}

dae::AnimationClip dae::AnimationManager::GetAnimationClips(UINT id)
{
	const auto it = m_pLoadedAnimations.find(id);
	if (it == m_pLoadedAnimations.end())
	{
		std::cout << "AnimationManager::GetAnimationClips() > Animation clip with ID %i not found! " << id << '\n';
		return {};
	}
	return it->second;
}
