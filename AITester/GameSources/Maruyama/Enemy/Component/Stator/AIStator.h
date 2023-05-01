#pragma once

#include "Maruyama/StateMachine/StatorBase.h"

class EnemyBase;

enum class AIState
{

};

struct AIStator_TransitionMemmber
{

};

class AIStator : public basecross::Enemy::StatorBase<EnemyBase, AIState, AIStator_TransitionMemmber>
{
public:
	using State = AIState;
	using TransitionMember = AIStator_TransitionMemmber;

public:
	AIStator(const std::shared_ptr<basecross::GameObject>& owner);

	virtual ~AIStator() = default;

private:
	TransitionMember mTransitionMember;
};