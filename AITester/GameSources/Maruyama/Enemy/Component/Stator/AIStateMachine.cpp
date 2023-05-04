#include "stdafx.h"
#include "Project.h"
#include "Maruyama/StateMachine/StateMachine.h"

#include "AIStateMachine.h"

#include "Maruyama/Enemy/EnemyBase.h"

#include "Maruyama/Enemy/StateNodes/StateNode_Normal.h"

AIStateMachine::AIStateMachine(const std::shared_ptr<basecross::GameObject>& owner):
	mTransitionMember(TransitionMember()),
	StatorBase(owner, mTransitionMember)
{}

void
AIStateMachine::CreateNode()
{
	auto enemy = GetGameObject()->GetComponent<Enemy::EnemyBase>();
	auto& stateMachine = m_stateMachine;

	//通常状態
	stateMachine->AddNode<Enemy::StateNode::Normal>(State::Normal, enemy);

	//攻撃状態
	//stateMachine->AddNode();
}

void 
AIStateMachine::CreateEdge()
{

}