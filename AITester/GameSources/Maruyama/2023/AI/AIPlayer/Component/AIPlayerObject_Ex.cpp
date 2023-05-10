#include "stdafx.h"

#include "AIPlayerObject_Ex.h"

#include "../AIPlayerController.h"

using namespace basecross;
using namespace basecross::bsm;

namespace AI
{
	namespace AIPlayer
	{
		Object::Object(const std::shared_ptr<basecross::Stage>& stage):
			GameObject(stage)
		{}

		void Object::OnCreate()
		{
			AddComponent<Controller>();
		}
	}
}