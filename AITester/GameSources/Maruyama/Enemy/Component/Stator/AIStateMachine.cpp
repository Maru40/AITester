#include "stdafx.h"
#include "Project.h"
#include "Maruyama/StateMachine/StateMachine.h"

#include "AIStateMachine.h"

#include "Maruyama/Enemy/EnemyBase.h"

AIStateMachine::AIStateMachine(const std::shared_ptr<basecross::GameObject>& owner):
	mTransitionMember(TransitionMember()),
	StatorBase(owner, mTransitionMember)
{}