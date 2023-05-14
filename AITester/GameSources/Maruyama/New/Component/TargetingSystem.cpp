#include "TargetingSystem.h"

#include "Targeted_Ex.h"

using namespace basecross;

TargetingSystem::TargetingSystem(const std::shared_ptr<GameObject>& owner):
	Component(owner)
{

}

void TargetingSystem::OnUpdate()
{
	//�^�[�Q�b�g�̍X�V
}

Targeted* TargetingSystem::CalculateCurrentTarget()
{
	//�{���͌��݂Ƀ^�[�Q�b�g�w�肵����������v�Z���āACurrentTarget�Ɏw�肷��B
	return GetCurrentTarget();
}

void TargetingSystem::AddTarget(const std::shared_ptr<Targeted>& target)
{
	mTargets.insert(target.get());
}

void TargetingSystem::RemoveTarget(const std::shared_ptr<Targeted>& target)
{
	mTargets.erase(target.get());
}

void TargetingSystem::SetCurrentTarget(Targeted* const target) { mCurrentTarget = target; }

Targeted* TargetingSystem::GetCurrentTarget() const { return mCurrentTarget; }

std::set<Targeted*> TargetingSystem::GetTargets() const { return mTargets; }