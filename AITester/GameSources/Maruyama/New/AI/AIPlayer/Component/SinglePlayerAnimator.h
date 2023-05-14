#pragma once

#include "Watanabe/Component/Animator.h"

#include "Watanabe/Component/PlayerAnimationState.h"

class SinglePlayerAnimator : public basecross::Animator
{
public:
	using AnimationState = basecross::PlayerAnimationState::State;
	
public:
	SinglePlayerAnimator(const std::shared_ptr<basecross::GameObject>& owner);

	~SinglePlayerAnimator() = default;
	
	void OnCreate() override;

	void OnUpdate() override;

	basecross::AnimationClip GetAnimationClip(const AnimationState& state) const;
};