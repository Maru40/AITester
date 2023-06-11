#include "UtilityGraph.h"

#include "Maruyama/Enemy/Component/EyeSearchRange.h"

//ここ改良したい

UtilityGraph::NodeVector UtilityGraph::SearchEyeInNode(const AstarGraph* graph, AstarNode* const selfNode, Eye* const eye)
{
	//データ化する必要がないかも
	std::list<OpenData> openDatas;
	std::list<OpenData> closeDatas;
	openDatas.push_back(OpenData(nullptr, selfNode));

	while (!openDatas.empty())
	{
		OpenData parentData = openDatas.front();
		openDatas.pop_front();
		closeDatas.push_back(parentData);

		AddOpenData(openDatas, closeDatas, parentData, graph, eye);
	}

	return NodeVector();
}

void 
UtilityGraph::AddOpenData(std::list<OpenData>& openDatas, std::list<OpenData>& closeDatas, const OpenData& parentData, const AstarGraph* graph, Eye* const eye)
{
	auto parentNode = parentData.selfNode;
	auto edges = graph->GetEdges(parentNode->GetIndex());

	for (auto& edge : edges) {
		auto toNode = std::dynamic_pointer_cast<AstarNode>(edge->GetToNode());

		if (IsAddOpenData(openDatas, closeDatas, parentData)) {
			//std::unordered_map<int, std::shared_ptr<AstarNode>> copyNodes;
			//auto nodes = graph->GetNodes();
			//std::memcpy((*copyNodes.begin()), *nodes.begin(), nodes.size());
		}
	}
}

bool 
UtilityGraph::IsAddOpenData(const std::list<OpenData>& openDatas, const std::list<OpenData>& closeDatas, const OpenData& parentData)
{
	if (IsMathData(openDatas, closeDatas, parentData)) {
		return false;
	}

	//視界内にいるかどうか
	

}

bool 
UtilityGraph::IsMathData(const std::list<OpenData>& openDatas, const std::list<OpenData>& closeDatas, const OpenData& parentData)
{
	auto compare = [&](const OpenData& data) { return data.selfNode == parentData.selfNode; };

	auto findOpenData = std::find_if(openDatas.begin(), openDatas.end(), compare);
	
	//endでないなら見つかった
	if (findOpenData != openDatas.end()) {
		
	}

	//オープンデータに登録されているなら
	if (std::find(openDatas.begin(), openDatas.end(), parentData) != openDatas.end()) {
		return true;
	}

	//クローズデータに登録されているなら
	if (std::find(closeDatas.begin(), closeDatas.end(), parentData) != closeDatas.end()) {
		return true;
	}

	return false;
}