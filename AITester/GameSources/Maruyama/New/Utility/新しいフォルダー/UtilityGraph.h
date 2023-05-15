#pragma once

#include "Maruyama/Patch/Graphs/SparseGraph_Ex.h"

#include "Maruyama/Enemy/Astar/AstarNode.h"
#include "Maruyama/Enemy/Astar/AstarEdge_Ex.h"

namespace basecross
{
	class EyeSearchRange;

	namespace maru
	{
		class AstarNode;
		class AstarEdge;
	}
}


class UtilityGraph
{
public:
	using AstarNode = basecross::maru::AstarNode;
	using AstarEdge = basecross::maru::AstarEdge;
	using AstarGraph = basecross::maru::SparseGraph<AstarNode, AstarEdge, nullptr>;

	using NodeVector = std::vector<std::shared_ptr<AstarNode>>;

	using Eye = basecross::EyeSearchRange;

public:
	struct OpenData
	{
		AstarNode* parent;
		AstarNode* selfNode;

		OpenData(AstarNode* const parent, AstarNode* const selfNode) :
			parent(parent),
			selfNode(selfNode)
		{}
	};


public:
	//‹ŠE”ÍˆÍ‚Ìƒm[ƒh‚ğæ“¾‚·‚éB
	NodeVector SearchEyeInNode(const AstarGraph* graph, AstarNode* const selfNode, Eye* const eye);

private:
	//ü‚è‚Ìƒm[ƒh‚ğ“ü‚ê‚é
	void AddOpenData(std::queue<OpenData>& openDatas, std::queue<OpenData>& closeDatas, const OpenData& parentData, const AstarGraph* graph, Eye* const eye);

	bool IsAddOpenData(const std::queue<OpenData>& openDatas, const std::queue<OpenData>& closeDatas, AstarNode* const node);
};