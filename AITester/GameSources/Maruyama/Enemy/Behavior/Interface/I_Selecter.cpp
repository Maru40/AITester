/*!
@file I_Selecter.cpp
@brief I_Selecterなど実体
*/

#include "stdafx.h"
#include "Project.h"

#include "I_Selecter.h"

#include "I_Edge.h"
#include "I_PriorityController.h"

#include "Maruyama/TaskList/TaskList.h"

#include "Maruyama/Utility/Random.h"
#include "Maruyama/Utility/Utility.h"

namespace basecross {
	namespace maru {

		namespace Behavior {

			//--------------------------------------------------------------------------------------
			/// ソート用の完全隠蔽関数
			//--------------------------------------------------------------------------------------

			/// <summary>
			/// 遷移先を優先順位順にソートする条件
			/// </summary>
			/// <param name="right">比較対象のデータ</param>
			/// <param name="left">比較対象のデータ</param>
			/// <returns>leftが小さいならtrue</returns>
			bool SortEdges(
				const std::weak_ptr<I_Edge>& left,
				const std::weak_ptr<I_Edge>& right
			) {
				return left.lock()->GetPriority() < right.lock()->GetPriority();	//優先順位が低い順にソート
			}

			//--------------------------------------------------------------------------------------
			/// ビヘイビアセレクター本体
			//--------------------------------------------------------------------------------------

			Selecter::Selecter():
				Selecter(SelectType::Priority)
			{}

			Selecter::Selecter(const SelectType selectType) :
				m_selectType(selectType)
			{}

			void Selecter::OnStart() {

			}

			bool Selecter::OnUpdate() {
				return false;
			}

			void Selecter::OnExit() {
				//遷移先のエッジを元の状態に戻す。
				for (auto& edge : m_transitionEdges) {
					edge.lock()->GetToNode()->SetState(BehaviorState::Inactive);
				}

				SetCurrentNode(nullptr);	//ノードをnullptrに変更
			}

			std::shared_ptr<I_Node> Selecter::SearchCurrentNode() const {
				switch (m_selectType)
				{
				case maru::Behavior::SelectType::Priority:
					return SearchFirstPriorityNode();
				case maru::Behavior::SelectType::Random:
					return SearchRandomNode();
				case maru::Behavior::SelectType::Sequence:
					return SearchSequenceNode();
				}

				return nullptr;
			}

			std::shared_ptr<I_Node> Selecter::SearchFirstPriorityNode() const {
				//現在のステートがRunningなら、一度検索をしているため、終了。
				if (IsState(BehaviorState::Running)) {
					return nullptr;
				}

				//遷移先ノードが空ならnullptr
				if (IsEmptyTransitionNodes()) {
					return nullptr;
				}

				auto transitionEdges = m_transitionEdges;		//メンバをソートするとconstにできないため、一時変数化

				//エッジの優先度計算を先にする。
				for (auto& weakEdge : transitionEdges) {
					if (weakEdge.expired()) {	//存在しないなら
						continue;
					}

					weakEdge.lock()->CalculatePriority();
				}

				//昇順ソート
				std::sort(transitionEdges.begin(), transitionEdges.end(), &SortEdges);	

				//並べ替えたノードが遷移できるかどうかを判断する。
				for (const auto& edge : transitionEdges) {
					if (edge.lock()->GetToNode()->CanTransition()) {	//遷移できるなら、そのノードを返す。
						return edge.lock()->GetToNode();
					}
				}

				return nullptr;
			}

			std::shared_ptr<I_Node> Selecter::SearchRandomNode() const {
				std::vector<std::shared_ptr<I_Edge>> transitionEdges;
				for (auto edge : m_transitionEdges) {
					if (edge.lock()->GetToNode()->CanTransition()) {
						transitionEdges.push_back(edge.lock());
					}
				}

				if (transitionEdges.empty()) {	//遷移先が存在しないならnullptrを返す。
					return nullptr;
				}

				auto randomEdge = maru::MyRandom::RandomArray(transitionEdges);
				return randomEdge->GetToNode();
			}

			std::shared_ptr<I_Node> Selecter::SearchSequenceNode() const {
				//積まれた上から順に遷移できるタスクに遷移。
				for (auto& edge : m_transitionEdges) {
					auto toNode = edge.lock()->GetToNode();
					if (toNode->CanTransition()) {
						return toNode;
					}
				}

				return nullptr;
			}

			void Selecter::ChangeCurrentNode(const std::shared_ptr<I_Node>& node) {
				//現在のノードの終了処理をする。
				if (auto currentNode = GetCurrentNode()) {
					currentNode->OnExit();
				}

				m_currentNode = node;

				//変更するノードがnullでなかったら、開始処理をする。
				if (node) {
					node->OnStart();
				}
			}

			//--------------------------------------------------------------------------------------
			/// アクセッサ
			//--------------------------------------------------------------------------------------

			void Selecter::SetFromEdge(const std::shared_ptr<I_Edge>& fromEdge) noexcept {
				m_fromEdge = fromEdge;
			}

			std::shared_ptr<I_Edge> Selecter::GetFromEdge() const noexcept {
				return m_fromEdge.lock();
			}

			void Selecter::AddTransitionEdge(const std::shared_ptr<I_Edge>& edge) {
				m_transitionEdges.push_back(edge);
			}

			bool Selecter::IsEmptyTransitionNodes() const {
				return static_cast<int>(m_transitionEdges.size()) == 0;
			}

			void Selecter::SetCurrentNode(const std::shared_ptr<I_Node>& node) noexcept {
				m_currentNode = node;
			}

			std::shared_ptr<I_Node> Selecter::GetCurrentNode() const noexcept {
				return m_currentNode.lock();
			}

		}
	}
}