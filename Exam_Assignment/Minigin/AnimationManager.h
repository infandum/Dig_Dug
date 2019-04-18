#pragma once
#include "Service.h"

namespace dae
{ 
	class AnimationManager : public Service
	{
	public:
		AnimationManager() = default;

		std::vector<std::vector<UINT>> BuildAnimationStateClip(UINT textureIdStart, UINT frames = 1, bool hasUpDown = false);
		void LoadAnimationClips(std::vector<std::vector<UINT>> TextureList, UINT id);
		std::vector<std::vector<UINT>> GetAnimationClips(UINT id);

		void SetAnimationSpeed(float speed) { m_AnimSpeed = speed; }
		float GetAnimationSpeed() const { return m_AnimSpeed; }
	private:
		std::map<UINT, std::vector<std::vector<UINT>>> m_pLoadedAnimations;
		float m_AnimSpeed = 16.f;
	};
}