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
				std::is_base_of_v<NodeBase, NodeType>&&		//NodeType��NodeBase���p�����Ă��邱�Ƃ�ۏ؂���
				std::is_base_of_v<EdgeBase, EdgeType>,		//EdgeType��EdgeBase���p�����Ă��邱�Ƃ�ۏ؂���
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
	/// �e���x�Ǘ���
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
		/// �e���x�v�Z�J�n
		/// </summary>
		void StartInfluenceCalculate();

	private:
		/// <summary>
		/// �e���x�̌v�Z
		/// </summary>
		void CalculateInfluence(InfluenceUpdater* const updater);

		/// <summary>
		/// �e���x�X�V
		/// </summary>
		void InfluenceUpdate(const std::unordered_map<int, std::shared_ptr<AstarNode>>& nodeMap);

		/// <summary>
		/// �e���x�v�Z�I��
		/// </summary>
		void EndInfluenceCalculate(const std::unordered_map<int, std::shared_ptr<AstarNode>>& nodeMap);

	private:
		AstarGraph* mGraph = nullptr;				//�O���t

		ThreadPool* mThreadPool = nullptr;			//�X���b�h�v�[��

		std::vector<InfluenceUpdater*> mUpdaters;	//�e���x�X�V�҈ꗗ

		u32 mCurrentUpdaterIndex = 0;				//���݂̍X�V��
	};

}