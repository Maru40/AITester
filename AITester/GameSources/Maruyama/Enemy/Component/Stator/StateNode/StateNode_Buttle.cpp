/*!
@file StateNode_HidePlacePatrol.cpp
@brief StateNode_HidePlacePatrolなど実体
*/

#include "stdafx.h"
#include "Project.h"

#include "StateNode_Buttle.h"

#include "Maruyama/Enemy/Component/EnemyBase.h"

#include "Maruyama/Enemy/Behavior/BehaviorTree.h"
#include "Maruyama/Enemy/Behavior/SubBehaviorTree/ButtleTree.h"

#include "Maruyama/Enemy/AIDirector/CoordinatorBase.h"
#include "Maruyama/Enemy/AIDirector/TupleSpace.h"

#include "Maruyama/Utility/Component/TargetManager.h"
#include "Watanabe/Component/PlayerStatus.h"

#include "Maruyama/Enemy/AIDirector/CombatCoordinator.h"
#include "Maruyama/Enemy/AIDirector/FactionCoordinator.h"

#include "Maruyama/Interface/I_FactionMember.h"

#include "Maruyama/Enemy/AIDirector/Calculater/CombatCalculater.h"

namespace basecross {
	namespace Enemy {

		namespace StateNode {

			Buttle::Buttle(const std::shared_ptr<EnemyBase>& owner):
				NodeBase_StateMachine(owner),
				m_behaviorTree(new ButtleTree(owner->GetGameObject()))
			{
				auto object = owner->GetGameObject();

				m_transform = object->GetComponent<Transform>();
				m_targetManager = object->GetComponent<TargetManager>(false);

				m_behaviorTree->OnCreate();
			}

			void Buttle::OnStart() {
				//バトルコーディネーターに移動する。
				auto faction = GetOwner()->GetFactionCoordinator();
				faction->TransitionFaction<CombatCoordinator>(GetOwner());

				//通知設定
				SettingNotify();
			}

			bool Buttle::OnUpdate() {
				m_behaviorTree->OnUpdate();

				return true;
			}

			void Buttle::OnExit() {
				m_behaviorTree->ForceStop();

				//登録した通知を削除
				auto  member = GetOwner();
				auto assignedFaction = member->GetAssignedFaction();	
				assignedFaction->RemoveMember(member);
				assignedFaction->GetTupleSpace()->RemoveAllNotifys(member); //タプルスペースに登録された者を変更
				assignedFaction->GetTupleSpace()->RemoveAllTuples(member);
			}

			void Buttle::SettingNotify() {
				auto tupleSpace = GetOwner()->GetAssignedFaction()->GetTupleSpace();

				//ターゲット発見
				tupleSpace->Notify<Tuple::FindTarget>(
					GetOwner(),
					[&](const std::shared_ptr<Tuple::FindTarget>& tuple) { ObserveOtherFindTarget(tuple); }
				);

				//ダメージ通知
				tupleSpace->Notify<Tuple::Damaged>(
					GetOwner(),
					[&](const std::shared_ptr<Tuple::Damaged>& tuple) { ObserveDamaged(tuple); }
				);

				//Kill通知
				tupleSpace->Notify<Tuple::Kill>(
					GetOwner(),
					[&](const std::shared_ptr<Tuple::Kill>& tuple) { NotifyTuple_Kill(tuple); }
				);
			}

			void Buttle::ObserveOtherFindTarget(const std::shared_ptr<Tuple::FindTarget>& tuple) {
				//条件次第でターゲット変更をする。
				if (!HasTarget()) {
					return;
				}
				
				auto targetManager = m_targetManager.lock();
				//評価値が今のターゲットより小さいなら
				if (tuple->GetValue() < targetManager->CalcuToTargetVec().length()) {
					//ファクションに、こいつを目標にしたいことを伝える。
					targetManager->SetTarget(tuple->GetTarget());
				}
			}

			void Buttle::ObserveDamaged(const std::shared_ptr<Tuple::Damaged>& tuple) {
				//自分自身がダメージを受けた時と、違う相手がダメージを受けた時で処理が違う。
				tuple->GetRequester() == GetOwner() ? SelfDamaged(tuple) : OtherDamaged(tuple);
			}

			void Buttle::SelfDamaged(const std::shared_ptr<Tuple::Damaged>& tuple) {
				auto otherTarget = tuple->GetDamageData().attacker;

				if (!HasTarget()) {
					//ターゲットを持ってないなら、ターゲットを設定。
					m_targetManager.lock()->SetTarget(otherTarget);
					return;
				}

				//同じターゲットなら切り替えの必要はない。
				if (m_targetManager.lock()->GetTarget() == otherTarget) {
					return;
				}

				float currentValue = Calculater::Combat::CalculateEvalutionValue(m_transform.lock(), m_targetManager.lock()->GetTarget());
				float otherValue = Calculater::Combat::CalculateEvalutionValue(m_transform.lock(), otherTarget);

				//ohterValueの方が優先なら、ターゲットを切り替える。
				if (otherValue < currentValue) {
					GetOwner()->GetAssignedFaction()->GetTupleSpace()->Write<Tuple::FindTarget>(
						GetOwner(),
						otherTarget,
						otherValue
					);

					m_targetManager.lock()->SetTarget(otherTarget);
				}
			}

			void Buttle::OtherDamaged(const std::shared_ptr<Tuple::Damaged>& tuple) {
				auto otherTarget = tuple->GetDamageData().attacker;

				//ターゲットが存在しないなら、
				if (!HasTarget()) {
					m_targetManager.lock()->SetTarget(otherTarget);
					return;
				}

				//攻撃中の対象なら、特に何もしない。
				if (m_targetManager.lock()->GetTarget() == otherTarget) {
					return;
				}

				//どちらのターゲットの優先度が高いかを計算する。
				float currentValue = Calculater::Combat::CalculateEvalutionValue(m_transform.lock(), m_targetManager.lock()->GetTarget());
				float otherValue = Calculater::Combat::CalculateEvalutionValue(m_transform.lock(), otherTarget);

				//ohterValueの方が優先なら、助けることを伝える。
				if (otherValue < currentValue) {
					auto tupleSpace = GetOwner()->GetAssignedFaction()->GetTupleSpace();
					tupleSpace->Write<Tuple::HelpAction>(GetOwner(), otherTarget, otherValue);	//HelpWriteする。
				}
			}

			void Buttle::NotifyTuple_Kill(const std::shared_ptr<Tuple::Kill>& tuple) {
				//ターゲットが存在しないなら、強制切り替え,
				//又は、ターゲットが死亡した相手なら切り替える。
				if (!HasTarget() ||
					m_targetManager.lock()->GetTarget() == tuple->GetKilled()	//ターゲットが死亡した相手なら
				) {
					//新規ターゲットの検索依頼
					GetOwner()->GetAssignedFaction()->GetTupleSpace()->Write<Tuple::SearchTarget>(
						GetOwner(),
						m_targetManager.lock(),
						0.0f
					);
				}
			}

			bool Buttle::HasTarget() const {
				auto targetManager = m_targetManager.lock();
				return targetManager->HasTarget();
			}
		}
	}
}