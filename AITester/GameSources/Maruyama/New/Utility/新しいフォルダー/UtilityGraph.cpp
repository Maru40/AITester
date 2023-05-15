#include "UtilityGraph.h"

#include "Maruyama/Enemy/Component/EyeSearchRange.h"

UtilityGraph::NodeVector UtilityGraph::SearchEyeInNode(const AstarGraph* graph, AstarNode* const selfNode, Eye* const eye)
{
	std::queue<OpenData> openDatas;
	std::queue<OpenData> closeDatas;
	openDatas.push(OpenData(nullptr, selfNode));

	while (!openDatas.empty())
	{
		auto parentData = openDatas.front();
		openDatas.pop();
		closeDatas.push(parentData);

		AddOpenData(openDatas, closeDatas,parentData, graph, eye);
	}
	
}

void 
UtilityGraph::AddOpenData(std::queue<OpenData>& openDatas, std::queue<OpenData>& closeDatas, const OpenData& parentData, const AstarGraph* graph, Eye* const eye)
{
	auto parentNode = parentData.selfNode;
	auto edges = graph->GetEdges(parentNode->GetIndex());

	for (auto& edge : edges) {
		auto toNode = std::dynamic_pointer_cast<AstarNode>(edge->GetToNode());

		if (IsAddOpenData(openDatas, closeDatas, toNode.get())) {

		}
	}
}

bool 
UtilityGraph::IsAddOpenData(const std::queue<OpenData>& openDatas, const std::queue<OpenData>& closeDatas, AstarNode* const node)
{
	return true;
}