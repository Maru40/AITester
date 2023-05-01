#include "stdafx.h"
#include "Project.h"
#include "Maruyama/StateMachine/StateMachine.h"

#include "AIStator.h"

#include "Maruyama/Enemy/EnemyBase.h"

AIStator::AIStator(const std::shared_ptr<basecross::GameObject>& owner):
	mTransitionMember(TransitionMember()),
	StatorBase(owner, mTransitionMember)
{}