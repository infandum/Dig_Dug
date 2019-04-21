#pragma once
#include "Service.h"

namespace dae
{ 
	class AnimationManager : public Service
	{
	public:
		AnimationManager() = default;

		AnimationClip BuildAnimationStateClip(UINT textureIdStart, UINT frames = 1, bool hasUpDown = false, bool isLooping = true);
		void LoadAnimationClips(AnimationClip animClip, UINT id);
		AnimationClip GetAnimationClips(UINT id);

		void SetAnimationSpeed(float speed) { m_AnimSpeed = speed; }
		float GetAnimationSpeed() const { return m_AnimSpeed; }
	private:
		std::map<UINT, AnimationClip> m_pLoadedAnimations;
		float m_AnimSpeed = 16.f;
	};
}