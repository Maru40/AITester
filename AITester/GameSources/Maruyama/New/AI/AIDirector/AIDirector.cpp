#include "AIDirector.h"

#include "Maruyama/Enemy/Astar/AstarNode.h"
#include "Maruyama/Enemy/Astar/AstarEdge_Ex.h"

namespace basecross
{
	namespace maru
	{
		std::weak_ptr<AI::AIDirector> basecross::maru::SingletonComponent<AI::AIDirector>::sm_instance;
	}
}

namespace AI
{
	AIDirector::AIDirector(const std::shared_ptr<basecross::GameObject>& owner):
		SingletonComponent(owner)
	{}

	void AIDirector::OnCreate()
	{

	}

	//í—ª‚ğ¶¬‚·‚éB
	void AIDirector::CreateStrategy()
	{
		
	}

	void AIDirector::SearchRoute(const Vector selfPosition, const Vector targetPosition)
	{

	}

	void AIDirector::SearchRoute(const std::shared_ptr<AstarNode>& startNode, const std::shared_ptr<AstarNode>& targetNode)
	{

	}
}