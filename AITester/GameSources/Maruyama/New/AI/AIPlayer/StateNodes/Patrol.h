#pragma once
#include "stdafx.h"

#include "Maruyama/StateMachine/Node_StateMachine.h"


namespace AI
{
	namespace AIPlayer
	{
		class Controller;
		namespace StateNode
		{
			
			using StateNodeBase = basecross::maru::NodeBase_StateMachine_Ex<Controller>;

			class Patrol : public StateNodeBase
			{
			public:
				Patrol(const std::shared_ptr<Controller>& owner);

				~Patrol() = default;

				void OnAwake() override;

				void OnStart() override;
				
				bool OnUpdate() override;

				void OnExit() override;

			};
		}
	}
}

