#include "AIPlayerStateMachine.h"

#include "Maruyama/New/AI/AIPlayer/Component/AIPlayerController.h"

#include "Maruyama/New/AI/AIPlayer/StateNodes/Patrol.h"

using namespace basecross;

namespace AI
{
	namespace AIPlayer
	{

		StateMachine::StateMachine(const std::shared_ptr<basecross::GameObject>& owner) :
			StatorBase(owner)
		{}

		void StateMachine::CreateNode()
		{
			auto controller = GetGameObject()->GetComponent<Controller>(false);

			//Patrol
			m_stateMachine->AddNode<StateNode::Patrol>(eState::Patrol, controller);

			//Battle

		}

		void StateMachine::CreateEdge()
		{

		}

	}
}
