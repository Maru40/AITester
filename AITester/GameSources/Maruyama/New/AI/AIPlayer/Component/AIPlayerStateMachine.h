#pragma once

#include "Maruyama/Stator/StatorBase.h"

namespace AI
{

	namespace AIPlayer
	{
		class Controller;

		enum class eState
		{
			Empty,
			Patrol,
			
		};

		struct TransitionMember
		{

		};


		class StateMachine : public basecross::Enemy::StatorBase<Controller, eState, TransitionMember>
		{
		public:
			StateMachine(const std::shared_ptr<basecross::GameObject>& owner);

			~StateMachine() = default;

		private:
			void CreateNode() override;
			void CreateEdge() override;

		};
	}
}