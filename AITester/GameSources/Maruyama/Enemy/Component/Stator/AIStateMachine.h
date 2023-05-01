#pragma once

#include "Maruyama/StateMachine/StatorBase.h"

class EnemyBase;

enum class AIState
{

};

struct AIStateMachine_TransitionMemmber
{

};

class AIStateMachine : public basecross::Enemy::StatorBase<EnemyBase, AIState, AIStateMachine_TransitionMemmber>
{
public:
	using State = AIState;
	using TransitionMember = AIStateMachine_TransitionMemmber;

public:
	AIStateMachine(const std::shared_ptr<basecross::GameObject>& owner);

	virtual ~AIStateMachine() = default;

private:
	TransitionMember mTransitionMember;
};