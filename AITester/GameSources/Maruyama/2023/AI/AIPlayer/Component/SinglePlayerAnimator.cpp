#include "SinglePlayerAnimator.h"

using namespace basecross;

SinglePlayerAnimator::SinglePlayerAnimator(const std::shared_ptr<basecross::GameObject>& owner):
	Animator(owner)
{}

void
SinglePlayerAnimator::OnCreate()
{
	auto data = LoadAnimationData(L"PlayerAnimation");
	for (auto d : data) {
		RegisterAnimationClip(d);
	}
}

void SinglePlayerAnimator::OnUpdate()
{
	
}

AnimationClip 
SinglePlayerAnimator::GetAnimationClip(const AnimationState& state) const
{
	return Animator::GetAnimationClip(PlayerAnimationState::PlayerAnimationState2wstring(state));
}