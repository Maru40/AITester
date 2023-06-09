
/*!
@file EnemyAIDirector.cpp
@brief EnemyAIDirectorのクラス実体
担当：丸山裕喜
*/

#include "stdafx.h"
#include "Project.h"

#include "Maruyama/Utility/SingletonComponent/SingletonComponent.h"
#include "EnemyAIDirector.h"

#include "FactionCoordinator.h"
#include "Maruyama/Enemy/Component/EnemyBase.h"

#include "Maruyama/Utility/Utility.h"

#include "Maruyama/Interface/I_TeamMember.h"
#include "Maruyama/Enemy/Component/Stator/AIPlayerStator.h"

namespace basecross {

	std::weak_ptr<Enemy::AIDirector> maru::SingletonComponent<Enemy::AIDirector>::sm_instance;

	namespace Enemy {

		AIDirector::AIDirector(const std::shared_ptr<GameObject>& objPtr):
			maru::SingletonComponent<AIDirector>(objPtr),
			m_tupleSapce(new Tuple::TupleSpace())
		{}

		void AIDirector::OnCreate() {
			//通知の設定
			m_tupleSapce->Notify<Tuple::FindBall>(
				GetThis<AIDirector>(),
				[&](const std::shared_ptr<Tuple::FindBall>& tuple) { NotifyTuple_FindBall(tuple); }
			);
		}

		void AIDirector::OnLateStart() {

		}

		void AIDirector::OnUpdate() {
			//グループ管理の更新
			for (auto& faction : m_factionCoordinators) {
				faction->OnUpdate();
			}
		}

		void AIDirector::NotifyTuple_FindBall(const std::shared_ptr<Tuple::FindBall>& tuple) {
			GetTupleSpace()->Take(tuple);
		}

		void AIDirector::SettingStartAllEnemys() {
			m_enemys = maru::Utility::FindWeakPtrComponents<EnemyBase>();
		}

		std::shared_ptr<FactionCoordinator> AIDirector::CreateFaction(const std::vector<std::weak_ptr<EnemyBase>>& assignMembers) {
			auto coordinator = std::make_shared<FactionCoordinator>(GetThis<AIDirector>(), assignMembers);
			coordinator->OnCreate();
			coordinator->OnStart();
			m_factionCoordinators.push_back(coordinator);

			return coordinator;
		}

		bool AIDirector::RemoveFaction(const std::shared_ptr<FactionCoordinator>& removeCoordinator) {
			removeCoordinator->OnExit();
			return maru::Utility::RemoveVec(m_factionCoordinators, removeCoordinator);
		}

		std::unordered_map<team::TeamType, std::vector<weak_ptr<EnemyBase>>> AIDirector::DivideTeamType(const std::vector<std::weak_ptr<EnemyBase>>& members) {
			std::unordered_map<team::TeamType, std::vector<std::weak_ptr<EnemyBase>>> enemysMap;

			for (auto& weakEnemy : m_enemys) {
				auto enemy = weakEnemy.lock();
				auto teamMember = enemy->GetGameObject()->GetComponent<I_TeamMember>(false);
				if (teamMember) {
					auto teamType = teamMember->GetTeam();
					enemysMap[teamType].push_back(enemy);
				}
				else {
					enemysMap[team::TeamType::Neutral].push_back(enemy);
				}
			}

			return enemysMap;
		}

		void AIDirector::StartAssign() {
			SettingStartAllEnemys();

			//チームタイプごとに分ける。
			auto enemysMap = DivideTeamType(m_enemys);

			//チームごとにファクションを生成する。
			for (auto& pair : enemysMap) {
				auto faction = CreateFaction(pair.second);
			}

			//playerをHidePlaceFactionに入れる。
			for (auto& enemy : m_enemys) {
				auto stator = enemy.lock()->GetGameObject()->GetComponent<AIPlayerStator>();
				if (!stator) {
					continue;
				}

				stator->ForceChangeState(AIPlayerStator::StateType::HidePlacePatrol);
			}
		}

		//--------------------------------------------------------------------------------------
		/// アクセッサ
		//--------------------------------------------------------------------------------------

		void AIDirector::AddEnemy(const std::shared_ptr<EnemyBase>& enemy) {
			m_enemys.push_back(enemy);
		}

		std::shared_ptr<FactionCoordinator> AIDirector::GetFactionCoordinator(const int index) const {
			if (m_factionCoordinators.size() <= index) { //サイズが小さかったら配列オーバー
				return nullptr;
			}

			return m_factionCoordinators[index];
		}

		std::shared_ptr<Tuple::TupleSpace> AIDirector::GetTupleSpace() const noexcept {
			return m_tupleSapce;
		}
	}
}