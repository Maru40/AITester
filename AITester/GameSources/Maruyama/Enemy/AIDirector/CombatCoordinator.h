
/*!
@file CombatCoordinator.h
@brief CombatCoordinatorなど
担当：丸山裕喜
*/

#pragma once
#include "stdafx.h"

#include "CoordinatorBase.h"

namespace basecross {

	namespace Enemy {

		//--------------------------------------------------------------------------------------
		/// 前方宣言
		//--------------------------------------------------------------------------------------
		class EnemyBase;
		class FactionCoordinator;

		namespace Tuple {
			class Kill;
			class SearchTarget;
			class FindTarget;
			class LostTarget;
		}

		//--------------------------------------------------------------------------------------
		/// 戦闘データのタイプ
		//--------------------------------------------------------------------------------------
		enum class CombatCoordinator_Data_State
		{
			Move,
			Attack,
			Evade,
			Wait,
		};

		//--------------------------------------------------------------------------------------
		/// 戦闘管理データ
		//--------------------------------------------------------------------------------------
		struct CombatCoordinator_Data
		{
			using State = CombatCoordinator_Data_State;

			std::weak_ptr<EnemyBase> selfPtr;
			State state = State::Move;

			//CombatCoordinator_Data();
		};

		//--------------------------------------------------------------------------------------
		/// 戦闘管理、攻撃権限管理、ロールアサイン
		//--------------------------------------------------------------------------------------
		class CombatCoordinator : public HereOwnerCoordinatorBase<FactionCoordinator, EnemyBase>
		{
		public:
			
		private:
			std::vector<std::weak_ptr<GameObject>> m_targets;	//すでに発見済みのターゲット

		public:
			CombatCoordinator(const std::shared_ptr<FactionCoordinator>& owner);

			~CombatCoordinator() = default;

			void OnCreate() override;
			void OnStart() override;
			bool OnUpdate() override;
			void OnExit() override;
			
		private:

		private:
			/// <summary>
			/// ターゲットの監視
			/// </summary>
			void UpdateObserveFindTarget();

			/// <summary>
			/// メンバーがダメージを受けたことを監視
			/// </summary>
			void UpdateObserveDamaged();

			/// <summary>
			/// キルタプルを受け取ったとき。
			/// </summary>
			void NotifyTuple_Kill(const std::shared_ptr<Tuple::Kill>& tuple);

			/// <summary>
			/// ターゲットの検索を託された時。
			/// </summary>
			/// <param name="tuple"></param>
			void NotifyTuple_SearchTarget(const std::shared_ptr<Tuple::SearchTarget>& tuple);

			/// <summary>
			/// 一番優先度の高いターゲットを探して返す。
			/// </summary>
			/// <returns></returns>
			std::shared_ptr<GameObject> SearchPriorityTarget(const std::shared_ptr<GameObject>& requester);

			void NotifyTuple_FindTarget(const std::shared_ptr<Tuple::FindTarget>& tuple);

			void NotifyTuple_LostTarget(const std::shared_ptr<Tuple::LostTarget>& tuple);

			/// <summary>
			/// 同じリクエスタのタプルを削除(本来ここに書くべきじゃない。移動予定)
			/// </summary>
			template<class T>
			void RemoveTuples(std::vector<std::shared_ptr<T>>& tuples, std::shared_ptr<Enemy::Tuple::I_Tupler>& requester) {
				auto iter = tuples.begin();
				while (iter != tuples.end()) {
					if ((*iter)->GetRequester() == requester) {
						iter = tuples.erase(iter);
						continue;
					}
					iter++;
				}
			}

		public:
			//--------------------------------------------------------------------------------------
			/// アクセッサ
			//--------------------------------------------------------------------------------------

			void AddTarget(const std::shared_ptr<GameObject>& target);

			bool RemoveTaret(const std::shared_ptr<GameObject>& target);

			bool HasTarget(const std::shared_ptr<GameObject>& target) const;

			/// <summary>
			/// 発見済みのターゲットを取得する。
			/// </summary>
			/// <returns>発見済みのターゲット</returns>
			std::vector<std::weak_ptr<GameObject>> GetFindTargets() const { return m_targets; }
		};

	}
}