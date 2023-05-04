#include "StateNode_Attack.h"

namespace Enemy
{
	namespace StateNode
	{
		Attack::Attack(const std::shared_ptr<EnemyBase>& owner):
			NodeBase_StateMachine(owner)
		{}

		void Attack::OnStart()
		{

		}

		bool Attack::OnUpdate()
		{
			return true;
		}

		void Attack::OnExit()
		{

		}
	}
}