#pragma once

#include "Maruyama/StateMachine/StatorBase.h"

namespace Enemy
{
	class EnemyBase;
}

enum class eAIState
{
	Normal,
	Attack,
	Down,
	Dead,
};

struct AIStateMachine_TransitionMemmber
{

};

class AIStateMachine : public basecross::Enemy::StatorBase<Enemy::EnemyBase, eAIState, AIStateMachine_TransitionMemmber>
{
public:
	using State = eAIState;
	using TransitionMember = AIStateMachine_TransitionMemmber;

public:
	AIStateMachine(const std::shared_ptr<basecross::GameObject>& owner);

	virtual ~AIStateMachine() = default;

private:
	void CreateNode() override;
	void CreateEdge() override;

private:
	TransitionMember mTransitionMember;
};