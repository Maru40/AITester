#pragma once

#include "Maruyama/StateMachine/Node_StateMachine.h"


namespace Enemy
{
	class EnemyBase;

	namespace StateNode
	{
		class Normal : public basecross::maru::NodeBase_StateMachine_Ex<EnemyBase>
		{
		public:

		public:
			Normal(const std::shared_ptr<Enemy::EnemyBase>& owner);

			void OnAwake() override;
			void OnStart() override;
			bool OnUpdate() override;
			void OnExit() override;
		};

	}
}