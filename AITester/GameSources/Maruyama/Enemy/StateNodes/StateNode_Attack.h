#pragma once

#include "Maruyama/StateMachine/Node_StateMachine.h"

namespace Enemy
{
	class EnemyBase;

	namespace StateNode
	{
		struct Attack_Parametor
		{

		};

		class Attack : public basecross::maru::NodeBase_StateMachine<EnemyBase>
		{
		public:
			using Parametor = Attack_Parametor;

		public:
			Attack(const std::shared_ptr<EnemyBase>& owner);


		};

	}
}