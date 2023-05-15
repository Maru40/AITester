#include "InfluenceManager.h"

#include "Maruyama/StateMachine/NodeBase.h"
#include "Maruyama/StateMachine/EdgeBase.h"
#include "Maruyama/Enemy/Astar/AstarNode.h"
#include "Maruyama/Enemy/Astar/AstarEdge_Ex.h"
#include "Maruyama/Patch/Graphs/SparseGraph_Ex.h"

#include "Maruyama/Thread/ThreadPool.h"
#include "Maruyama/Utility/Utility.h"
#include "Maruyama/Utility/Mathf.h"

#include "Maruyama/New/AI/AIDirector/InfluenceMap/InfluenceUpdater.h"

using namespace basecross;

namespace AI
{
	InfluenceManager::InfluenceManager(AstarGraph* const graph):
		mGraph(graph)
	{
		mThreadPool = new ThreadPool(1);	//�X���b�h�v�[��
	}

	InfluenceManager::~InfluenceManager()
	{
		if (mThreadPool) {
			delete(mThreadPool);
		}
	}

	void InfluenceManager::AddUpdater(InfluenceUpdater* const updater) { mUpdaters.push_back(updater); }

	bool InfluenceManager::HasUpdater() const { return mUpdaters.size() != 0; }

	InfluenceUpdater* InfluenceManager::GetCurrentUpdater() const { return mUpdaters[mCurrentUpdaterIndex]; }

	void InfluenceManager::StartInfluenceCalculate()
	{
		if (!HasUpdater()) {
			return;
		}

		//�X�V�҂�ݒ肷��B
		auto updater = GetCurrentUpdater();

		mThreadPool->Submit(this, &InfluenceManager::CalculateInfluence, this, updater);
	}

	void InfluenceManager::CalculateInfluence(InfluenceUpdater* const updater)
	{
		//�m�[�h���擾
		auto nodeMap = mGraph->GetNodes();
		std::unordered_map<int, std::shared_ptr<AstarNode>> resultMap;

		auto selfNode = updater->GetSelfNode();


		EndInfluenceCalculate(resultMap);	//�v�Z�������ʂ�Ԃ��B
	}

	void InfluenceManager::InfluenceUpdate(const std::unordered_map<int, std::shared_ptr<AstarNode>>& nodeMap)
	{
		//�����Ń~���[�e�b�N�X

		mGraph->SetNodeMap(nodeMap);
	}

	void InfluenceManager::EndInfluenceCalculate(const std::unordered_map<int, std::shared_ptr<AstarNode>>& nodeMap)
	{
		InfluenceUpdate(nodeMap);		//�e���x�̍X�V

		//�X�V�҂�ύX���āA�e���x�̍X�V���n�߂�B
		mCurrentUpdaterIndex++;
		if (mUpdaters.size() <= mCurrentUpdaterIndex) {
			mCurrentUpdaterIndex = 0;
		}
		StartInfluenceCalculate();
	}
}