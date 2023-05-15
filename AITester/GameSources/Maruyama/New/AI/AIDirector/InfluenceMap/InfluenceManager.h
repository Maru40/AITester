#pragma once

#include "InfluenceData.h"

#include "Maruyama/New/Interface/I_ThreadRequester.h"

#include "Maruyama/Enemy/Astar/AstarNode.h"
#include "Maruyama/Enemy/Astar/AstarEdge_Ex.h"
#include "Maruyama/Patch/Graphs/SparseGraph_Ex.h"

namespace basecross
{
	class ThreadPool;

	namespace maru
	{
		class NodeBase;
		class EdgeBase;
		template<class NodeType, class EdgeType,
			std::enable_if_t<
				std::is_base_of_v<NodeBase, NodeType>&&		//NodeTypeがNodeBaseを継承していることを保証する
				std::is_base_of_v<EdgeBase, EdgeType>,		//EdgeTypeがEdgeBaseを継承していることを保証する
			std::nullptr_t
		>>
		class SparceGraph;

		class AstarNode;
		class AstarEdge;
	}
}

namespace AI
{
	class InfluenceUpdater;
	
	/// <summary>
	/// 影響度管理社
	/// </summary>
	class InfluenceManager : public I_ThreadRequester
	{
	public:
		using AstarNode = basecross::maru::AstarNode;
		using AstarEdge = basecross::maru::AstarEdge;
		using AstarGraph = basecross::maru::SparseGraph<AstarNode, AstarEdge, nullptr>;
		using ThreadPool = basecross::ThreadPool;

	public:
		InfluenceManager(AstarGraph* const graph);

		~InfluenceManager();

	public:
		void AddUpdater(InfluenceUpdater* const updater);

		bool HasUpdater() const;

		InfluenceUpdater* GetCurrentUpdater() const;

		/// <summary>
		/// 影響度計算開始
		/// </summary>
		void StartInfluenceCalculate();

	private:
		/// <summary>
		/// 影響度の計算
		/// </summary>
		void CalculateInfluence(InfluenceUpdater* const updater);

		/// <summary>
		/// 影響度更新
		/// </summary>
		void InfluenceUpdate(const std::unordered_map<int, std::shared_ptr<AstarNode>>& nodeMap);

		/// <summary>
		/// 影響度計算終了
		/// </summary>
		void EndInfluenceCalculate(const std::unordered_map<int, std::shared_ptr<AstarNode>>& nodeMap);

	private:
		AstarGraph* mGraph = nullptr;				//グラフ

		ThreadPool* mThreadPool = nullptr;			//スレッドプール

		std::vector<InfluenceUpdater*> mUpdaters;	//影響度更新者一覧

		u32 mCurrentUpdaterIndex = 0;				//現在の更新者
	};

}