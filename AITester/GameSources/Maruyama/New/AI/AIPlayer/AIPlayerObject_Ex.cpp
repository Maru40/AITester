#include "stdafx.h"

#include "AIPlayerObject_Ex.h"

#include "Component/AIPlayerController.h"

#include "../../Component/InputMover.h"
#include "../../Component/InputerComponent.h"

#include "Maruyama/Utility/Component/CollisionAction.h"
#include "Maruyama/Utility/Component/RotationController.h"
#include "Maruyama/New/AI/AIPlayer/Component/SinglePlayerAnimator.h"

#include "Maruyama/New/Component/Targeted_Ex.h"
#include "Maruyama/New/Component/TargetingSystem.h"
#include "Maruyama/New/AI/AIDirector/Strategy/StrategyMember.h"

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
			AddComponent<SinglePlayerAnimator>();
			AddComponent<Targeted>();
			AddComponent<TargetingSystem>();
			AddComponent<StrategyMember>();
		}

		void Object::OnUpdate()
		{
			
		}

	}
}