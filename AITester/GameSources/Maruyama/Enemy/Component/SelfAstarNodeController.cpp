
/*!
@file ImpactMap.cpp
@brief ImpactMapのクラス実体
担当：丸山裕喜
*/

#include "stdafx.h"
#include "Project.h"

#include "SelfAstarNodeController.h"

#include "Maruyama/Utility/SingletonComponent/SingletonComponent.h"
#include "Maruyama/Enemy/ImpactMap/FieldImpactMap.h"

#include "Maruyama/Enemy/ImpactMap/ImpactMap.h"
#include "Maruyama/Enemy/Astar/NavGraphNode.h"
#include "Maruyama/Enemy/Astar/GraphAstar.h"
#include "Maruyama/Enemy/Astar/AstarGraph.h"
#include "Maruyama/Enemy/Astar/AstarEdge.h"
#include "Maruyama/Enemy/Astar/UtilityAstar.h"

#include "Watanabe/DebugClass/Debug.h"

namespace basecross {

	SelfAstarNodeController::SelfAstarNodeController(const std::shared_ptr<GameObject>& objPtr) :
		Component(objPtr),
		m_isNodeInitialize(false),
		m_isMover(true)
	{}

	void SelfAstarNodeController::OnCreate() {

	}

	void SelfAstarNodeController::OnLateStart() {
		InitializeNode();
	}

	void SelfAstarNodeController::OnUpdate() {
		//動く者なら、ノードの更新を監視する。
		if (IsMover()) {
			UpdateProccess();
		}
	}

	void SelfAstarNodeController::UpdateProccess() {
		if (IsInitializeNode()) {
			return;
		}

		if (!HasNode() || IsFarNode()) {
			m_isNodeInitialize = true;
			std::thread initializeNode(&SelfAstarNodeController::InitializeNode, this);
			initializeNode.detach();
			return;
		}

		if (IsUpdateNode()) {
			UpdateNode();
		}
	}

	void SelfAstarNodeController::UpdateNode() {
		//ノードを持ってて、動かないなら、
		if (HasNode() && !IsMover()) {
			return;
		}

		if (!HasNode()) {
			InitializeNode();
			return;
		}

		auto impactMap = maru::FieldImpactMap::GetInstance()->GetImpactMap();
		auto astar = impactMap->GetGraphAstar();
		auto graph = astar->GetGraph();

		//ソート用のデータ構造体
		struct Data {
			std::weak_ptr<NavGraphNode> node;
			float range;

			Data(const std::shared_ptr<NavGraphNode>& node, const float range):
				node(node), range(range)
			{}
		};

		auto edges = graph->GetEdges(m_node.lock()->GetIndex());

		std::vector<Data> datas;	//ソート用の配列
		datas.reserve(edges.size());

		//現在のノードを入れる。
		float range = (GetNode()->GetPosition() - transform->GetPosition()).length();
		datas.push_back(Data(GetNode(), range));

		//距離を計ってソート用の配列に代入する。
		for (auto& edge : edges) {
			auto node = graph->GetNode(edge->GetTo());
			if (!node) {
				auto strIndex = std::to_wstring(edge->GetTo());
				Debug::GetInstance()->Log(L"OpenDataHandler::CreateOpenData(): ノードがnullです。: " + strIndex);
				continue;
			}
			float toNodeRange = (node->GetPosition() - transform->GetPosition()).length();

			datas.push_back(Data(node, toNodeRange));
		}

		//ソート条件
		auto sortFunction = [&](const Data& left, const Data& right) {
			return left.range < right.range;
		};
		std::sort(datas.begin(), datas.end(), sortFunction);		//ソート

		m_node = !datas.empty() ? datas[0].node.lock() : m_node;	//配列が存在するなら新規ノードに変更
	}

	bool SelfAstarNodeController::IsUpdateNode() {
		if (m_node.expired()) {	//ノードが存在しないならアップデートが必要
			return true;
		}

		auto fieldImpactMap = maru::FieldImpactMap::GetInstance();
		float intervalRnage = fieldImpactMap->GetIntervalRange();

		auto toNodeRange = (m_node.lock()->GetPosition() - transform->GetPosition()).length();

		return intervalRnage < toNodeRange;	//距離が遠くなったら更新が必要。
	}

	void SelfAstarNodeController::InitializeNode() {
		std::lock_guard<mutex> lock(m_mtx);	//ミューテックスロック

		auto impactMap = maru::FieldImpactMap::GetInstance()->GetImpactMap();
		auto astar = impactMap->GetGraphAstar();
		auto graph = astar->GetGraph();

		auto areaIndex = astar->SearchNearAreaIndex(transform->GetPosition());
		if (areaIndex < 0) {
			m_isNodeInitialize = false;
			return;
		}

		auto objects = GetStage()->GetGameObjectVec();
		auto node = UtilityAstar::SearchNearNode(astar->GetGraph(areaIndex), transform->GetPosition(), objects, { GetGameObject() });
		if (!node) {
			//再起して、絶対見つける。
			node = SearchNode(areaIndex, areaIndex);
			Debug::GetInstance()->Log(L"全ノードサーチをしました。重い！！");
			if (!node) {
				Debug::GetInstance()->Log(L"全サーチしたのにnullptr");
			}
		}

		SetNode(node);

		m_isNodeInitialize = false;
	}

	std::shared_ptr<NavGraphNode> SelfAstarNodeController::SearchNode(const int firstAreaIndex, const int currentAreaIndex, const int direction) {
		auto index = currentAreaIndex + direction;
		if (index < 0) {	//0より小さくなったら、大きくする過程で探す。
			return SearchNode(firstAreaIndex, firstAreaIndex, +1);
		}

		auto areaGraph = maru::FieldImpactMap::GetInstance()->GetImpactMap()->GetGraphAstar()->GetGraph(index);
		if (direction > 0 && !areaGraph) {
			return nullptr;
		}

		auto node = UtilityAstar::SearchNearNode(
			areaGraph, transform->GetPosition()
		);

		return node ? node : SearchNode(firstAreaIndex, index, direction);
	}

	bool SelfAstarNodeController::IsFarNode() {
		if (!HasNode()) {
			return false;
		}

		auto toNode = GetNode()->GetPosition() - transform->GetPosition();
		float range = toNode.length();
		float intervalRange = maru::FieldImpactMap::GetInstance()->GetIntervalRange();
		constexpr float FarCost = 1.0f;
		float farRange = intervalRange + FarCost;

		return farRange < range;
	}

	std::shared_ptr<NavGraphNode> SelfAstarNodeController::CalculateNode() {
		UpdateNode();
		return GetNode();
	}

	void SelfAstarNodeController::SetNode(const std::shared_ptr<NavGraphNode>& node) noexcept {
		m_node = node;
	}

	std::shared_ptr<NavGraphNode> SelfAstarNodeController::GetNode() const noexcept {
		return m_node.lock();
	}

	bool SelfAstarNodeController::HasNode() const noexcept {
		return !m_node.expired();
	}




	//if (HasNode()) {
	//	wstring str = L"";
	//	str += L"NodeIndex: ";
	//	str += std::to_wstring(GetNode()->GetIndex());
	//	Debug::GetInstance()->Log(str);
	//}
	//else {
	//	Debug::GetInstance()->Log(L"ノードがありません。");
	//}

}