#pragma once

#include "../Base/AIControllerBase.h"

namespace AI
{
	namespace AIPlayer
	{
		class Controller : public AIControllerBase
		{
		public:
			Controller(const std::shared_ptr<basecross::GameObject>& owner);

			virtual ~Controller();
		};
	}
}