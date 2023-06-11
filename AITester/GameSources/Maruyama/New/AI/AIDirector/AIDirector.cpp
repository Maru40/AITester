#include "AIDirector.h"

#include "Maruyama/Enemy/Astar/AstarNode.h"
#include "Maruyama/Enemy/Astar/AstarEdge_Ex.h"

#include "Maruyama/Utility/Utility.h"

#include "Maruyama/New/AI/AIDirector/DetachmentSystem.h"

//#include "Maruyama/New/AI/AIDirector/Tactic/TacticBase.h"
//#include "Maruyama/New/AI/AIDirector/Tactic/TacticMember.h"

namespace basecross
{
	namespace maru
	{
		std::weak_ptr<AI::AIDirector> basecross::maru::SingletonComponent<AI::AIDirector>::sm_instance;
	}
}

using namespace basecross;

namespace AI
{
	AIDirector::AIDirector(const std::shared_ptr<basecross::GameObject>& owner):
		SingletonComponent(owner)
	{}

	AIDirector::~AIDirector()
	{

	}

	void AIDirector::OnCreate()
	{

	}

	void AIDirector::OnLateStart()
	{

	}

	void AIDirector::OnUpdate()
	{
		//�e���}�b�v�A�b�v�f�[�g

	}

	void AIDirector::SearchRoute(const Vector selfPosition, const Vector targetPosition)
	{

	}

	void AIDirector::SearchRoute(const std::shared_ptr<AstarNode>& startNode, const std::shared_ptr<AstarNode>& targetNode)
	{

	}
}