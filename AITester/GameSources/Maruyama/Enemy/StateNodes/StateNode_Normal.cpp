#include "StateNode_Normal.h"

#include "Maruyama/Enemy/EnemyBase.h"

namespace Enemy
{
	namespace StateNode
	{
		Normal::Normal(const std::shared_ptr<Enemy::EnemyBase>& owner) :
			NodeBase_StateMachine_Ex(owner)
		{}

		void Normal::OnAwake()
		{
			
		}

		void Normal::OnStart()
		{

		}

		bool Normal::OnUpdate()
		{
			return true;
		}

		void Normal::OnExit()
		{

		}

	}
}