#include "stdafx.h"

#include "AIPlayerObject_Ex.h"

#include "Component/AIPlayerController.h"

#include "../../Component/InputMover.h"
#include "../../Component/InputerComponent.h"

#include "Maruyama/Utility/Component/CollisionAction.h"
#include "Maruyama/Utility/Component/RotationController.h"
#include "Maruyama/2023/AI/AIPlayer/Component/SinglePlayerAnimator.h"

using namespace basecross;
using namespace basecross::bsm;

namespace AI
{
	namespace AIPlayer
	{
		Object::Object(const std::shared_ptr<basecross::Stage>& stage):
			PlayerObjectBase(stage)
		{}

		void Object::OnCreate()
		{
			PlayerObjectBase::OnCreate();

			AddComponent<Controller>();
		}

		void Object::OnUpdate()
		{
			
		}
	}
}