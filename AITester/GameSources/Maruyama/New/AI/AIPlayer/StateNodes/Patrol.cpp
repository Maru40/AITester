#include "Patrol.h"

namespace AI
{
	namespace AIPlayer
	{
		namespace StateNode
		{

			Patrol::Patrol(const std::shared_ptr<Controller>& owner):
				StateNodeBase(owner)
			{}

			void Patrol::OnAwake()
			{

			}

			void Patrol::OnStart()
			{

			}

			bool Patrol::OnUpdate()
			{
				return true;
			}

			void Patrol::OnExit()
			{

			}

		}
	}
}